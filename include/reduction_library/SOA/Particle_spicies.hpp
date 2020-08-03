#pragma once

#include <vector>
#include "reduction_library/SOA/Particle.hpp"
#include "reduction_library/SOA/Record_component.hpp"
#include "reduction_library/Base_attributes_getters.hpp"

namespace reduction_library{
namespace SOA{

    using Momentums = attribute::Record_component<attribute::Scalar_records_names::momentum_x, double>;
    using Weights = attribute::Record_component<attribute::Scalar_records_names::weighting, double>;


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
class attribute::Geting_weighting_power<SOA::Particle_spicies, attribute::Scalar_records_names::weighting>
{
public:
    Geting_weighting_power(){}
    double operator() (SOA::Particle_spicies particles)
    {
        SOA::Weights& weights = static_cast<SOA::Weights&>(particles);
        double weighting_power = weights.get_weighting_power();
        return weighting_power;
    }
private:

};

template<>
class attribute::Geting_weighting_power<SOA::Particle_spicies, attribute::Scalar_records_names::momentum_x>
{
public:
    Geting_weighting_power (){}
    double operator() (SOA::Particle_spicies particles)
    {
        SOA::Momentums& momentums = static_cast<SOA::Momentums&>(particles);
        double weighting_power = momentums.get_weighting_power();
        return weighting_power;
    }
private:

};


} // reduction_library

