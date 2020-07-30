#pragma once

#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/record/Type.hpp"

namespace reduction_library{
namespace record{

    template<typename T_record>
    struct Geting_unit_dimension;

    template<typename T_record>
    double get_unit_dimension(T_record&& component)
    {
        Geting_unit_dimension<T_record> ud_get_functor;
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

    template<typename T_record, component::Name name_component>
    HDNLINE typename traits::Type<name_component, T_record>::type get(T_record&& record);


} // namespace record
} //namespace reduction_library

