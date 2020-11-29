/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

/** @file
 *
 * Define name tags to identify records inside particle species
 *
 * This file implements the standard openPMD component names for the scalar, Cartesian and cylindrical cases
 * https://github.com/openPMD/openPMD-standard/blob/latest/STANDARD.md#scalar-vector-and-tensor-records .
 * For these standard cases, the following names must be used.
 * For other cases, a user is free to use any unique type tags, no requirements are posed on those.
 */


namespace reduction_library{
namespace record{
namespace name{

    //! Tag for component-wise momentum of the macroparticle or of theunderlying individual particle
    struct Momentum {};

    //! Tag for defining the number of underlying individual particles that the macroparticles represent
    struct Weighting {};

    //! Tag for component-wise position of a particle
    struct Position {};

    //! Tag for electric charge of the macroparticle or of the underlying individual particle
    struct Charge {};

    //! Tag for mass of the macroparticle or of the underlying individual particle
    struct Mass {};

    //! Tag for a globally-unique identifying integer for each particle, that can be used to, e.g., track particles
    struct Idx {};
};

} // namespace record
} //namespace reduction_library
