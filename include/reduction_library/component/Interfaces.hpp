#pragma once

#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/component/Type.hpp"
#include "reduction_library/HDNLINE.hpp"
#include <vector>

namespace reduction_library{
namespace component{

    template<typename T_component, typename T_particle>
    HDNLINE
	void set(T_component& component, traits::Type<T_component> value, T_particle& particle);

    template<typename T_component, typename T_particle>
    HDNLINE
    traits::Type<T_component> get(T_particle& particle);

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


