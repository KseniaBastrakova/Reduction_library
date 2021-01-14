/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace reduction_library{

/** @file
 * Auxiliary class for representing one particle
 * We accume, that particle contains only
 * index number of particle in particle species
 * and link to base particle species that provides access to elements by idx
 *
 */

    template<class Particle_Species_Type>
    class Particle{
    public:
        //-----------------------------------------------------------------------------
        //! Index number of particle in particle species. Should be unique
        int idx;
        //-----------------------------------------------------------------------------
        //! Link to base particle species, that contains this particle
        Particle_Species_Type &particle_species;
        Particle(int idx, Particle_Species_Type &particle_species):
            idx(idx), particle_species(particle_species){}
    };

} // namespace reduction_library
