#pragma once

#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Component.hpp"
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
        using Component_current = Component<T_Value_type>;

    private:
        int macro_weighted;
        double weighting_power;
        component::Name component_name;
        record::Name record_name;
        Component_current component;

    public:
        Scalar_record():
               macro_weighted(7),
               weighting_power(42.),
               component_name(component::Name::SCALAR){}
        Scalar_record(record::Name record_name, Dataset<T_Value_type> values):
               record_name(record_name),
               macro_weighted(7),
               weighting_power(42.),
               component_name(component::Name::SCALAR),
               component(component::Name::SCALAR, values) {}

        double get_weighting_power(){
            return weighting_power;
        }
        int get_macro_weighted(){
            return weighting_power;
        }
        component::Name get_component_name() const{
            return component_name;
        }

        Component_current& get_component(){
            return component;
        }
        void set_component(Component_current new_component){
            component = new_component;
        }

        void print_component(){
            component.print_dataset();
        }

    };

}//SOA

namespace record{
namespace traits{

    template<class T_Value_type>

    struct Type<component::Name::SCALAR, SOA::Scalar_record<T_Value_type>>
    {
       using type = typename SOA::Scalar_record<T_Value_type>::Component_current; // int; //SOA::Component<T_Value_type>; //
    };
} //namespace traits

    template<class T_Value_type>
    struct Getting_value<component::Name::SCALAR, SOA::Scalar_record<T_Value_type>>
    {
    public:
        typename traits::Type<component::Name::SCALAR, SOA::Scalar_record<T_Value_type>>::type &
            operator() (SOA::Scalar_record<T_Value_type>& record)
        {
            auto& current_component = record.get_component();
            return current_component;
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
      double operator() (SOA::Scalar_record<T_Value_type>&& record)
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

