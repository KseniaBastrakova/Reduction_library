/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

/** @file
 *
 * This file implements utilities for records
 * They build on top of record concept interface and do not pose additional requirements on records types.
 */

#include "reduction_library/component/Name.hpp"

namespace reduction_library{
namespace record{
namespace traits{

/** Record object traits
 *  represent types for record's attributes
*/


/** Main
 *  represent types for components's attributes
*/
template<typename T_Component_Name, typename T_Record>
    struct Type;

template<typename T_Record>
    struct Component_names;

} //traits

template<typename T_component_name, typename T_Record>
struct Type{
    using type = typename record::traits::Type<T_component_name, T_Record>::type;

};

template<typename T_Record>
struct Component_names{
    using type = typename record::traits::Component_names<T_Record>::type;

};
} //record
} //reduction_library
