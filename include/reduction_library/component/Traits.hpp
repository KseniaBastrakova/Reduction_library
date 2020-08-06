#pragma once

#include "reduction_library/component/Name.hpp"
namespace reduction_library{
namespace component{
namespace traits{

    template<component::Name T_component>
    struct Type{
        using type = double;

    };

} //traits
} //component
} //reduction_library

