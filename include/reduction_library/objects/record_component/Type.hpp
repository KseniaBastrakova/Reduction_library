#pragma once

#include "reduction_library/objects/record_component/Record_component_names.hpp"

namespace reduction_library{
namespace objects{
namespace record_component{

    template<typename T_Particle, Record_component_names T_scalar_record>
    using Type = typename traits::Type<T_Particle, T_scalar_record>::type;

}//record_component
}//objects
}//reduction_library
