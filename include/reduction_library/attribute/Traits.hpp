#pragma once

#include "reduction_library/attribute/Attributes_types.hpp"

namespace reduction_library{
namespace attribute{
namespace traits{

    template<typename T_Particle, Attribute T_attribute>
    struct Type{
        using type = double;


    };

} //traits
} //attribute
} //reduction_library

