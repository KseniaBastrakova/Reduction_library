#pragma once

#include "reduction_library/component/Name.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/HDNLINE.hpp"

namespace reduction_library{
namespace component{

    template<component::Name Component_name, record::Name Record_name, typename T_particle, typename T_component>
    struct Setting_value;

    template<component::Name Component_name, record::Name Record_name, typename T_particle, typename T_dataset>
    HDNLINE void set(T_dataset value, T_particle& particle){
        Setting_value<Component_name, Record_name, T_particle, T_dataset> v_set_functor;
        v_set_functor.operator ()(value, particle);

    }

    template<component::Name Component_name, record::Name Record_name, typename T_particle>
    struct Getting_value;

    template<component::Name Component_name, record::Name Record_name, typename T_particle>
    HDNLINE auto get(T_particle& particle){
        Getting_value<Component_name, Record_name, T_particle> v_get_functor;
        return v_get_functor.operator() (particle);

    }

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
