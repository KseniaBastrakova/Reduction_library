#pragma once

#include "vector"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/particle_species/Type.hpp"

namespace reduction_library{
namespace particle_species{

    template<record::Name T_record_name, typename T_Particle_species>
    struct Getting_value;

    template<record::Name T_record_name, typename T_Particle_species>
    HDNLINE typename traits::Type<T_record_name, T_Particle_species>::type &
        get(T_Particle_species& particle_species)
    {
        Getting_value<T_record_name, T_Particle_species> v_get_functor;
        return v_get_functor.operator() (particle_species);
    }

    template<typename T_particle_species>
    HDNLINE std::vector<record::Name> get_names(const T_particle_species& record);


} // namespace particle_species
} // namespace reduction_library
