#pragma once

#include "reduction_library/record/Traits.hpp"
#include "reduction_library/component/Name.hpp"


namespace reduction_library{
namespace record{
    template<component::Name Component_name, typename T_record>
    using Type = typename traits::Type<Component_name, T_record>::type;

}//component
}//reduction_library
