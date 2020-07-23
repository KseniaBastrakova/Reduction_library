#pragma once

#include "reduction_library/objects/record_component/Record_component_names.hpp"

namespace reduction_library{
namespace objects{
namespace record_component{
namespace traits{

    template<typename T_Particle, Record_component_names T_attribute>
    struct Type{
        using type = double;

    };

} //traits
} //record_component
} //objects
} //reduction_library

