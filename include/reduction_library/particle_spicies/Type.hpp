#pragma once

#include "reduction_library/particle_spicies/Traits.hpp"
#include "reduction_library/record/Name.hpp"


namespace reduction_library{
namespace particle_spicies{
    template<record::Name Record_name, typename T_particle_spicies>
    using Type = typename traits::Type<Record_name, T_particle_spicies>::type;

}// particle_spicies
}// reduction_library
