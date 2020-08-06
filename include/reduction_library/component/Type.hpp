#pragma once

#include "reduction_library/component/Traits.hpp"


namespace reduction_library{
namespace component{
    template<component::Name T_component>
    using Type = typename traits::Type<T_component>::type;

}//component
}//reduction_library



