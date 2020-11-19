#pragma once

#include "reduction_library/component/Type.hpp"
#include "reduction_library/component/Interfaces.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Dataset.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"
#include <vector>
#include <iostream>

namespace reduction_library{
namespace SOA{

template<typename T_Dataset>
struct Component{
private:
    T_Dataset dataset;
    double unit_SI;

public:
    using Dataset_type = T_Dataset;
    Component(){}

    Component(const Component& component):
        dataset(component.get_dataset()),
        unit_SI(component.get_unit_SI()){}

    template<typename T_Another_Dataset>
    Component(const Component<T_Another_Dataset>& component):
        dataset(component.get_dataset()),
        unit_SI(42.){}

    Component(T_Dataset dataset):
            unit_SI(42.),
            dataset(dataset){}

    auto& operator[](int idx)
    {
        return dataset[idx];
    }

    double get_unit_SI() const
    {
        return unit_SI;
    }
    void set_unit_SI(double new_unit_SI)
    {
        unit_SI = new_unit_SI;
    }
    T_Dataset& set_dataset()
    {
        return dataset;
    }
    const T_Dataset& get_dataset() const
    {
        return dataset;
    }

    /// We use this functions only for test

    void print_component_name(){
        std::cout<<dataset<<std::endl;
    }
    void print_dataset(){
        dataset.print();
    }
    std::size_t get_size(){
        return dataset.get_size();
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

template<typename T_Value>
auto make_component(std::vector<T_Value> values)
{
    using Double_dataset_type = typename SOA::Dataset<double>;
    auto dataset = SOA::Dataset<double>(values);
    auto component = SOA::Component<Double_dataset_type>(dataset);
    return component;
}


template<typename T_Dataset>
struct Geting_unit_SI<SOA::Component<T_Dataset>>
{
public:
    double operator() (SOA::Component<T_Dataset>& component)
    {
         return component.get_unit_SI();
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

