#pragma once

#include "reduction_library/component/Name.hpp"

namespace reduction_library{
namespace record{
namespace traits{

    template<component::Name Component_name, typename T_record>
    struct Type{
        using type = double;

    };

} //traits
} //record
} //reduction_library


