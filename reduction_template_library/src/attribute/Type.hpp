#pragma once

#include "../Attributes_types.hpp"
#include "Traits.hpp"

namespace reduction_library{
namespace attribute{

template<typename T_Particle, Attribute T_attribute>
using Type = typename traits::Type<T_Particle, T_attribute>::type;



    }
}
