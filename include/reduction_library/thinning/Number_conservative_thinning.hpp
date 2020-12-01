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
#include "reduction_library/particle_species/Interfaces.hpp"
#include "reduction_library/helpers/Type_list.hpp"

namespace reduction_library{
namespace thinning{

class Number_conservative_thinning{
private:
    double ratio_deleted_paticles;
    double *weights;
    double sum_weights;
    int number_particles;

public:
    using Parameters = helpers::Type_list<double, double *, int>;
    ALPAKA_FN_ACC Number_conservative_thinning():
        ratio_deleted_paticles(0),
        sum_weights(0),
        number_particles(0),
        weights(NULL){}

    ALPAKA_FN_ACC void init(Number_conservative_thinning::Parameters parameters)
    {
        this->ratio_deleted_paticles = std::get<0>(parameters);
        this->weights = std::get<1>(parameters);
        this->number_particles = std::get<2>(parameters);
    }

    template<typename Acc, typename T_Particle, typename T_Random_Generator>
    ALPAKA_FN_ACC void collect(Acc const& acc, T_Particle& particle, T_Random_Generator& generator)
    {
        using namespace alpaka;
        double weight = particle_access::get_weighting(particle);
        atomic::atomicOp<atomic::op::Add>(acc, &sum_weights, (double)weight, hierarchy::Blocks{});
        int particle_idx =  particle_access::get_idx(particle);
        this->weights[particle_idx] = weight;
    }

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

    template<typename Acc, typename T_Particle, typename T_Random_Generator>
    ALPAKA_FN_ACC void reduce(Acc const& acc, T_Particle& particle, T_Random_Generator& generator) const
    {
        int particle_idx = particle_access::get_idx(particle);
        double new_weight = weights[particle_idx];
        particle_access::set_weighting(new_weight, particle);

    }
};

} //thinning
} //reduction_library
