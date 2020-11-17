#pragma once

#include "reduction_library/HDNLINE.hpp"

namespace reduction_library{
namespace component{
/** Component object interface
 * the idea of component interface, functions and attributes
 * based on openPMD component:
 * https://github.com/openPMD/openPMD-standard/blob/latest/STANDARD.md
 *
 * This interface provides setting and getting unitSI for given component
*/

/** Functor for getting unit SI for given template component
 *  return value of unit si attribute for given component
 * \tparam T_Component component type
*/
template<typename T_Component>
struct Geting_unit_SI;

//-----------------------------------------------------------------------------
//! Host device function for getting unit si for given component
template<typename T_Component>
HDNLINE double get_unit_SI(T_Component& component)
{
    Geting_unit_SI<T_Component> si_get_functor;
    return si_get_functor.operator ()(component);
}

/** Functor for setting unit SI for given template component
 *  set given unit si as attribute for given component
 * \tparam T_Component component type
*/
template<typename T_Component>
struct Setting_unit_SI;

//---------------------------------------------------------------------------------------
//! Host device function for setting unit si for given component, unit_si -- new si value
template<typename T_Component>
HDNLINE void set_unit_SI(T_Component& component, double unit_si)
{
    Setting_unit_SI<T_Component> si_set_functor;
    si_set_functor.operator ()(component, unit_si);
}

}//namespace component
}//namespace reduction_library
