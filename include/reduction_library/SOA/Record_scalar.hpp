#pragma once

#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Component.hpp"
#include "reduction_library/SOA/Dataset.hpp"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/HINLINE.hpp"

namespace reduction_library{
namespace SOA{

    template<typename T_Value_type>
    struct Scalar_record{
    public:
        using This = Scalar_record<T_Value_type>;
        using Component_current = Component<T_Value_type>;

    private:
        int macro_weighted;
        double weighting_power;
       // component::Name component_name;
        Component_current component;

    public:
        Scalar_record():
               macro_weighted(7),
               weighting_power(42.)
              // component_name(component::Name::scalar)
            {}
        Scalar_record(Dataset<T_Value_type> values):
               macro_weighted(7),
               weighting_power(42.),
               component(values) {}

        double get_weighting_power(){
            return weighting_power;
        }
        int get_macro_weighted(){
            return weighting_power;
        }
     //   void set_component_name(component::Name new_component_name){
     //       component_name = new_component_name;
      //  }

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
       using type = typename SOA::Scalar_record<T_Value_type>::Component_current;
    };

    template<class T_Value_type>
    struct Component_names<SOA::Scalar_record<T_Value_type>>
    {
        using type = typename std::tuple<component::Name::SCALAR>;
    };


} //namespace traits


    template<class T_Value_type >
    SOA::Scalar_record<T_Value_type> make_scalar_record(SOA::Component<T_Value_type> input_component)
    {
        SOA::Scalar_record<T_Value_type> scalar_record;
        scalar_record.set_component(input_component);
      //  scalar_record.set_component_name(component::Name::scalar);
        return scalar_record;
    }

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

  //  template<class T_Value_type>
  //  HINLINE std::vector<component::Name> get_names(const SOA::Scalar_record<T_Value_type>& record)
  //  {
   //     std::vector<component::Name> component_names = {record.get_component_name()};
   //     return component_names;

  //  }

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

