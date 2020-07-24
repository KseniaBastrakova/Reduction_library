#pragma once

#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/component/Type.hpp"
#include <vector>

namespace reduction_library{
namespace component{

	template<typename T_component>
	void set_attribute(T_component& component, traits::Type<T_component> value);

    template<typename T_component>
    traits::Type<T_component> get_attribute(T_component& component);

	template<typename T_component>
	struct Geting_unit_SI;

    template<typename T_component>
    double get_unit_SI(T_component&& component)
    {

    	Geting_unit_SI<T_component> si_get_functor;
		return si_get_functor.operator ()(component);
    }

}//component
}//reduction_library


