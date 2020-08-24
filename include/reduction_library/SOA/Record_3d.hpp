#pragma once

#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Component.hpp"
#include "reduction_library/SOA/Dataset.hpp"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/HINLINE.hpp"

namespace reduction_library{
namespace SOA{

    template<typename T_X_Value_type, typename T_Y_Value_type, typename T_Z_Value_type>
    struct Record_3d{
        using This = Record_3d<T_X_Value_type, T_Y_Value_type, T_Z_Value_type>;
        using Component_X = Component<T_X_Value_type>;
        using Component_Y = Component<T_Y_Value_type>;
        using Component_Z = Component<T_Z_Value_type>;

    private:
        int macroWeighted;
        double weightingPower;
     //   std::vector<component::Name> component_names;
        Component_X x_component;
        Component_Y y_component;
        Component_Z z_component;
        record::unit_dimension_type unit_dimension;

    public:
        Record_3d():
                  macroWeighted(7),
                  weightingPower(42.),
                  unit_dimension(unit_dimension){
              //    component_names.push_back(component::Name::x)
        }

        double get_weighting_power(){
            return weightingPower;
        }
        int get_macro_weighted(){
            return weightingPower;
        }
      //  std::vector<component::Name> get_component_names() const{
    //        return component_names;
     //   }
        record::unit_dimension_type get_unit_dimension() const{
            return unit_dimension;
        }

        // probaly, needs to be deleted:

        Component_X& getting_x_component(){
            return x_component;
        }

        Component_Y& getting_y_component(){
            return y_component;
        }

        Component_Z& getting_z_component(){
            return z_component;
        }
    };

}//SOA

//  typename SOA::Scalar_record<T_Value_type>::Component_current;
namespace record{
namespace traits{

    template<class T_X_component, class T_Y_component, class T_Z_component>
    struct Type<component::Name::X, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
       using type = typename SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>::Component_X;
    };

    template<class T_X_component, class T_Y_component, class T_Z_component>
    struct Type<component::Name::Y, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
       using type = typename SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>::Component_Y;
    };

    template<class T_X_component, class T_Y_component, class T_Z_component>
    struct Type<component::Name::Z, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
       using type = typename SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>::Component_Z;
    };

} //namespace traits

    template<class T_X_component, class T_Y_component, class T_Z_component>
    SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>
        make_momentum_record(SOA::Component<T_X_component> x_component,
                           SOA::Component<T_X_component> y_component,
                           SOA::Component<T_X_component> z_component)
    {
        using Record_type = SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>;
        SOA::Record_3d<T_X_component, T_Y_component, T_Z_component> scalar_record();

        auto& value_x = get<component::Name::X, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>(scalar_record);
        value_x.set_dataset(x_component.get_dataset());
     //   value_x.set_name(x_component.get_name());

        auto& value_y = get<component::Name::Y, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>(scalar_record);
        value_y.set_dataset(y_component.get_dataset());
      //  value_y.set_name(y_component.get_name());

        auto& value_z = get<component::Name::Z, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>(scalar_record);
        value_z.set_dataset(z_component.get_dataset());
      //  value_z.set_name(z_component.get_name());

        return scalar_record;
    }

    template<class T_X_component, class T_Y_component, class T_Z_component>
    HDNLINE std::vector<component::Name> get_names(const SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>& record)
    {
        return record.get_component_names();

    }

    template<class T_X_component, class T_Y_component, class T_Z_component>
    struct Getting_value<component::Name::X, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
    public:
        typename traits::Type<component::Name::X,
        SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>::type &
            operator() (SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>& record)
        {
            return record.getting_x_component();
        }

    };

    template<class T_X_component, class T_Y_component, class T_Z_component>
    struct Getting_value<component::Name::Y, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
    public:
        typename traits::Type<component::Name::Y,
        SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>::type &
            operator() (SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>& record)
        {
            return record.getting_y_component();
        }

    };

    template<class T_X_component, class T_Y_component, class T_Z_component>
    struct Getting_value<component::Name::Z, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
    public:
        typename traits::Type<component::Name::Z,
        SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>::type &
            operator() (SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>& record)
        {
            return record.getting_z_component();
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

