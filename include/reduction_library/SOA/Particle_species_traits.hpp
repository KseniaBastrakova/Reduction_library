/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "reduction_library/helpers/Type_list.hpp"
#include "reduction_library/SOA/Particle_species.hpp"
#include "reduction_library/SOA/Record_traits.hpp"

namespace reduction_library{
namespace SOA{

/** Derive a new species type based on the given species type using alpaka-datasets
 *
 * For species, not using alpaka datasets, return the given species type.
 * \tparam T_Acc_New alpaka accelerator type
 * \tparam T_Particle_Species, follows concept species
 */
template<typename T_Acc_New, typename T_Particle_Species>
struct Acc_species{
    using type = T_Particle_Species;
};

/** Partal specialization for species based on SOA::Record
*
*  return type of species based using alpaka datasets type, with new accelerator
*
* \tparam T_Acc_New new Alpaka accelerator type
* \tparam T_Names_List typelist of record's names
* \tparam T_Record_Type_List typelist of record's types
*/
template<typename T_Acc_New, typename T_Names_List, typename T_Record_Type_List>
struct Acc_species<T_Acc_New, Particle_species<T_Names_List, T_Record_Type_List>>{
    template<typename T_Record>
    using Transform_record = Acc_record_t<T_Acc_New, T_Record>;
    using New_records_type = typename helpers::apply_meta_t<Transform_record, T_Record_Type_List>;
    using type = Particle_species<T_Names_List, New_records_type>;
};

template<typename T_Acc_New, typename T_Names_List, typename T_Record_type_list>
using Acc_species_t = typename Acc_species<T_Acc_New, Particle_species<T_Names_List, T_Record_type_list>>::type;

} // namespace SOA
} // namespace reduction_library
