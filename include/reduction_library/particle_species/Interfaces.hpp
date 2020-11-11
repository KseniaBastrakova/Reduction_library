#pragma once

#include "vector"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/particle_species/Type.hpp"

namespace reduction_library{
namespace particle_species{

    template<typename T_record_name, typename T_Particle_Species>
    struct Getting_value;

    template<typename T_record_name, typename T_Particle_species>
    HDNLINE typename traits::Type<T_record_name, T_Particle_species>::type &
        get(T_Particle_species& particle_species)
    {
        Getting_value<T_record_name, T_Particle_species> v_get_functor;
        return v_get_functor.operator() (particle_species);
    }

    template<typename T_Particle_Species>
    struct Getiing_size;

    template<typename T_Particle_Species>
    HDNLINE double get_size(T_Particle_Species& particle_species)
    {
       Getiing_size<T_Particle_Species> size_get_functor;
       return size_get_functor.operator ()(particle_species);
    }

    template<typename T_Particle_Species>
    struct Getting_particle;

    template<typename T_Particle_Species>
    void get_particle(T_Particle_Species& particle_species, int idx)
    {
       Getting_particle<T_Particle_Species> getting_functor;
       getting_functor.operator ()(particle_species, idx);
    }

    template<typename T_Particle_Species>
    struct Deletting_particle;

    template<typename T_Particle_Species>
    void delete_particle(T_Particle_Species& particle_species, int idx)
    {
       Deletting_particle<T_Particle_Species> deleting_functor;
       deleting_functor.operator ()(particle_species, idx);
    }



} // namespace particle_species
} // namespace reduction_library
