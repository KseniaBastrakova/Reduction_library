/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <alpaka/alpaka.hpp>

#include "Alpaka_dataset.hpp"


namespace reduction_library{
namespace dataset{
namespace traits{

/** Derive a new dataset type based on the given dataset type using the given alpaka accelerator type
 *
 * For non-alpaka datasets, return the given dataset type.
 *
 * \tparam T_Dataset dataset type, follows concept SOA::Dataset
 * \tparam T_Acc alpaka accelerator type
 */
template<typename T_Acc_New, typename T_Dataset>
struct Acc_dataset{
    using type = T_Dataset;
};

/** Partal specialization for Alpaka datasets
 *
 *  return Alpaka dataset type with new accelerator
 *
 * \tparam T_Acc_Old current Alpaka accelerator type
 * \tparam T_Acc_New new Alpaka accelerator type
 * \tparam T_Value type of values in Alpaka dataset
 */
template<typename T_Acc_New, typename T_Acc_Old, typename T_Value>
struct Acc_dataset<T_Acc_New, SOA::Alpaka_dataset<T_Acc_Old, T_Value>>{
    using type = SOA::Alpaka_dataset<T_Acc_New, T_Value>;
};

template<typename Acc_new, typename T_Dataset>
using Acc_dataset_t = typename Acc_dataset<Acc_new, T_Dataset>::type;

} // namespace SOA
}
} // namespace reduction_library
