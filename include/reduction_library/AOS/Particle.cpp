
#include "reduction_library/AOS/Particle.hpp"

#include "../objects/Scalar_records_names.hpp"
#include "../objects/Type.hpp"
#include "reduction_library/AOS/Particle_spicies.hpp"

namespace reduction_library{

    template <>
    attribute::traits::Type<Particle<Particle_spicies>, attribute::Scalar_records_names::momentum_x>
        attribute::get_attribute<Particle<Particle_spicies>, attribute::Scalar_records_names::momentum_x>(Particle<Particle_spicies>& particle)
    {
        AOS::Momentums& momentum = static_cast<AOS::Momentums&>(particle.baseParticles);
        return momentum.get()[particle.idx];
    }


    template <>
    attribute::traits::Type<Particle<Particle_spicies>, attribute::Scalar_records_names::weighting>
        attribute::get_attribute<Particle<Particle_spicies>, attribute::Scalar_records_names::weighting>(Particle<Particle_spicies>& particle)
    {
        AOS::Weights& weights = static_cast<AOS::Weights&>(particle.baseParticles);
        return weights.get()[particle.idx];
    }

    template <>
    void attribute::set_attribute<Particle<Particle_spicies>, attribute::Scalar_records_names::momentum_x>(Particle<Particle_spicies>& particle,
            attribute::traits::Type<Particle<Particle_spicies>, attribute::Scalar_records_names::momentum_x> value)
    {
        AOS::Momentums& momentum = static_cast<AOS::Momentums&>(particle.baseParticles);
        momentum = value;
    }

    template <>
    void attribute::set_attribute<Particle<Particle_spicies>, attribute::Scalar_records_names::weighting>(Particle<Particle_spicies>& particle,
            attribute::traits::Type<Particle<Particle_spicies>, attribute::Scalar_records_names::weighting> value)
    {
        AOS::Weights& weights = static_cast<AOS::Weights&>(particle.baseParticles);
        weights = value;
    }

}
