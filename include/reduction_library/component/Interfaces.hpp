#pragma once

#include "reduction_library/HDNLINE.hpp"
#include <vector>

#include "reduction_library/component/Name.hpp"
#include "reduction_library/component/Traits.hpp"


namespace reduction_library{
namespace component{

	template<typename T_particle, Name T_component>
	HDNLINE void set_attribute(T_particle& particle, traits::Type<T_component> value);

    template<typename T_particle, Name T_component>
    HDNLINE traits::Type<T_component> get_attribute(T_particle& particle);

	template<Name T_component>
	class Geting_unit_SI;

    template<typename T_particles, Name T_component>
    double get_unit_SI(T_particles particles){

    	Geting_unit_SI<T_component> si_get_functor;
		return si_get_functor.operator ()(particles);
    }

}//component
}//reduction_library


