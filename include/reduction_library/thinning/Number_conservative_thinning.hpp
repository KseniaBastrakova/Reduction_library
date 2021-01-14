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
#include "reduction_library/particle_species/Interfaces.hpp"
#include "reduction_library/helpers/Type_list.hpp"

namespace reduction_library{
namespace thinning{
/** @file
 * Particle reduction method "number conservative"
 * the idea is that we select random macroparticles with probability proportional
 *  to their weight, i.e. w i /W , where W = w i . We repeat this selection m
 *  times and count the number of times c i we have chosen the i-th macro-particle.
 *  After that the particles that have not been selected even once (c i = 0) are
 *  removed and the others are assigned with a new weight equal to ŵ i = c i W/m.
 *  It is clear that the i-th macro-particle will be selected hc i i = mw i /W times on
 *  average and thus the mathematical expectation of the change in the macroparticle’s
 *   weight is zero: h ŵ i i = (hc i i W/m) = w i , i.e. the method is agnostic.
 *   This procedure strictly conserves the total weight of macro-particles in a cell:
 *   Ŵ =ŵ i = c_i* W/m = W .
 *
 * Based on "Strategies for particle resampling in PIC simulations" --
 * A. Muraviev, A. Bashinov, E. Efimenko, V. Volokitin, I. Meyerov, A. Gonoskov
 *
 */
    /** Particle reduction with "in kernell" implementation,
     * that requires additional memory for random sample storage
     * and getting unique index for each particle for indexing
     * (particles can be stored in every data structure, but each particle
     * must support functions:
     *
     * getting unique idx for component::name::SCALAR Componenent and
     * Record record::name::Idx
     *
     * getting weight for component::name::SCALAR Componenent and
     * Record record::name::Weight
     *
     */

    class Number_conservative_thinning{
    private:
        //-----------------------------------------------------------------------------
        //! Ratio of particles to be deleted (ex: 0.1 = 10%, 0.8 = 80%)
        double ratio_deleted_paticles;
        //-----------------------------------------------------------------------------
        //! Memory for storage normalize weight for each particle. We need one double for each reduced particle
        double *weights;
        //-----------------------------------------------------------------------------
        //! Sum of all weights of input particles
        double sum_weights;
        //-----------------------------------------------------------------------------
        //! Amount of input particles
        int number_particles;
    public:
        /** Input parameters for algorithm
         *  std:: tuple with
         *  1-st parameter : ratio of deleted particles (from 0 to 1)
         *  2-st parameter pointer to additional memory,
         *  for weights storages: needs (number_of_particles * size_of_double) memory
         *  3-st parameter : number input particles
         */
        using Parameters = helpers::Type_list<double, double *, int>;
        ALPAKA_FN_ACC Number_conservative_thinning():
            ratio_deleted_paticles(0),
            sum_weights(0),
            number_particles(0),
            weights(NULL){}

        /** Algorithm initialization:
         *  with tuple, contains:
         *  ratio of deleted particles (from 0 to 1) (double)
         *  parameter pointer to additional memory, needs(number_of_particles * size_of_double) (double *)
         *  number input particles (int)
         */
        ALPAKA_FN_ACC void init(Number_conservative_thinning::Parameters parameters)
        {
            this->ratio_deleted_paticles = std::get<0>(parameters);
            this->weights = std::get<1>(parameters);
            this->number_particles = std::get<2>(parameters);
        }

        /** Collecting all particles for reducing
         *
         * compute sum of weights, and set of weights
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
            double weight = particle_access::get_weighting(particle);
            atomic::atomicOp<atomic::op::Add>(acc, &sum_weights, (double)weight, hierarchy::Blocks{});
            int particle_idx =  particle_access::get_idx(particle);
            this->weights[particle_idx] = weight;
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
            std::vector<double> normalize_weights(weights, weights + number_particles);

            std::transform(normalize_weights.begin(), normalize_weights.end(), normalize_weights.begin(),
                           std::bind(std::divides<double>(), std::placeholders::_1, sum_weights));

            std::size_t m_times = (std::size_t)(-1. * number_particles * log(1. - ratio_deleted_paticles)) + 1;

            std::vector<double> number_of_inc = sample_getter.operator ()(normalize_weights, m_times, generator);
            for (int i = 0; i < number_of_inc.size(); i++)
            {
                weights[i] = number_of_inc[i] * sum_weights / m_times;
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
            int particle_idx = particle_access::get_idx(particle);
            double new_weight = weights[particle_idx];
            particle_access::set_weighting(new_weight, particle);

        }
    };

} //namespace thinning
} //namespace reduction_library
