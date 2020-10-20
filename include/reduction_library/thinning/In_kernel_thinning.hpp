#pragma once

#include <alpaka/alpaka.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <iostream>
#include "reduction_library/Particle.hpp"


namespace reduction_library{
namespace thinning{

    template<class T_particle>
    class In_kernel_thinning{
    private:
        double ratioDeletedPaticles;
        int numOfParticles;

    public:
        ALPAKA_FN_ACC In_kernel_thinning():
            ratioDeletedPaticles(0),
            numOfParticles(0){}

        ALPAKA_FN_ACC void init(double ratioDeletedPaticles){
            this->ratioDeletedPaticles = ratioDeletedPaticles;
            numOfParticles = 0;
        }

        template<typename Acc>
        ALPAKA_FN_ACC void collect(Acc const& acc, T_particle particle){

        	using namespace alpaka;
        	atomic::atomicOp<atomic::op::Add>(acc, &numOfParticles, (int)1, hierarchy::Blocks{});
        }

        template<typename Acc>
        ALPAKA_FN_ACC void process(Acc const& acc){


        }
        template<typename Acc, typename T_random_generator>
        ALPAKA_FN_ACC void reduce(Acc const& acc, T_particle& particle, T_random_generator& generator) const {
            using namespace alpaka;
            double random_value = generator();
            if (random_value < ratioDeletedPaticles)
            {
               particle_access::set_weighting(0, particle);
            }
        }
    };

} //thinning
} //reduction_library







