/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "reduction_library/SOA/Record.hpp"
#include "reduction_library/helpers/Type_list.hpp"
#include "reduction_library/SOA/Component_traits.hpp"

namespace reduction_library{
namespace SOA{

/** Derive a new record type based on the given record type using alpaka-datasets
 *
 * For record, not using alpaka datasets, return the given record type.
 * \tparam T_Acc_New alpaka accelerator type
 * \tparam T_Record record type, follows concept Record
 */
template<typename T_Acc_New, typename T_Record>
struct Acc_record{
    using type = T_Record;
};

/** Partal specialization for records based on SOA::Record
 *
 *  return type of Record based using alpaka datasets type, with new accelerator
 *
 * \tparam T_Acc_New new Alpaka accelerator type
 * \tparam T_Record type of old record
 */
template<typename T_Acc_New, typename T_Names_list, typename T_Component_type_list>
struct Acc_record<T_Acc_New, Record<T_Names_list, T_Component_type_list>>{
    template<typename T_Component>
    using Transform_component = Acc_component_t<T_Acc_New, T_Component>;
    using New_components_type = typename helpers::apply_meta_t<Transform_component, T_Component_type_list>;
    using type = Record<T_Names_list, New_components_type>;
};

template<typename T_Acc_New, typename T_Record>
using Acc_record_t = typename Acc_record<T_Acc_New, T_Record>::type;

} // namespace SOA
} // namespace reduction_library
