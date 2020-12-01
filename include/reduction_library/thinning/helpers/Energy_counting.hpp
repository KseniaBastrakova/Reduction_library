/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <math.h>
#include "reduction_library/Particle.hpp"

namespace reduction_library{
namespace thinning{

template<typename T_Particle>
class Getting_particle_energy{
    static constexpr double speed_light = 299792458.;
public:
    double operator()(const T_Particle& particle)
    {
        auto momentum_x = particle_access::get_momentum_x(particle);
        auto momentum_y = particle_access::get_momentum_y(particle);
        auto momentum_z = particle_access::get_momentum_z(particle);
        auto mass = particle_access::get_mass(particle);
        double total_energy = sqrt((momentum_x * momentum_x +
                momentum_y * momentum_y + momentum_z * momentum_z) * speed_light * speed_light +
                (mass * speed_light * speed_light) * (mass * speed_light * speed_light));
        return total_energy;
    }
};

} // namespace thinning
} // reduction_library
