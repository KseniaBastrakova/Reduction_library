#pragma once

#include <tuple>
#include "reduction_library/SOA/Record_getters.hpp"
#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Component.hpp"
#include "reduction_library/SOA/Dataset.hpp"
#include "reduction_library/helpers/Tuple_idx_getters.hpp"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/HINLINE.hpp"

namespace reduction_library{
namespace SOA{

    template<typename T_X_Value_type, typename T_Y_Value_type, typename T_Z_Value_type>
    struct Record_3d{
    public:
        using This = Record_3d<T_X_Value_type, T_Y_Value_type, T_Z_Value_type>;
        using Components = std::tuple<Component<T_X_Value_type>, Component<T_X_Value_type>, Component<T_X_Value_type>>;
        using Names = std::tuple<component::Name::X, component::Name::Y, component::Name::Z>;

    private:
        int macroWeighted;
        double weightingPower;
        Names names;
        Components components;
        record::unit_dimension_type unit_dimension;

    public:
        Record_3d():
                  macroWeighted(7),
                  weightingPower(42.),
                  unit_dimension(unit_dimension){}

        double get_weighting_power(){
            return weightingPower;
        }
        int get_macro_weighted(){
            return weightingPower;
        }
        record::unit_dimension_type get_unit_dimension() const{
            return unit_dimension;
        }
        Components& get_components(){
            return components;
        }

    };


}//SOA


namespace record{
namespace traits{

    template<class T_component_name, class T_X_component, class T_Y_component, class T_Z_component>
    struct Type< T_component_name, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
        using Names = typename SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>::Names;

        using type = typename std::tuple_element_t<
                helpers::Index<T_component_name, Names>::value,
                typename SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>::Components
               >;
    };


} //namespace traits

    template<class T_X_component, class T_Y_component, class T_Z_component>
    SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>
        make_momentum_record(SOA::Component<T_X_component> x_component,
                           SOA::Component<T_Y_component> y_component,
                           SOA::Component<T_Z_component> z_component)
    {
        using Record_type = SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>;
        Record_type record_3d;

        SOA::Component<T_X_component> value_x(x_component.get_dataset());
        get<component::Name::X, Record_type>(record_3d) = value_x;

        SOA::Component<T_Y_component> value_y(y_component.get_dataset());
        get<component::Name::Y, Record_type>(record_3d) = value_y;

        SOA::Component<T_Z_component> value_z(z_component.get_dataset());
        get<component::Name::Z, Record_type>(record_3d) = value_z;

        return record_3d;
    }

    template<class T_component_name, class T_X_component, class T_Y_component, class T_Z_component>
    struct Getting_value<T_component_name, SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
    public:
        typename traits::Type<T_component_name,
        SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>::type &
            operator() (SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>& record)
        {
            using Names = typename SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>::Names;
            constexpr auto idx = helpers::Index<T_component_name, Names>::value;
            return std::get< idx >( record.get_components() );
        }

    };

    template<typename T_X_component, typename T_Y_component, typename T_Z_component>
    struct Geting_weighting_power<SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
    public:
      double operator() (SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>& record)
      {
          return record.get_weighting_power();
      }

    };


    template<typename T_X_component, typename T_Y_component, typename T_Z_component>
    struct Geting_macro_weighted<SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
    public:
      double operator() (SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>&& record)
      {
          return record.get_macro_weighted();
      }

    };


    template<typename T_X_component, typename T_Y_component, typename T_Z_component>
    struct Geting_unit_dimension<SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>>
    {
    public:
      unit_dimension_type operator() (SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>& record)
      {
          return record.get_unit_dimension();
      }

    };

} // namespace record

}// reduction_library

