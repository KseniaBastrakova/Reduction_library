#pragma once

#include <vector>

#include "../AOS_f/Particle.hpp"
#include "../SOA/Record_component.hpp"
#include "reduction_library/Base_attributes_getters.hpp"

namespace reduction_library{
namespace AOS{

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
class attribute::Geting_weighting_power<Particle_spicies, attribute::Scalar_records_names::weighting>
{
public:
    Geting_weighting_power(){}
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
//	template<Name T_scalar_record>
//class Geting_unit_SI;

//template<typename T_particles, Name T_scalar_record>
  //  double get_unit_SI(T_particles particles){

/*
template<>
class record_component::Geting_unit_SI<AOS::Particle_spicies, record_component::Name::x>
{
public:
	Geting_unit_SI(){}
    double operator() (AOS::Particle_spicies particles)
    {
        AOS::Momentums& momentums = static_cast<AOS::Momentums&>(particles);
        double weighting_power = momentums.get_weighting_power();
        return weighting_power;
    }
private:

};

*/

} // reduction_library

