#pragma once
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "particles/Particle.hpp"
#include "particles/Particlest.hpp"

namespace reduction_library{

    template<class T_particle>
    class IKernaellThinning{
    private:
        double ratioDeletedPaticles;
        int numOfParticles;

    public:
        IKernaellThinning(double ratioDeletedPaticles):
            ratioDeletedPaticles(ratioDeletedPaticles),
            numOfParticles(0){}

        void collect(T_particle particle){
            numOfParticles++;
        }

        void process(){

        }

        void reduce(T_particle particle){
            double random_value = ((double) rand() / (RAND_MAX));
            if (random_value < ratioDeletedPaticles)
            {
                auto& weihgting = set_attribute<T_particle, Attribute::momentum_x>(particle);
                weihgting = 0;
            }
        }
    };
}







