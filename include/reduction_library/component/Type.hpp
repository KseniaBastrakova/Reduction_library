#pragma once

#include "reduction_library/component/Traits.hpp"


namespace reduction_library{
namespace component{
    template<typename T_component>
    using Type = typename traits::Type<T_component>::type;

}//component
}//reduction_library



