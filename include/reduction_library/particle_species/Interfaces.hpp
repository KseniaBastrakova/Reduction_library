#pragma once

#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/particle_species/Type.hpp"

namespace reduction_library{
namespace particle_species{
/** particle species object interface
 * the idea of particle species interface, functions and attributes
 * based on openPMD component:
 * https://github.com/openPMD/openPMD-standard/blob/latest/STANDARD.md
 * and necessity for merging and tinning algorithms
 *
 * example of defining can be founded in SOA::Particle_species
 * This interface provides getting record,
 * getting species size, get particle by idx,
 * deleting particle by idx
*/

/** Functor for getting record for given particle species
 * \tparam T_Record_Name - mame of record (defined in /reduction_library/record/Name.hpp)
 * \tparam T_Particle_Species - type of input particle species
*/
template<typename T_Record_Name, typename T_Particle_Species>
struct Getting_value;

/** Host device function for getting record from given component
 * return record with type, defined in (reduction_library/particle_species/Type.hpp)
 * \tparam T_Record_Name - mame of record (defined in /reduction_library/record/Name.hpp)
 * \tparam T_Particle_Species - type of input particle species
*/
template<typename T_Record_Name, typename T_Particle_Species>
HDNLINE typename traits::Type<T_Record_Name, T_Particle_Species>::type &
    get(T_Particle_Species& particle_species)
{
    Getting_value<T_Record_Name, T_Particle_Species> v_get_functor;
    return v_get_functor.operator() (particle_species);
}

/** Functor for getting number of particles in  given particle species
 * \tparam T_Particle_Species - type of input particle species
*/
template<typename T_Particle_Species>
struct Getiing_size;

//-----------------------------------------------------------------------------
//! Host device function for getting number of particles in given component
template<typename T_Particle_Species>
HDNLINE int get_size(T_Particle_Species& particle_species)
{
   Getiing_size<T_Particle_Species> size_get_functor;
   return size_get_functor.operator ()(particle_species);
}

/** Functor for getting particle in given particle species
 * \tparam T_Particle_Species - type of input particle species
*/
template<typename T_Particle_Species>
struct Getting_particle;

//-----------------------------------------------------------------------------
//! Host device function for getting particle with given idx. Return type define in  Particle_Type interface
template<typename T_Particle_Species>
auto get_particle(T_Particle_Species& particle_species, int idx)
{
   Getting_particle<T_Particle_Species> getting_functor;
   getting_functor.operator ()(particle_species, idx);
}

/** Functor for deletting particle in given particle species
 * \tparam T_Particle_Species - type of input particle species
*/
template<typename T_Particle_Species>
struct Deletting_particle;

//-----------------------------------------------------------------------------
//! Host device function for deleting particle with given idx
template<typename T_Particle_Species>
void delete_particle(T_Particle_Species& particle_species, int idx)
{
   Deletting_particle<T_Particle_Species> deleting_functor;
   deleting_functor.operator ()(particle_species, idx);
}

} // namespace particle_species
} // namespace reduction_library
