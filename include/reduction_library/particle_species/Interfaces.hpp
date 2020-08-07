#pragma once

#include "vector"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/particle_species/Type.hpp"

namespace reduction_library{
namespace particle_spicies{

    template<record::Name T_name_record, typename T_Particle_spicies>
    struct Getting_value;

    template<record::Name T_name_record, typename T_record>
    HDNLINE typename traits::Type<T_name_record, T_record> get(T_record& record){
        Getting_value<T_name_record, T_record> v_get_functor;
        return v_get_functor.operator() (record);

    }

    template<typename T_particle_spicies>
    HDNLINE std::vector<record::Name> get_names(const T_particle_spicies& record);


} // namespace particle_spicies
} // namespace reduction_library

