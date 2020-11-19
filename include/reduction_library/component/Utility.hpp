#pragma once


#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/component/Concept.hpp"

/** @file
 *
 * This file implementes utilities for components.
 * They build on top of component concept interface and do not pose additional requirements on component types.
 */

namespace reduction_library{
namespace component{
   
    /// TODO: if you want a helper on top of ValueType, put it here, not in that file

    /** Get conversion unit of the given component to SI
     *
     * \tparam T_Component component type
     * /// TODO: other things are optional, and for such simple functions not necessary
     */
    template< typename T_Component >
    HDNLINE double get_unit_SI( T_Component & component )
    {
        Geting_unit_SI< T_Component > si_get_functor;
        return si_get_functor.operator()( component );
    }
    
    /** Set conversion unit of the given component to SI to the given value
     *
     * \tparam T_Component component type
     * /// TODO: other things are optional, and for such simple functions not necessary
     */
    template<typename T_Component>
    HDNLINE void set_unit_SI( T_Component & component, double unit_si )
    {
        Setting_unit_SI<T_Component> si_set_functor;
        si_set_functor.operator ()(component, unit_si);
    }

} // namespace component
} // namespace reduction_library
