#pragma once
/*
//#include "reduction_library/record/Type.hpp"
#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/component/Name.hpp"
//#include "reduction_library/SOA/Component.hpp"
#include "reduction_library/record/Type.hpp"
#include "reduction_library/HDNLINE.hpp"

#include <vector>

namespace reduction_library{
namespace SOA{

    template<typename T_X_component, typename T_Y_component, typename T_Z_component>
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
                  record::unit_dimension_type unit_dimension,
                  record::Name record_name):
                  x_component(x_component),
                  y_component(y_component),
                  z_component(z_component),
                  record_name(record_name),
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
            return unit_dimension;
        }

    };

}//SOA

namespace record{
namespace traits{

    template<class T_X_component, class T_Y_component, class T_Z_component>
    struct Type<component::Name::x, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
       using type = T_X_component;
    };

    template<class T_X_component, class T_Y_component, class T_Z_component>
    struct Type<component::Name::y, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
       using type = T_Y_component;
    };

    template<class T_X_component, class T_Y_component, class T_Z_component>
    struct Type<component::Name::z, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
       using type = T_Z_component;
    };
} //namespace traits

    template<class T_X_component, class T_Y_component, class T_Z_component>
    HDNLINE std::vector<component::Name> get_names(const SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>& record)
    {
        return record.get_component_names();

    }

    template<class T_X_component, class T_Y_component, class T_Z_component>
    struct Getting_value<component::Name::x, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
    public:
        typename traits::Type<component::Name::x,
        SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>::type
            operator() (SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>& record)
        {
            auto current_value = record.x_component;
            return current_value;
        }

    };

    template<class T_X_component, class T_Y_component, class T_Z_component>
    struct Getting_value<component::Name::y, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
    public:
        typename traits::Type<component::Name::y,
        SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>::type
            operator() (SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>& record)
        {
            auto current_value = record.y_component;
            return current_value;
        }

    };

    template<class T_X_component, class T_Y_component, class T_Z_component>
    struct Getting_value<component::Name::z, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
    public:
        typename traits::Type<component::Name::z,
        SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>::type
            operator() (SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>& record)
        {
            auto current_value = record.z_component;
            return current_value;
        }

    };

    template<typename T_X_component, typename T_Y_component, typename T_Z_component>
    struct Geting_weighting_power<SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
    public:
      double operator() (SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>& record)
      {
          double weighting_power = record.get_weighting_power();
          return weighting_power;
      }

    };


    template<typename T_X_component, typename T_Y_component, typename T_Z_component>
    struct Geting_macro_weighted<SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
    public:
      double operator() (SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>&& record)
      {
          double weighting_power = record.get_macro_weighted();
          return weighting_power;
      }

    };


    template<typename T_X_component, typename T_Y_component, typename T_Z_component>
    struct Geting_unit_dimension<SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
    public:
      unit_dimension_type operator() (SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>& record)
      {
          unit_dimension_type unit_dimension = record.get_unit_dimension();
          return unit_dimension;
      }

    };

} // namespace record
}// reduction_library
*/
