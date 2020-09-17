#pragma once

#include <alpaka/alpaka.hpp>

#include <stdlib.h>
#include <time.h>
#include <vector>
#include "reduction_library/SOA/Particle.hpp"


namespace reduction_library{
namespace thinning{

    template<class T_particle>
    class KernelThinning{
    private:
        double ratioDeletedPaticles;
        int numOfParticles;

    public:
        KernelThinning(double ratioDeletedPaticles):
            ratioDeletedPaticles(ratioDeletedPaticles),
            numOfParticles(0){}

        void collect(T_particle particle){
            numOfParticles++;
        }

        void process(){

        }
        template<typename Acc>
        ALPAKA_FN_ACC void reduce(Acc const& acc, T_particle particle) const {

            using namespace alpaka;
            double random_value = 0;

            if (random_value < ratioDeletedPaticles)
            {
                particle::set_weighting(0, particle);
            }
        }
    };

} //thinning
} //reduction_library







