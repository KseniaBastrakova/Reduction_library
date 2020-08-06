#pragma once

#include "reduction_library/record/Type.hpp"
#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Component.hpp"
#include "reduction_library/HDNLINE.hpp"

#include <vector>

namespace reduction_library{
namespace SOA{

    template<record::Name T_record, typename T_X_component, typename T_Y_component, typename T_Z_component>
    struct Record_3d {
    private:
        int macroWeighted;
        double weightingPower;
        std::vector<component::Name> component_names;
        record::Name record_name;
        T_X_component x_component;
        T_Y_component y_component;
        T_Z_component z_component;
        record::unit_dimension_type unit_dimension;

    public:
        Record_3d(T_X_component x_component,
                  T_Y_component y_component,
                  T_Z_component z_component,
                  record::unit_dimension_type unit_dimension):
                  x_component(x_component),
                  y_component(y_component),
                  z_component(z_component),
                  record_name(T_record),
                  macroWeighted(7),
                  weightingPower(42.),
                  unit_dimension(unit_dimension){
                  component_names.push_back(component::Name::x);
                  component_names.push_back(component::Name::y);
                  component_names.push_back(component::Name::z);
        }

        double get_weighting_power(){
            return weightingPower;
        }
        int get_macro_weighted(){
            return weightingPower;
        }
        std::vector<component::Name> get_component_names() const{
            return component_names;
        }
        int get_size(){
            int size = 777;
            return size;
        }
        record::unit_dimension_type get_unit_dimension() const{

        }

    };


}//SOA

    template<record::Name T_record, typename T_X_component, typename T_Y_component, typename T_Z_component>
    HDNLINE std::vector<component::Name> record::get_names(const SOA::Record_3d<T_record, T_X_component, T_Y_component, T_Z_component>& record)
    {
        return record.get_component_names();

    }

   // template<>
    //HDNLINE typename record::traits::Type<SOA::Record_3d<component::Name::x, record::Name::momentum>>::type
    //record::get<SOA::Record_3d<record::Name::momentum>>(SOA::Record_3d<record::Name::momentum>& record)
   // {
    //    double result = 777.0;
     //   return result;
   // }

    template<record::Name T_record, typename T_X_component, typename T_Y_component, typename T_Z_component>
    struct record::Geting_weighting_power<SOA::Record_3d<T_record, T_X_component, T_Y_component, T_Z_component>>
    {
    public:
      double operator() (SOA::Record_3d<T_record, T_X_component, T_Y_component, T_Z_component>& record)
      {
          double weighting_power = record.get_weighting_power();
          return weighting_power;
      }

    };


    template<record::Name T_record, typename T_X_component, typename T_Y_component, typename T_Z_component>
    struct record::Geting_macro_weighted<SOA::Record_3d<T_record, T_X_component, T_Y_component, T_Z_component>>
    {
    public:
      double operator() (SOA::Record_3d<T_record, T_X_component, T_Y_component, T_Z_component>&& record)
      {
          double weighting_power = record.get_macro_weighted();
          return weighting_power;
      }

    };


    template<record::Name T_record, typename T_X_component, typename T_Y_component, typename T_Z_component>
    struct record::Geting_unit_dimension<SOA::Record_3d<T_record, T_X_component, T_Y_component, T_Z_component>>
    {
    public:
      unit_dimension_type operator() (SOA::Record_3d<T_record, T_X_component, T_Y_component, T_Z_component>& record)
      {
          unit_dimension_type unit_dimension = record.get_unit_dimension();
          return unit_dimension;
      }

    };

}// reduction_library

