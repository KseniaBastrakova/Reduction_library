#pragma once

#include <alpaka/alpaka.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <iostream>
//#include "reduction_library/SOA/Particle.hpp"
#include "reduction_library/Particle.hpp"


namespace reduction_library{
namespace thinning{

    template<class T_particle>
    class KernelThinning{
    private:
        double ratioDeletedPaticles;
        int numOfParticles;

    public:
        ALPAKA_FN_ACC KernelThinning():
            ratioDeletedPaticles(0),
            numOfParticles(0){}

        ALPAKA_FN_ACC void init(double ratioDeletedPaticles){
            this->ratioDeletedPaticles = ratioDeletedPaticles;
        }

        template<typename Acc>
        ALPAKA_FN_ACC void collect(Acc const& acc, T_particle particle){
            numOfParticles++;
        }

        template<typename Acc>
        ALPAKA_FN_ACC void process(Acc const& acc){

        }
        template<typename Acc>
        ALPAKA_FN_ACC void reduce(Acc const& acc, T_particle particle, double random_value) const {

            using namespace alpaka;
           // double random_value = 0;
            printf("random value  %f \n",  random_value);
            printf("ratioDeletedPaticles  %f \n",  ratioDeletedPaticles);
            if (random_value < ratioDeletedPaticles)
            {
               particle_access::set_weighting(0, particle);
            }
        }
    };

} //thinning
} //reduction_library







