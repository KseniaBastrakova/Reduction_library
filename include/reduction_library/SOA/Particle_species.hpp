/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <tuple>
#include <alpaka/alpaka.hpp>
#include "reduction_library/helpers/Tuple_idx_getters.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/SOA/Particle.hpp"
#include "reduction_library/particle_species/Type.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"
//#include "reduction_library/SOA/Particle_species_traits.hpp"
#include "reduction_library/helpers/Type_list.hpp"

namespace reduction_library{
namespace SOA{

/** @file
 *
 * Implementation particle species concept (reduction_library/particle_species/Interfaces.hpp)
 * for "SOA" data representation
 *
 * define all necessary functions and traits: getting Unit_SI, setting Unit_SI
 * getting type of particle, getting type of each record in species,
 * getting record by name, getting number of particles, getting particle by idx
 *
 * Parameterized by T_Names_List and T_Record_Type_List typelists,
 * Which contains collection of records with and corresponding names
 *
 */

template<typename T_Names_List, typename T_Record_Type_List>
class Particle_species{
public:
    //-----------------------------------------------------------------------------
    //! Type of each particle, that contains in particle species
    using Particle_type = Particle<Particle_species>;
    //-----------------------------------------------------------------------------
    //! Type of records collection
    using Records = T_Record_Type_List;
    //-----------------------------------------------------------------------------
    //! Type of records names, that connected with records collection
    using Names = T_Names_List;
    //-----------------------------------------------------------------------------
    //! Number of particles in species
    int size;
public:
    Records records;
    Particle_species(){}

    Particle_species(const Particle_species& particle_species):
        records(particle_species.get_records())
    {
        size = std::get< 0 >( records ).get_size();
    }

    template<typename T_Another_Names_List, typename T_Another_Record_Type_List>
    ALPAKA_FN_HOST_ACC Particle_species(Particle_species<T_Another_Names_List,T_Another_Record_Type_List> const & particle_species):
        records(particle_species.get_records())
    {
        size = std::get< 0 >(records).get_size();
    }

    Particle_species(T_Record_Type_List records):
        records(records)
    {
        size = std::get< 0 >( records ).get_size();
    }

    /** Read-only getting record collection */
    ALPAKA_FN_HOST_ACC auto get_records() const
    {
        return records;
    }

    /** Getting link to one particle.  */
    Particle_type get_particle(int idx)
    {
        return Particle_type(idx, *this);
    }

    /** Getting number of particles.  */
    ALPAKA_FN_HOST_ACC int get_size() const
    {
        auto first_record = std::get< 0 >( records );
        return first_record.get_size();
    }

};

} // SOA


namespace particle_species{
namespace traits{

    /** Get a record type in particle species by record name
     *
     * \tparam T_Record_Name name of record for getting type
     * \tparam T_Names_List type list of records names, that connected with records collection
     * \tparam T_Record_Type_List type list of records collection, that contains in species
     */
    template<typename T_Record_Name, typename T_Names_List, typename T_Record_Type_List>
    struct Type<T_Record_Name, SOA::Particle_species<T_Names_List, T_Record_Type_List>>
    {
        using Species = SOA::Particle_species<T_Names_List, T_Record_Type_List>;
        using Names = typename Species::Names;
        using type = typename std::tuple_element_t<
                helpers::Index<T_Record_Name, Names>::value,
                typename Species::Records
         >;
    };

    /** Get a particle type for species
     *
     * \tparam T_Names_List type list of records names, that connected with records collection
     * \tparam T_Record_Type_List type list of records collection, that contains in species
     */
    template<typename T_Names_List, typename T_Record_Type_List>
    struct Particle_Type<SOA::Particle_species<T_Names_List, T_Record_Type_List>>
    {
        using Particle_type = typename SOA::Particle_species<T_Names_List, T_Record_Type_List>::My_particle;
        using type = Particle_type;
    };

} // namespace traits

    /** Partal specialization particle species interface Getting_value for SOA::Particle_species
     *
     *  return record by name
     *
     * \tparam  T_Record_Name name of requested record
     * \tparam T_Names_List type list of records names, that connected with records collection
     * \tparam T_Record_Type_List type list of records collection, that contains in species
     */
    template<typename T_Record_Name, typename T_Names_List, typename T_Record_Type_List>
    struct Getting_value<T_Record_Name, SOA::Particle_species<T_Names_List, T_Record_Type_List>>
    {
    public:
    	ALPAKA_FN_HOST_ACC auto& operator() (SOA::Particle_species<T_Names_List, T_Record_Type_List>& particle_species)
        {
            using Names = typename SOA::Particle_species<T_Names_List, T_Record_Type_List>::Names;
            constexpr auto idx = helpers::Index<T_Record_Name, Names>::value;
            return std::get< idx >( particle_species.records );
        }
    };

    /** Partal specialization particle species interface Getiing_size for SOA::Particle_species
     *
     *  return number of particles in particle species
     *
     * \tparam T_Names_List type list of records names, that connected with records collection
     * \tparam T_Record_Type_List type list of records collection, that contains in species
     */
    template<typename T_Names_List, typename T_Record_Type_List>
    struct Getiing_size<SOA::Particle_species<T_Names_List, T_Record_Type_List>>
    {
    public:
        ALPAKA_FN_HOST_ACC auto operator() (const SOA::Particle_species<T_Names_List, T_Record_Type_List>& particle_species)
        {
            return particle_species.get_size();
        }
     };

    /** Partal specialization particle species interface Getting_particle for SOA::Particle_species
     *
     *  return particle from particle species by given idx
     *
     * \tparam T_Names_List type list of records names, that connected with records collection
     * \tparam T_Record_Type_List type list of records collection, that contains in species
     */
    template<typename T_Names_List, typename T_Record_Type_List>
    struct Getting_particle<SOA::Particle_species<T_Names_List, T_Record_Type_List>>
    {
    public:
        ALPAKA_FN_HOST_ACC auto& operator() (SOA::Particle_species<T_Names_List, T_Record_Type_List>& particle_species, int idx)
        {
            return particle_species.get_particle(idx);
        }
    };

    /** Making species by list of records and list of names
     *
     *  list of record should correspond list of names
     *
     * \tparam T_Names_List type list of records names, that connected with records collection
     * \tparam T_Record_Type_List type list of records collection, that contains in species
     */
    template<typename ... T_Names, typename ... T_Record_Types>
    auto make_species(T_Record_Types& ...  records)
    {
        using Names = helpers::Type_list< T_Names ... >;
        using Record_types = helpers::Type_list<T_Record_Types ...>;
        using Species = SOA::Particle_species< Names, Record_types>;
        Record_types input_records(records...);
        Species species(input_records);
        return species;
    }


} // namespace particle_spicies
} // reduction_library
