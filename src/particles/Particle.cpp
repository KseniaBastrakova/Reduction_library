
#include "particles/Particle.hpp"
#include "AOS/Particles.hpp"
#include "reduction_library/attribute/Type.hpp"
#include "reduction_library/attribute/Attributes_types.hpp"

namespace reduction_library{

    template <>
    attribute::traits::Type<Particle<Particles>, attribute::Attribute::momentum_x>
        attribute::get_attribute<Particle<Particles>, attribute::Attribute::momentum_x>(Particle<Particles>& particle)
    {
        AOS::Momentums& momentum = static_cast<AOS::Momentums&>(particle.baseParticles);
        return momentum.get()[particle.idx];
    }


    template <>
    attribute::traits::Type<Particle<Particles>, attribute::Attribute::weighting>
        attribute::get_attribute<Particle<Particles>, attribute::Attribute::weighting>(Particle<Particles>& particle)
    {
        AOS::Weights& weights = static_cast<AOS::Weights&>(particle.baseParticles);
        return weights.get()[particle.idx];
    }

    template <>
    void attribute::set_attribute<Particle<Particles>, attribute::Attribute::momentum_x>(Particle<Particles>& particle,
            attribute::traits::Type<Particle<Particles>, attribute::Attribute::momentum_x> value)
    {
        AOS::Momentums& momentum = static_cast<AOS::Momentums&>(particle.baseParticles);
        momentum = value;
    }

    template <>
    void attribute::set_attribute<Particle<Particles>, attribute::Attribute::weighting>(Particle<Particles>& particle,
            attribute::traits::Type<Particle<Particles>, attribute::Attribute::weighting> value)
    {
        AOS::Weights& weights = static_cast<AOS::Weights&>(particle.baseParticles);
        weights = value;
    }

}
