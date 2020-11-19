#pragma once

#include "reduction_library/record/Name.hpp"

namespace reduction_library{
namespace particle_species{
namespace traits{
    /** Particle species traits
     *
     *  Provide type for record by record name defined in reduction_library/record/Name.hpp
     *  Provide type for particle, that belongs particle species
     *  Provide type for storage of all records names, that belong to particle species
     *  sing for particle species getters
     *  Have to be defined for users types
     *  Example of defining can be found in reduction_library/SOA/Record_traits.hpp
     */

    /** Trait interface for getting record type for given particle species
     * by record name
     *
     * \tparam T_Record_Name name of record (defined in /reduction_library/record/Name.hpp)
     * \tparam T_Particle_Species type of input particle species
     */
    template<typename T_Record_Name, typename T_Particle_Species>
        struct Type;

    /** Trait interface for getting particle type for given particle species
     *
     * \tparam T_Particle_Species type of input particle species
     */
    template<typename T_Particle_Species>
        struct Particle_Type;

    /** Trait interface for type of storage of record names, contains in particle species
     *
     * \tparam T_Particle_Species type of input particle species
     */
    template<typename T_Particle_Species>
        struct Record_names;

} // namespace traits

    /** Trait interface for getting record typename for given particle species
     * by record name
     *
     * \tparam T_Record_Name name of record (defined in /reduction_library/record/Name.hpp)
     * \tparam T_Particle_Species type of input particle species
     */
    template<typename T_Record_Name, typename T_Particle_Species>
    struct Type{
        using type = typename particle_species::traits::Type<T_Record_Name, T_Particle_Species>::type;
    };

    /** Trait interface for getting particle typename for given particle species
     *
     * \tparam T_Particle_Species - type of input particle species
     */
    template<typename T_Particle_Species>
    struct Particle_Type{
        using type = typename particle_species::traits::Particle_Type<T_Particle_Species>::type;
    };

    /** Trait interface for typename of storage of record names, contains in particle species
     *
     * \tparam T_Particle_Species type of input particle species
     */
    template<typename T_Particle_Species>
    struct Record_names{
        using type = typename particle_species::traits::Record_names<T_Particle_Species>::type;
    };
} // namespace particle_species
} // namespace reduction_library
