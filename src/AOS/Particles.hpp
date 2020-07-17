#pragma once

#include <vector>

#include "reduction_library/attribute/AtrributeChunk.hpp"
#include "particles/Particle.hpp"

namespace reduction_library{
namespace AOS{

    using Momentums = attribute::AtrributeChunk<attribute::Attribute::momentum_x, double>;
    using Weights = attribute::AtrributeChunk<attribute::Attribute::weighting, double>;


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

} // AOS
} // reduction_library

