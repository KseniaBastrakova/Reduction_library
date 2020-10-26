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
    //public:
    //    using datasetType = Dataset<T_Dataset>;
    private:
        T_Dataset dataset;
        double unit_SI;

    public:
        Component(){}
        Component(T_Dataset dataset):
                unit_SI(42.),
                dataset(dataset){}

    auto& operator[](int idx)
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
    void set_dataset(T_Dataset new_dataset){
        dataset = new_dataset;
    }
    T_Dataset& get_dataset(){
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

