#pragma once

#include <alpaka/alpaka.hpp>

#include "Alpaka_dataset.hpp"


namespace reduction_library{
namespace SOA{

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
struct Acc_dataset<T_Acc_New, Alpaka_dataset<T_Acc_Old, T_Value>>{
    using type = Alpaka_dataset<T_Acc_New, T_Value>;
};

template<typename Acc_new, typename T_Dataset>
using Acc_dataset_t = typename Acc_dataset<Acc_new, T_Dataset>::type;

} // namespace SOA
} // namespace reduction_library