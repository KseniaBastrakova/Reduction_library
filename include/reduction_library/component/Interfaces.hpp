#pragma once

#include "reduction_library/component/Name.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/HDNLINE.hpp"

namespace reduction_library{
namespace component{

	template<typename T_component>
	struct Geting_unit_SI;

    template<typename T_component>
    HDNLINE double get_unit_SI(T_component& component)
    {
    	Geting_unit_SI<T_component> si_get_functor;
		return si_get_functor.operator ()(component);
    }

    template<typename T_component>
    struct Setting_unit_SI;

    template<typename T_component>
    HDNLINE void set_unit_SI(T_component& component, double unit_si)
    {
        Setting_unit_SI<T_component> si_set_functor;
        si_set_functor.operator ()(component, unit_si);
    }


}//namespace component
}//namespace reduction_library
