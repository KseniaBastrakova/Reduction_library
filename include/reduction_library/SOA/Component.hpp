#pragma once

#include "reduction_library/component/Type.hpp"
#include "reduction_library/component/Interfaces.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/record/Name.hpp"
#include <vector>
#include <iostream>

namespace reduction_library{
namespace SOA{

    template<typename T_Dataset>
    struct Component {
    private:
        T_Dataset dataset;
        double unit_SI;

    public:
        using datasetType = T_Dataset;
        component::Name component_name;
        Component(){}
        Component(component::Name component_name, T_Dataset dataset):
                unit_SI(42.),
                component_name(component_name),
                dataset(dataset){}

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


namespace component{
namespace traits{
    template<typename T_Dataset>
    struct Type<SOA::Component<T_Dataset>>{
        using type = T_Dataset;

    };
}

    template<typename T_Dataset>
    struct Geting_unit_SI<SOA::Component<T_Dataset>>
    {
    public:
        double operator() (SOA::Component<T_Dataset>& component)
        {
            double weighting_power = component.get_unit_SI();
            return weighting_power;
        }

    };

    template<typename T_Dataset>
    double get_unit_SI(SOA::Component<T_Dataset>& component)
    {
      Geting_unit_SI<SOA::Component<T_Dataset>> si_get_functor;
      return si_get_functor.operator ()(component);
    }

    template<component::Name T_component, record::Name T_record, class T_Dataset>
    struct Getting_value<SOA::Component<T_Dataset>, Particle<T_record>>
    {
    public:
        typename traits::Type<SOA::Component<T_Dataset>>::type operator() (Particle<T_record>& particle)
        {
          // реализация тут
        }

    };
}
}
/*
    template<class T_Particle_spicies, typename T_Dataset>
    struct Getting_value<SOA::Component<T_Dataset>, Particle<T_Particle_spicies>>
    {
    public:
        typename traits::Type<SOA::Component<T_Dataset>>::type operator() (Particle<T_Particle_spicies>& particle)
        {
            //auto & record = std::get< T_Record >(particle.baseParticles);

          //   auto & component = record::get< ComponentName >( record );
            //   return component[ idx ];
            auto current_value = particle.baseParticles[particle.idx];
            return current_value;
        }

    };



    template<class T_Particle_spicies, typename T_Dataset>
    struct Getting_value<SOA::Component<T_Dataset>, Particle<T_Particle_spicies>>
    {
    public:
        typename traits::Type<SOA::Component<T_Dataset>>::type operator() (Particle<T_Particle_spicies>& particle)
        {
            //auto & record = std::get< T_Record >(particle.baseParticles);

          //   auto & component = record::get< ComponentName >( record );
            //   return component[ idx ];
            auto current_value = particle.baseParticles[particle.idx];
            return current_value;
        }

    };

    template<class T_Particle_spicies, typename T_Dataset>
    struct Setting_value<SOA::Component<T_Dataset>, Particle<T_Particle_spicies>>
    {
    public:
        void operator() (typename traits::Type<SOA::Component<T_Dataset>>::type value,
                Particle<T_Particle_spicies>& particle)
        {
            particle.baseParticles[particle.idx] = value;
        }

    };

}// namespace component
}// reduction_library
*/
