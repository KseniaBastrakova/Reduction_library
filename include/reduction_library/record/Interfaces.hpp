#pragma once

#include <vector>
#include <array>

#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/record/Type.hpp"

namespace reduction_library{
namespace record{

    using unit_dimension_type = std::array<int, 7>;

    template<typename T_record>
    struct Geting_weighting_power;

    template<typename T_record>
    double get_weighting_power(T_record& record)
    {
        Geting_weighting_power<T_record> wp_get_functor;
        return wp_get_functor.operator ()(record);
    }

    template<typename T_record>
    struct Geting_macro_weighted;

    template<typename T_record>
    double get_macro_weighted(T_record&& record)
    {
        Geting_macro_weighted<T_record> mw_get_functor;
        return mw_get_functor.operator ()(std::move(record));
    }

    template<typename T_record>
    struct Geting_unit_dimension;

    template<typename T_record>
    unit_dimension_type get_unit_dimension(T_record& record)
    {
        Geting_unit_dimension<T_record> ud_get_functor;
        return ud_get_functor.operator ()(record);
    }

    template<typename T_name_component, typename T_record>
    struct Getting_value;

    template<typename T_name_component, typename T_record>
    HDNLINE typename traits::Type<T_name_component, T_record>::type & get(T_record& record){
        Getting_value<T_name_component, T_record> v_get_functor;
        return v_get_functor.operator() (record);

    }

    template<typename T_record>
    HDNLINE std::vector<component::Name> get_names(const T_record& record);


} // namespace record
} //namespace reduction_library
