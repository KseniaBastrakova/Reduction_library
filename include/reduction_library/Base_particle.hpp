#pragma once

#include "reduction_library/component/Name.hpp"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/record/Name.hpp"

namespace reduction_library{
namespace particle{

    template<typename Component_name, typename Record_name, typename T_particle>
    struct Getting_value;

    template<typename Component_name, typename Record_name, typename T_particle>
    HDNLINE auto get(T_particle& particle){
        Getting_value<Component_name, Record_name, T_particle> v_get_functor;
        return v_get_functor.operator() (particle);
    }

    template<typename Component_name, typename Record_name, typename T_particle, typename T_dataset>
    struct Setting_value;

    template<typename Component_name, typename Record_name, typename T_particle, typename T_dataset>
    HDNLINE void set(T_dataset value, T_particle& particle){
        Setting_value<Component_name, Record_name, T_particle, T_dataset> v_set_functor;
        v_set_functor.operator ()(value, particle);

}

} // namespace particle
} //namespace reduction_library
