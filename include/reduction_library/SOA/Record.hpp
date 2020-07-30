#pragma once

#include "reduction_library/record/Type.hpp"
#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/record/Name.hpp"

#include <vector>

namespace reduction_library{
namespace SOA{

    template<component::Name T_component, class T_Value>
    struct Component {
    private:
        std::vector<T_Value> values;
        double unit_SI;
        component::Name component_name;
    public:
        Component(const std::vector<T_Value>& values):
            unit_SI(42.), component_name(T_component){}

        std::vector<T_Value>& get()
        {
            return values;
        }
        double get_unit_SI()
        {
            return unit_SI;
        }
        component::Name get_component_name()
        {
            return T_component;
        }


    };


}//SOA

    template<component::Name T_component, class T_Value>
    struct component::Geting_unit_SI<SOA::Component<T_component, T_Value>>
    {
    public:
        double operator() (SOA::Component<T_component, T_Value>&& component)
        {
            double weighting_power = component.get_unit_SI();
            return weighting_power;
        }

    };

    template <>
    component::traits::Type<SOA::Component<component::Name::x, double>>::type
        component::get<SOA::Component<component::Name::x, double>, Particle<Particle_spicies>>
    (Particle<Particle_spicies>& particle)
    {
        double component_idx = particle.idx;
        //auto value = component.get()[component_idx];
        return component_idx;
    };


    template <>
    void component::set<SOA::Component<component::Name::x, double>, Particle<Particle_spicies>>
    (component::traits::Type<SOA::Component<component::Name::x,
            double>>::type value, Particle<Particle_spicies>& particle)
    {
        int component_idx = particle.idx;
       // component.get()[component_idx] = value;

    };



}// reduction_library

