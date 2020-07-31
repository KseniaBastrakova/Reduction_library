#pragma once

#include "reduction_library/record/Name.hpp"

namespace reduction_library{
namespace particle_spicies{
namespace traits{

    template<record::Name Record_name, typename T_record>
    struct Type{
        using type = double;

    };

} //traits
} //particle_spicies
} //reduction_library
