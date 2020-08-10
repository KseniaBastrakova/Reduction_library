#pragma once

#include "reduction_library/component/Name.hpp"

namespace reduction_library{
namespace record{
namespace traits{

template<component::Name T_component_name, typename T_Record>
    struct Type;

} //traits

template<component::Name T_component_name, typename T_Record>
struct Type{
    using type = typename record::traits::Type<T_component_name, T_Record>::type;

};
} //record
} //reduction_library
