#pragma once

#include <iostream>
#include "math.h"
#include <vector>

namespace reduction_library{
namespace thinning{

template<typename T_Particle>
class Getting_particle_energy{
    static constexpr double speed_light = 299792458.;
public:
    double operator()(const T_Particle& particle)
    {
        auto momentum_x = particle.get_momentum_x();
        auto momentum_y = particle.get_momentum_y();
        auto momentum_z = particle.get_momentum_z();
        auto mass = particle.get_mass();
        double total_energy = sqrt((momentum_x^2 + momentum_y^2 + momentum_z^2) * speed_light^2 +
                (mass * speed_light^2)^2);
        return total_energy;
    }

};

} // namespace thinning
} // reduction_library
