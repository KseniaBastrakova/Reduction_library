#pragma once

#pragma once

#include <tuple>
#include "reduction_library/helpers/Type_list.hpp"
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

template<typename T_Names_List, typename T_Component_Type_List>
struct Record{
public:
    using This = Record<T_Names_List, T_Component_Type_List>;
    using Components = T_Component_Type_List;
    using Names = T_Names_List;

private:
    int macroWeighted;
    double weightingPower;
    Names names;
   // Components components;
    record::unit_dimension_type unit_dimension;
public:
    Components components;
    Record(const Record& record):
        components(record.components),
        macroWeighted(record.get_macro_weighted()),
        weightingPower(record.get_weighting_power()),
        unit_dimension(record.get_unit_dimension()){}

    template<typename T_Another_Names_List, typename T_Another_Component_Type_List>
    Record(const Record<T_Another_Names_List, T_Another_Component_Type_List>& record):
        components(record.components),
        macroWeighted(record.get_macro_weighted()),
        weightingPower(record.get_weighting_power()),
        unit_dimension(record.get_unit_dimension()){}

    Record(T_Component_Type_List components):
        components(components),
        macroWeighted(7),
        weightingPower(42.),
        unit_dimension(unit_dimension){}

    double get_weighting_power() const
    {
        return weightingPower;
    }
    int get_macro_weighted() const
    {
        return weightingPower;
    }
    record::unit_dimension_type get_unit_dimension() const
    {
        return unit_dimension;
    }
    Components& get_components()
    {
        return components;
    }
    std::size_t get_size()
    {
        auto component = std::get< 0 >( components );
        return component.get_size();
    }

};

}//SOA


namespace record{
namespace traits{

    template<class T_component_name, typename T_Names_list, typename T_Component_Type_List>
    struct Type<T_component_name, SOA::Record<T_Names_list, T_Component_Type_List>>
    {
        using Record = SOA::Record<T_Names_list, T_Component_Type_List>;
        using Names = typename Record::Names;
        using Components = typename Record::Components;

        using type = typename std::tuple_element_t<
                helpers::Index<T_component_name, Names>::value,
                Components
               >;
    };
} //namespace traits


    // single type
    template<typename T_Component_type>
    using Record_scalar = SOA::Record<helpers::Type_list<component::Name::SCALAR >, helpers::Type_list< T_Component_type>>;

    // 3d
    template<typename T_X_component, typename T_Y_component, typename T_Z_component>
    using Record_XYZ = SOA::Record<helpers::Type_list<component::Name::X, component::Name::Y, component::Name::Z>,
            helpers::Type_list<T_X_component, T_Y_component, T_Z_component>>;

    // 2d
    template<typename T_X_component, typename T_Y_component>
    using Record_XY = SOA::Record<helpers::Type_list<component::Name::X, component::Name::Y>,
            helpers::Type_list<T_X_component, T_Y_component>>;



    template<class T_component_name, typename T_Names_list, typename T_Component_Type_List>
    struct Getting_value<T_component_name, SOA::Record<T_Names_list, T_Component_Type_List>>
    {
    public:
        typename traits::Type<T_component_name, SOA::Record<T_Names_list, T_Component_Type_List>>::type &
            operator() (SOA::Record<T_Names_list, T_Component_Type_List>& record)
        {
            using Record = SOA::Record<T_Names_list, T_Component_Type_List>;
            using Names = typename Record::Names;
            constexpr auto idx = helpers::Index<T_component_name, Names>::value;
            return std::get< idx >( record.get_components() );
        }

    };

    template<typename T_Names_list, typename T_Component_type_list>
    struct Geting_weighting_power<SOA::Record<T_Names_list, T_Component_type_list>>
    {
    public:
      double operator() (SOA::Record<T_Names_list, T_Component_type_list>& record)
      {
          return record.get_weighting_power();
      }

    };


    template<typename T_Names_list, typename T_Component_type_list>
    struct Geting_macro_weighted<SOA::Record<T_Names_list, T_Component_type_list>>
    {
    public:
      double operator() (SOA::Record<T_Names_list, T_Component_type_list>&& record)
      {
          return record.get_macro_weighted();
      }

    };


    template<typename T_Names_list, typename T_Component_type_list>
    struct Geting_unit_dimension<SOA::Record<T_Names_list, T_Component_type_list>>
    {
    public:
      unit_dimension_type operator() (SOA::Record<T_Names_list, T_Component_type_list>& record)
      {
          return record.get_unit_dimension();
      }

    };


    template<typename ... T_Names, typename ... T_Component_types>
    auto make_record(T_Component_types& ...  components)
    {
        using Names = helpers::Type_list< T_Names ... >;
        using Component_types = helpers::Type_list<T_Component_types ... >;
        using Record = SOA::Record< Names, Component_types>;
        Component_types input_components(components...);
        Record record(input_components);
        return record;
    }


    template<class T_Scalar_component>
    Record_scalar<T_Scalar_component> make_record_scalar(T_Scalar_component scalar_component)
    {
        auto scalar_record = make_record<component::Name::SCALAR>(scalar_component);
        return scalar_record;
    }

    template<class T_X_component, class T_Y_component, class T_Z_component>
    Record_XYZ<T_X_component, T_Y_component, T_Z_component> make_record_XYZ(T_X_component x_component,
                                                                            T_Y_component y_component,
                                                                            T_Z_component z_component)
    {
        auto result_3d_record = make_record<component::Name::X,
                component::Name::Y, component::Name::Z>(x_component, y_component, z_component);
        return result_3d_record;
    }

    template<class T_X_component, class T_Y_component>
    Record_XY<T_X_component, T_Y_component> make_record_XY(T_X_component x_component,
                                                           T_Y_component y_component)
    {
        auto result_2d_record = make_record<component::Name::X,
                component::Name::Y>(x_component, y_component);
        return result_2d_record;
    }


} // namespace record

}// reduction_library

