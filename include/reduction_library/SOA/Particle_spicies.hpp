#pragma once

#include "reduction_library/record/Name.hpp"
#include "reduction_library/SOA/Record_scalar.hpp"
#include "reduction_library/SOA/Record_3d.hpp"
#include "reduction_library/SOA/Particle.hpp"


namespace reduction_library{
namespace SOA{
  /*  using Double_component = Component<double>;

    using Momentums = SOA::Record_3d<record::Name::momentum, Double_component, Double_component, Double_component>;
    using Weights = SOA::Scalar_record<record::Name::weighting, Double_component>;
    //, public Weights


    class Particle_spicies: public Momentums{
        int size;
        public:
        using MyParticle = Particle<Particle_spicies>;
        Particle_spicies(const std::vector<double>& x_values,
                         const std::vector<double>& y_values,
                         const std::vector<double>& z_values,
                         const std::vector<double>& weights):
                             Momentums(x_values, y_values, z_values), size(weights.size()){}

        MyParticle getParticle(int idx){
            return MyParticle(idx, *this);
        }
        int getSize(){
            return size;
        }

    };
*/
} // SOA
} // reduction_library
