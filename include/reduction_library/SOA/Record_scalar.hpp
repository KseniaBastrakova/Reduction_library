#pragma once

#include "reduction_library/record/Type.hpp"
#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Component.hpp"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/HINLINE.hpp"

#include <vector>

namespace reduction_library{
namespace SOA{


    template<record::Name T_record, typename T_Scalar_component>
    struct Scalar_record{
    private:
        int macroWeighted;
        double weightingPower;
        component::Name component_name;
        record::Name record_name;
        T_Scalar_component scalar_component;

    public:
        Scalar_record(T_Scalar_component scalar_component):
               scalar_component(scalar_component),
               record_name(T_record),
               macroWeighted(7),
               weightingPower(42.),
               component_name(component::Name::SCALAR){}

        double get_weighting_power(){
            return weightingPower;
        }
        int get_macro_weighted(){
            return weightingPower;
        }
        component::Name get_component_name() const{
            return component_name;
        }
        int get_size(){
            int size = 777;
            return size;
        }

    };

}//SOA

    template<record::Name T_record, typename T_Scalar_component>
    HINLINE std::vector<component::Name> record::get_names(const SOA::Scalar_record<T_record, T_Scalar_component>& record)
    {
        std::vector<component::Name> component_names = {record.get_component_name()};
        return component_names;

    }

    template<record::Name T_record, typename T_Scalar_component>
    struct record::Geting_weighting_power<SOA::Scalar_record<T_record, T_Scalar_component>>
    {
    public:
      double operator() (SOA::Scalar_record<T_record, T_Scalar_component>& record)
      {
          double weighting_power = record.get_weighting_power();
          return weighting_power;
      }

    };


    template<record::Name T_record, typename T_Scalar_component>
    struct record::Geting_macro_weighted<SOA::Scalar_record<T_record, T_Scalar_component>>
    {
    public:
      double operator() (SOA::Scalar_record<T_record, T_Scalar_component>&& record)
      {
          double weighting_power = record.get_macro_weighted();
          return weighting_power;
      }

    };

} //reduction_library
