#pragma once

#include "reduction_library/SOA/Aplaka_Dataset.hpp"
#include <alpaka/alpaka.hpp>


namespace reduction_library{
namespace SOA{

template<typename Dataset, typename Acc>
struct Acc_dataset{
    using type = Dataset;
};

template<typename Acc, typename T_Value, typename Acc_new>
struct Acc_dataset<Aplaka_Dataset<Acc,T_Value>, Acc_new>{
    using type = Aplaka_Dataset<T_Value, Acc_new>;
};

template<typename Acc, typename T_Value, typename Acc_new>
using Acc_dataset_new = typename Acc_dataset<Aplaka_Dataset<Acc,T_Value>, Acc_new>::type;

} // namespace SOA
} // namespace reduction_library
