/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/component/Concept.hpp"

/** @file
 *
 * This file implements utilities for components.
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
        Getting_unit_SI< T_Component > si_get_functor;
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
