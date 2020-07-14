#include "Particle.hpp"
#include "Particles.hpp"
#include "attribute/Type.hpp"

namespace reduction_library{

    template <>
    attribute::Type<Particle<Particles>, Attribute::momentum_x> & get_attribute<Particle<Particles>, Attribute::momentum_x>(Particle<Particles>& particle)
    {
        Momentums& momentum = static_cast<Momentums&>(particle.baseParticles);
        return momentum.get()[particle.idx];
    }


    template <>
    attribute::Type<Particle<Particles>, Attribute::weighting>& get_attribute<Particle<Particles>, Attribute::weighting>(Particle<Particles>& particle)
    {
        Weights& weights = static_cast<Weights&>(particle.baseParticles);
        return weights.get()[particle.idx];
    }

}
