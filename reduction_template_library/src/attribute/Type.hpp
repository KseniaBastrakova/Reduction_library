#pragma once

#include "Atributes_types.hpp"
#include "attribute/Traits.hpp"

namespace reduction_library{
namespace attribute{

template<typename T_Particle, Attribute T_attribute>
using Type = typename traits::Type<T_Particle, T_attribute>::type;



}
}
