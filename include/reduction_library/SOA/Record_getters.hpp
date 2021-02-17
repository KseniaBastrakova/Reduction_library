/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "../Particle_getters.hpp"
#include "reduction_library/record/Concept.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"
#include "reduction_library/SOA/Particle_species_traits.hpp"

namespace reduction_library{
namespace particle_access{

/** @file
 * Implementation getting and setting Particle records by component
 * provides access to every user-defined attribute of a particle
 * All possible record and components names
 * can be founded in reduction_library/component/Name.hpp
 * and in reduction_library/record/Name.hpp
 */

/** Getting element with given component name and record name for
 * given particle
 *
 *
 * \tparam Component_Name name of the requested component
 * \tparam Record_Name name of the requested Record
 * \tparam T_Particle_Species base type of species for given particle
 */
template<typename Component_Name, typename Record_Name, class T_Particle_Species>
struct Getting_value<Component_Name, Record_Name, Particle<T_Particle_Species>>
{
public:
    auto operator() (Particle<T_Particle_Species>& particle)
    {
        auto& base_particles = particle.particle_species; // species
        auto& record_value = particle_species::get<Record_Name, T_Particle_Species>(base_particles);
        auto& component = record::get<Component_Name>(record_value);
        auto& dataset = component.set_dataset();
        int idx = particle.idx;
        double& value = dataset[idx];
        return value;
    }
};

/** Setting element with given component name and record name for
 *  given particle
 *
 * \tparam Component_Name name of the requested component
 * \tparam Record_Name name of the requested Record
 * \tparam T_Particle_Species base type of species for given particle
 */
template<typename Component_Name, typename Record_Name, class T_Particle_species, typename T_Dataset>
struct Setting_value<Component_Name, Record_Name, Particle<T_Particle_species>, T_Dataset>
{
public:
    void operator() (T_Dataset value, Particle<T_Particle_species>& particle)
    {
        auto& base_particles = particle.particle_species; // species
        auto& record_value = particle_species::get<Record_Name, T_Particle_species>(base_particles);
        auto& component = record::get<Component_Name>(record_value);
        auto& dataset = component.set_dataset();
        int idx = particle.idx;
        dataset.set_value(value, idx);
    }
};

} // namespace particle_access
} // namespace reduction_library
