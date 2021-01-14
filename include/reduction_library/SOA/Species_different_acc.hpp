#pragma once

#include <tuple>
#include <alpaka/alpaka.hpp>
#include "reduction_library/SOA/Particle_species_traits.hpp"

namespace reduction_library{
namespace particle_species{
/** @file
 * Making new particle species, that contain soft copy
 * of existing particle species and have different Alpaka accelarator
 * using it for copying data from host to device, for example
 *
 */

/** Get a new particle species from old one, but with different input accelerator
 *
 *  returns soft copy of input particle species, but with new accelerator
 *
 * \tparam T_Acc_New new alpaka accelerator type
 * \tparam T_Names_List type list of records names, that connected with records collection
 * \tparam T_Record_Type_List type list of records collection, that contains in species
 * \tparam particle_species particle species with old accelerator
 */

template<typename T_Acc_New, typename T_Names_List, typename T_Record_Type_List>
struct Make_different_acc<T_Acc_New, SOA::Particle_species<T_Names_List, T_Record_Type_List>>
{
public:
   ALPAKA_FN_HOST_ACC typename Acc_species<T_Acc_New, SOA::Particle_species<T_Names_List, T_Record_Type_List>>::type
       operator() (SOA::Particle_species<T_Names_List, T_Record_Type_List>& particle_species)
   {
       using Particle_species_new_acc = traits::Acc_species_t<T_Acc_New, T_Names_List, T_Record_Type_List>;
       Particle_species_new_acc particle_species_acc_new(particle_species);
       return particle_species_acc_new;
   }

};
} // namespace particle_species
} // namespace reduction_library
