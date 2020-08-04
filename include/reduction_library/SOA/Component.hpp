#pragma once

#include "reduction_library/component/Type.hpp"
#include "reduction_library/component/Interfaces.hpp"
#include "reduction_library/component/Name.hpp"
#include <vector>
#include <iostream>



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
        double operator() (SOA::Component<T_component, T_Value>& component)
        {
            double weighting_power = component.get_unit_SI();
            return weighting_power;
        }

    };

    template<component::Name T_component, class T_Value>
    double get_unit_SI(SOA::Component<T_component, T_Value>& component)
    {
      component::Geting_unit_SI<SOA::Component<T_component, T_Value>> si_get_functor;
      return si_get_functor.operator ()(component);
    }

    class Particle_spicies;
    template <>
    component::traits::Type<SOA::Component<component::Name::x, double>>::type
        component::get<SOA::Component<component::Name::x, double>, Particle<Particle_spicies>>
    (Particle<Particle_spicies>& particle);


    template <>
    void component::set<SOA::Component<component::Name::x, double>, Particle<Particle_spicies>>
    (component::traits::Type<SOA::Component<component::Name::x, double>>::type value,
            Particle<Particle_spicies>& particle);


}// reduction_library

