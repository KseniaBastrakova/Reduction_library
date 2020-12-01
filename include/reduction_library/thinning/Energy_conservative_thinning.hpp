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
#include "reduction_library/Particle.hpp"
#include "reduction_library/thinning/helpers/Sample_getting.hpp"
#include "reduction_library/thinning/helpers/Energy_counting.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"
#include "reduction_library/helpers/Type_list.hpp"

namespace reduction_library{
namespace thinning{

class Energy_conservative_thinning{
private:
    double ratio_deleted_paticles;
    double *energyes;
    double sum_weighted_energyes;
    int number_particles;

public:
    using Parameters = helpers::Type_list<double, double *, int>;
    ALPAKA_FN_ACC Energy_conservative_thinning():
        ratio_deleted_paticles(0),
        sum_weighted_energyes(0),
        number_particles(0),
        energyes(NULL){}

    //double ratioDeletedPaticles, double *p_memory, int number_particles
    ALPAKA_FN_ACC void init(Energy_conservative_thinning::Parameters parameters)
    {
        this->ratio_deleted_paticles = std::get<0>(parameters);
        this->energyes = std::get<1>(parameters);
        this->number_particles = std::get<2>(parameters);
    }

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

    template<typename Acc, typename T_Particle, typename T_Random_Generator>
    ALPAKA_FN_ACC void reduce(Acc const& acc, T_Particle& particle, T_Random_Generator& generator) const
    {
        using namespace alpaka;
        Getting_particle_energy<T_Particle> counter;
        double energy = counter(particle);
        int particle_idx = particle_access::get_idx(particle);
        double new_weight = energyes[particle_idx] / energy;
        std::cout<<"new_weight "<<new_weight<<" ";
        particle_access::set_weighting(new_weight, particle);

    }
};

} //thinning
} //reduction_library
