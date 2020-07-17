#pragma once

#include "reduction_library/attribute/Scalar_records_names.hpp"

namespace reduction_library{
namespace attribute{
namespace traits{

    template<typename T_Particle, Scalar_records_names T_attribute>
    struct Type{
        using type = double;


    };

} //traits
} //attribute
} //reduction_library

