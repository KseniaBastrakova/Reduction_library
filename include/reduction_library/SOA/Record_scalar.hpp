#pragma once

#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Component.hpp"//
#include "reduction_library/SOA/Dataset.hpp"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/HINLINE.hpp"

#include <vector>

namespace reduction_library{
namespace SOA{
    template<typename T_Value_type>
    struct Scalar_record{
    public:
        using This = Scalar_record<T_Value_type>;
        using Dataset_current = Dataset<T_Value_type>;
        using Component_current = Component<Dataset_current, This>;

    private:
        int macroWeighted;
        double weightingPower;
        component::Name component_name;
        record::Name record_name;
        Component_current component;

    public:
        Scalar_record(){}
        Scalar_record(record::Name record_name, Dataset<T_Value_type> values):
               record_name(record_name),
               macroWeighted(7),
               weightingPower(42.),
               component_name(component::Name::SCALAR),
               component(component::Name::SCALAR, values, *this) {}

        double get_weighting_power(){
            return weightingPower;
        }
        int get_macro_weighted(){
            return weightingPower;
        }
        component::Name get_component_name() const{
            return component_name;
        }
        Component_current& get_component(){
            return component;
        }

    };

}//SOA

namespace record{
namespace traits{

    template<class T_Value_type>

    struct Type<component::Name::SCALAR, SOA::Scalar_record<T_Value_type>>
    {
       using type = typename SOA::Scalar_record<T_Value_type>::Component;
    };
} //namespace traits

    template<class T_Value_type>
    struct Getting_value<component::Name::SCALAR, SOA::Scalar_record<T_Value_type>>
    {
    public:
        typename traits::Type<component::Name::SCALAR, SOA::Scalar_record<T_Value_type>>::type
            operator() (SOA::Scalar_record<T_Value_type>& record)
        {
            auto current_value = record.component;
            return current_value;
        }

    };

    template<class T_Value_type>
    HINLINE std::vector<component::Name> get_names(const SOA::Scalar_record<T_Value_type>& record)
    {
        std::vector<component::Name> component_names = {record.get_component_name()};
        return component_names;

    }

    template<class T_Value_type>
    struct Geting_weighting_power<SOA::Scalar_record<T_Value_type>>
    {
    public:
      double operator() (SOA::Scalar_record<T_Value_type>& record)
      {
          double weighting_power = record.get_weighting_power();
          return weighting_power;
      }

    };


    template<class T_Scalar_component>
    struct Geting_macro_weighted<SOA::Scalar_record<T_Scalar_component>>
    {
    public:
      double operator() (SOA::Scalar_record<T_Scalar_component>&& record)
      {
          double weighting_power = record.get_macro_weighted();
          return weighting_power;
      }

    };

} //namespace record
} //reduction_library

