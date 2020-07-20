#pragma once

#include <vector>

#include "reduction_library/attribute/Scalar_record.hpp"
#include "reduction_library/AOS/Particle.hpp"
#include "reduction_library/attribute/Base_attributes_getters.hpp"

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

template<>
class attribute::Geting_weighting_power<Particle_spicies, attribute::Scalar_records_names::weighting>
{
public:
    Geting_weighting_power (){}
    double operator() (AOS::Particle_spicies particles)
    {
        AOS::Weights& weights = static_cast<AOS::Weights&>(particles);
        double weighting_power = weights.get_weighting_power();
        return weighting_power;
    }
private:

};

template<>
class attribute::Geting_weighting_power<Particle_spicies, attribute::Scalar_records_names::momentum_x>
{
public:
    Geting_weighting_power (){}
    double operator() (AOS::Particle_spicies particles)
    {
        AOS::Momentums& momentums = static_cast<AOS::Momentums&>(particles);
        double weighting_power = momentums.get_weighting_power();
        return weighting_power;
    }
private:

};

} // reduction_library

