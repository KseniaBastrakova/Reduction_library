#pragma once
#include <vector>
#include "AtrributeChunk.hpp"
#include "Particle.hpp"

namespace reduction_library{

    using Momentums = AtrributeChunk<Attribute::momentum_x, double>;
    using Weights = AtrributeChunk<Attribute::weighting, double>;


    class Particles: public Momentums, public Weights {
        int size;
        public:
        using MyParticle = Particle<Particles>;
        Particles(std::vector<double>& weights,
                 std::vector<double>& momentum):
                     Momentums(momentum), Weights(weights), size(weights.size()){}

        MyParticle getParticle(int idx){

            return MyParticle(idx, *this);
        }
        int getSize(){
            return size;
        }

    };

}

