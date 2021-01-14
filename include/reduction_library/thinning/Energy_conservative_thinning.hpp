/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <vector>
#include <functional>
#include <alpaka/alpaka.hpp>

#include "../Particle_getters.hpp"
#include "reduction_library/thinning/helpers/Sample_getting.hpp"
#include "reduction_library/thinning/helpers/Energy_counting.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"
#include "reduction_library/helpers/Type_list.hpp"

namespace reduction_library{
namespace thinning{
/** @file
 * Particle reduction method "energy conservative"
 * the idea is that we select a random macro-particle m times,
 * but do this with probability proportional to energy,
 * i.e. the i-th macroparticle is selected with probability e_i * w_i /E,
 * where e_i is the energy of the particle represented by the i-th macroparticle
 * and E = sum (i=0, i=n)(e_i w_i). The macroparticles that have been
 * selected c_i != 0 times are assigned with the weight c_i*E/ (e_i*m) and the others
 * are removed. One can check that this procedure complies with the principle of agnostic down-sampling and also
 * strictly conserves the total energy E in each cell. However, this method does
 * not strictly conserve the total weight W . This method is useful when the total
 * kinetic energy of particles needs to be strictly conserved.
 *
 * Based on "Strategies for particle resampling in PIC simulations" --
 * A. Muraviev, A. Bashinov, E. Efimenko, V. Volokitin, I. Meyerov, A. Gonoskov
 *
 */
    /** Particle reduction with "in kernell" implementation,
     * that requires additional memeory for random sample storage
     * and getting unique index for each particle for indexation
     * (particles can be strored in every datastructure, but each particle
     * must support functions:
     *
     * getting unique idx for component::name::SCALAR Componenent and
     * Record record::name::Idx
     *
     * getting weight for component::name::SCALAR Componenent and
     * Record record::name::Weight
     *
     * getting x, y, z momentum for component::name::X, component::name::Y,
     * component::name::Z
     * and Record record::name::Momentum
     *
     * getting Mass for component::name::SCALAR Componenent and
     * Record record::name::Mass (can be zero)
     *
     */

    class Energy_conservative_thinning{
    private:
        //-----------------------------------------------------------------------------
        //! Ratio of particles to be deleted (ex: 0.1 = 10%, 0.8 = 80%)
        double ratio_deleted_paticles;
        //-----------------------------------------------------------------------------
        //! Memory for storage energy for each particle. We need one double for each reduced particle
        double *energyes;
        //-----------------------------------------------------------------------------
        //! Sum energies multiply by weight for all particles
        double sum_weighted_energyes;
        //-----------------------------------------------------------------------------
        //! Number of input particles
        int number_particles;

    public:
        /** Input parameters for algorithm
         *  std:: tuple with
         *  1-st parameter : ratio of deleted particles (from 0 to 1)
         *  2-st parameter pointer to additional memory,
         *  for energies storages: needs (number_of_particles * size_of_double) memory
         *  3-st parameter : number input particles
         */
        using Parameters = helpers::Type_list<double, double *, int>;
        ALPAKA_FN_ACC Energy_conservative_thinning():
            ratio_deleted_paticles(0),
            sum_weighted_energyes(0),
            number_particles(0),
            energyes(NULL){}

        /** Algorithm initialization:
         *  with tuple, contains:
         *  ratio of deleted particles (from 0 to 1) (double)
         *  parameter pointer to additional memory, needs(number_of_particles * size_of_double) (double *)
         *  number input particles (int)
         */
        ALPAKA_FN_ACC void init(Energy_conservative_thinning::Parameters parameters)
        {
            this->ratio_deleted_paticles = std::get<0>(parameters);
            this->energyes = std::get<1>(parameters);
            this->number_particles = std::get<2>(parameters);
        }

        /** Collecting all particles for reducing
         *
         * compute sum of energies, and energy for each particle,
         * that stored for each unique particle idx
         *
         * \tparam Acc Alpaka accelerator type
         * \tparam T_Particle type of particle. Should provide nessary functions
         * for getting and setting parameters
         *
         * \tparam T_Random_Generator type of functor of random generator.
         * Should allow getting stream independent random number
         */
        template<typename Acc, typename T_Particle, typename T_Random_Generator>
        ALPAKA_FN_ACC void collect(Acc const& acc, T_Particle& particle, T_Random_Generator& generator)
        {
            using namespace alpaka;
            Getting_particle_energy<T_Particle> counter;
            double energy = counter(particle);
            double weight = particle_access::get_weighting(particle);
            double weighted_energy = energy * weight;
            atomic::atomicOp<atomic::op::Add>(acc, &sum_weighted_energyes, (double)weighted_energy, hierarchy::Blocks{});
            int particle_idx = particle_access::get_idx(particle);
            this->energyes[particle_idx] = energy;
        }

        /** Process algorithm quantities
         *
         * compute new weight for each particle:
         * 0 (particles, that marks to be deleted)
         * (c_i * W/m), otherwise
         *
         * \tparam Acc Alpaka accelerator type
         * \tparam T_Random_Generator type of functor of random generator.
         * Should allow getting stream independent random number
         *
         */
        template<typename Acc, typename T_Random_Generator>
        ALPAKA_FN_ACC void process(Acc const& acc, T_Random_Generator& generator)
        {
            Getting_n_inc_weighted_sample<T_Random_Generator, double> sample_getter;
            std::vector<double> weighted_energy(energyes, energyes + number_particles);

            std::transform(weighted_energy.begin(), weighted_energy.end(), weighted_energy.begin(),
                           std::bind(std::divides<double>(), std::placeholders::_1, sum_weighted_energyes));

            std::size_t m_times = (std::size_t)(-1. * number_particles * log(1. - ratio_deleted_paticles)) + 1;

            std::vector<double> number_of_inc = sample_getter(weighted_energy, m_times, generator);
            for (int i = 0; i < number_of_inc.size(); i++)
            {
                energyes[i] = number_of_inc[i] * sum_weighted_energyes / m_times;
            }
        }

        /** Assign all particles with new weight
         *
         * 0 (particles, that marks to be deleted)
         * (c_i * W/m), otherwise
         *
         * \tparam Acc Alpaka accelerator type
         * \tparam T_Random_Generator type of functor of random generator.
         * Should allow getting stream independent random number
         * \tparam T_Particle type of particle. Should provide nessary functions
         * for getting and setting parameters
         *
         */
        template<typename Acc, typename T_Particle, typename T_Random_Generator>
        ALPAKA_FN_ACC void reduce(Acc const& acc, T_Particle& particle, T_Random_Generator& generator) const
        {
            using namespace alpaka;
            Getting_particle_energy<T_Particle> counter;
            double energy = counter(particle);
            int particle_idx = particle_access::get_idx(particle);
            double new_weight = energyes[particle_idx] / energy;
            particle_access::set_weighting(new_weight, particle);

        }
    };

} //thinning
} //reduction_library
