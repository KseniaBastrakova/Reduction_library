#pragma once

#include <tuple>
#include <alpaka/alpaka.hpp>
#include "reduction_library/SOA/Particle_species_traits.hpp"

namespace reduction_library{
namespace particle_species{

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
}
}
