#pragma once

#include <vector>

#include "reduction_library/attribute/Scalar_record.hpp"
#include "reduction_library/AOS/Particle.hpp"

namespace reduction_library{
namespace AOS{

    using Momentums = attribute::Scalar_record<attribute::Scalar_records_names::momentum_x, double>;
    using Weights = attribute::Scalar_record<attribute::Scalar_records_names::weighting, double>;


    class Particle_spicies: public Momentums, public Weights {
        int size;
        public:
        using MyParticle = Particle<Particle_spicies>;
        Particle_spicies(std::vector<double>& weights,
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

