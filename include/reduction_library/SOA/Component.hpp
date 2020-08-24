#pragma once

#include "reduction_library/component/Type.hpp"
#include "reduction_library/component/Interfaces.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Dataset.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"
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
        component::Name* component_name;
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
    void set_dataset(datasetType new_dataset){
        dataset = new_dataset;
    }
    datasetType get_dataset(){
        return dataset;
    }
    component::Name get_name(){
        return *component_name;
    }
  //  void set_name(component::Name new_component_name){
    //    component_name = new_component_name;
 //   }

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



}// namespace component
}// reduction_library

