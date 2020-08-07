#pragma once

#include "reduction_library/component/Type.hpp"
#include "reduction_library/component/Interfaces.hpp"
#include "reduction_library/component/Name.hpp"
#include <vector>
#include <iostream>



namespace reduction_library{
namespace SOA{

    template<class T_Value>
    struct Component {
    private:
        std::vector<T_Value> values;
        double unit_SI;
        component::Name component_name;
    public:
    Component(const std::vector<T_Value>& values, component::Name component_name):
            unit_SI(42.),
            component_name(component_name){}

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
        return component_name;
    }

};

}//SOA


    template<class T_Value>
    struct component::traits::Type<SOA::Component<T_Value>>{
        using type = double;  //T_Value;

    };


    template<class T_Value>
    struct component::Geting_unit_SI<SOA::Component<T_Value>>
    {
    public:
        double operator() (SOA::Component<T_Value>& component)
        {
            double weighting_power = component.get_unit_SI();
            return weighting_power;
        }

    };

    template<class T_Value>
    double get_unit_SI(SOA::Component<T_Value>& component)
    {
      component::Geting_unit_SI<SOA::Component<T_Value>> si_get_functor;
      return si_get_functor.operator ()(component);
    }


    template<class T_Particle_spicies, class T_Value>
    struct component::Getting_value<SOA::Component<T_Value>, Particle<T_Particle_spicies>>
    {
    public:
        typename traits::Type<SOA::Component<T_Value>>::type operator() (Particle<T_Particle_spicies>& particle)
        {
            auto current_value = particle.baseParticles[particle.idx];
            return current_value;
        }

    };

    template<class T_Particle_spicies, class T_Value>
    struct component::Setting_value<SOA::Component<T_Value>, Particle<T_Particle_spicies>>
    {
    public:
        void operator() (typename traits::Type<SOA::Component<T_Value>>::type value,
                Particle<T_Particle_spicies>& particle)
        {
            particle.baseParticles[particle.idx] = value;
        }

    };

}// reduction_library
