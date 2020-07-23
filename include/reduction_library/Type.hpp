#pragma once

#include "reduction_library/Traits.hpp"

namespace reduction_library{
namespace attribute{

    template<typename T_Particle, Scalar_records_names T_scalar_record>
    using Type = typename traits::Type<T_Particle, T_scalar_record>::type;

} //attribute
} //reduction_library

