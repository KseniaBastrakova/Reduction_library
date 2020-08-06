#pragma once

#include "reduction_library/component/Type.hpp"
#include "reduction_library/HDNLINE.hpp"

namespace reduction_library{
namespace component{

    template<component::Name T_component, typename T_particle>
    struct Setting_value;

    template<component::Name T_component, typename T_particle>
    HDNLINE void set(typename traits::Type<T_component>::type value, T_particle& particle){
        Setting_value<T_component, T_particle> v_set_functor;
        v_set_functor.operator ()(value, particle);

    }

    template<component::Name T_component, typename T_particle>
    struct Getting_value;

    template<component::Name T_component, typename T_particle>
    HDNLINE typename traits::Type<T_component>::type get(T_particle& particle){
        Getting_value<T_component, T_particle> v_get_functor;
        return v_get_functor.operator() (particle);

    }

	template<typename T_component>
	struct Geting_unit_SI;

    template<typename T_component>
    double get_unit_SI(T_component& component)
    {
    	Geting_unit_SI<T_component> si_get_functor;
		return si_get_functor.operator ()(component);
    }

}//component
}//reduction_library
