#pragma once

#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/particle_spicies/Type.hpp"
#include "vector"

namespace reduction_library{
namespace particle_spicies{

    template<record::Name name_record, typename T_particle_spicies>
    HDNLINE typename traits::Type<name_record, T_particle_spicies>::type get(T_particle_spicies&& record);

    template<typename T_particle_spicies>
    HDNLINE std::vector<record::Name> get_names(const T_particle_spicies& record);


} // namespace particle_spicies
} // namespace reduction_library
