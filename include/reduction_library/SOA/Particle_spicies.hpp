#pragma once

#include "reduction_library/record/Name.hpp"
#include "reduction_library/SOA/Record_scalar.hpp"
#include "reduction_library/SOA/Record_3d.hpp"


namespace reduction_library{
namespace SOA{

    using Momentums = SOA::Record_3d<record::Name::momentum>;
    using Weights = SOA::Scalar_record<record::Name::weighting>;


    class Particle_spicies: public Momentums, public Weights{
        int size;
        public:
        using MyParticle = Particle<Particle_spicies>;
        Particle_spicies(const std::vector<double>& x_values,
                         const std::vector<double>& y_values,
                         const std::vector<double>& z_values,
                         const std::vector<double>& weights):
                             Momentums(x_values, y_values, z_values),
                             Weights(weights), size(weights.size()){}

        MyParticle getParticle(int idx){
            return MyParticle(idx, *this);
        }
        int getSize(){
            return size;
        }

    };

} // SOA
} // reduction_library
