#pragma once

#include "reduction_library/record/Name.hpp"

namespace reduction_library{
namespace particle_species{
namespace traits{

template<typename T_record_name, typename T_Particle_species>
    struct Type;

} // namespace traits

template<typename T_record_name, typename T_Particle_species>
struct Type{
    using type = typename particle_species::traits::Type<T_record_name, T_Particle_species>::type;

};
} // namespace particle_species
} // namespace reduction_library
