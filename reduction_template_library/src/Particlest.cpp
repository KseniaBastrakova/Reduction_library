#include "Particlest.hpp"

namespace reduction_library{

    template <>
    double& get_attribute<Particle_st, Attribute::momentum_x>(Particle_st& particle)
    {
        return particle.momentum;
    }


    template <>
    double& get_attribute<Particle_st, Attribute::weighting>(Particle_st& particle)
    {
        return particle.weighting;
    }

}
