#pragma once

#include <alpaka/alpaka.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <iostream>
#include "reduction_library/Particle.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"


namespace reduction_library{
namespace thinning{

class In_kernel_thinning{
private:
    double ratioDeletedPaticles;
    int num_of_left_particles;
    double sum_reduced_weights;
    double part_of_additional_weight;

public:
    ALPAKA_FN_ACC In_kernel_thinning():
        ratioDeletedPaticles(0),
        num_of_left_particles(0),
        sum_reduced_weights(0.),
        part_of_additional_weight(0.){}

    ALPAKA_FN_ACC void init(double ratioDeletedPaticles)
    {
        this->ratioDeletedPaticles = ratioDeletedPaticles;
        num_of_left_particles = 0;
        sum_reduced_weights = 0.;
        part_of_additional_weight = 0.;
    }

    template<typename Acc, typename T_Particle, typename T_Random_Generator>
    ALPAKA_FN_ACC void collect(Acc const& acc, T_Particle& particle, const T_Random_Generator& generator)
    {
        using namespace alpaka;
        double random_value = generator();
        if (random_value < ratioDeletedPaticles)
        {
           particle_access::set_weighting(0, particle);
           auto weight = particle_access::get_weighting(particle);
           atomic::atomicOp<atomic::op::Add>(acc, &sum_reduced_weights, (double)weight, hierarchy::Blocks{});
        }
        else
        {
            atomic::atomicOp<atomic::op::Add>(acc, &num_of_left_particles, (int)1, hierarchy::Blocks{});
        }

    }

    template<typename Acc>
    ALPAKA_FN_ACC void process(Acc const& acc)
    {
        part_of_additional_weight = sum_reduced_weights / num_of_left_particles;
    }

    template<typename Acc, typename T_Particle>
    ALPAKA_FN_ACC void reduce(Acc const& acc, T_Particle& particle) const
    {
        double weight = particle_access::get_weighting(particle);
        if ( weight > 0 )
        {
            double result_weight = weight + part_of_additional_weight;
            particle_access::set_weighting(result_weight, particle);
        }

    }
};

} //thinning
} //reduction_library
