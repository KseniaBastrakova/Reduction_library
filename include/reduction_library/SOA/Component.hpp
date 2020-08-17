#pragma once

#include "reduction_library/component/Type.hpp"
#include "reduction_library/component/Interfaces.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Dataset.hpp"
#include "reduction_library/record/Name.hpp"
#include <vector>
#include <iostream>

namespace reduction_library{
namespace SOA{

    template<typename T_Dataset>
    struct Component {
    public:
        using datasetType = Dataset<T_Dataset>;
    private:
        datasetType dataset;
        double unit_SI;

    public:
        component::Name component_name;
        Component(){}
        Component(component::Name component_name, datasetType dataset):
                unit_SI(42.),
                component_name(component_name),
                dataset(dataset){}

    T_Dataset& operator[](int idx)
    {
        return dataset[idx];
    }

    double get_unit_SI()
    {
        return unit_SI;
    }
    void set_unit_SI(double new_unit_SI)
    {
        unit_SI = new_unit_SI;
    }
    component::Name get_component_name()
    {
        return component_name;
    }
    void set_dataset(datasetType new_dataset){
        dataset = new_dataset;
    }

    /// We use this functions only for test

    void print_component_name(){
        std::cout<<dataset<<std::endl;
    }
    void print_dataset(){
        dataset.print();
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
            double unit_si = component.get_unit_SI();
            return unit_si;
        }

    };

    template<typename T_Dataset>
    struct Setting_unit_SI<SOA::Component<T_Dataset>>
    {
    public:
        void operator() (SOA::Component<T_Dataset>& component, double unit_si)
        {
            component.set_unit_SI(unit_si);
        }

    };

    template<component::Name Component_name, record::Name Record_name, class T_Record>
    struct Getting_value<Component_name, Record_name, Particle<T_Record>>
    {
    public:
        auto operator() (Particle<T_Record>& particle)
        {
            auto base_particles = particle.baseParticles;
            auto & component = record::get<Component_name, T_Record>(base_particles);
            return component[ particle.idx ];
        }

    };

    template<component::Name Component_name, record::Name Record_name, class T_Record, typename T_Dataset>
    struct Setting_value<Component_name, Record_name, Particle<T_Record>, T_Dataset>
    {
    public:
        void operator() (T_Dataset value, Particle<T_Record>& particle)
        {
            auto& base_particles = particle.baseParticles;
            auto& component = record::get<Component_name, T_Record>(base_particles);
            int idx = particle.idx;
            component[idx] = value;
        }

    };

}// namespace component
}// reduction_library

