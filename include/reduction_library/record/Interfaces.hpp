#pragma once

#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/record/Type.hpp"
#include "vector"

namespace reduction_library{
namespace record{

    template<typename T_record>
    struct Geting_weighting_power;

    template<typename T_record>
    double get_unit_dimension(T_record&& component)
    {
        Geting_weighting_power<T_record> ud_get_functor;
        return ud_get_functor.operator ()(component);
    }

    template<typename T_record>
    struct Geting_macro_weighted;

    template<typename T_record>
    double get_macro_weighted(T_record&& component)
    {
        Geting_macro_weighted<T_record> mw_get_functor;
        return mw_get_functor.operator ()(component);
    }

    template<component::Name name_component, typename T_record>
    HDNLINE typename traits::Type<name_component, T_record>::type get(T_record&& record);

    template<typename T_record>
    HDNLINE std::vector<component::Name> get_names(const T_record& record);


} // namespace record
} //namespace reduction_library

