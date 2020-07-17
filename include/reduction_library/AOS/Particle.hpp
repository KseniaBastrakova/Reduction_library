#pragma once

#include "reduction_library/attribute/Scalar_records_names.hpp"
#include "reduction_library/attribute/Type.hpp"
#include "reduction_library/attribute/Base_attributes_getters.hpp"

namespace reduction_library{

    template<class Particle_type>
    class Particle{
    public:
        int idx;
        Particle_type &baseParticles;
        Particle(int idx, Particle_type &baseParticles):
            idx(idx), baseParticles(baseParticles){}
    };
    class Particle_spicies;


    template <>
    attribute::traits::Type<Particle<Particle_spicies>, attribute::Scalar_records_names::momentum_x>
        attribute::get_attribute<Particle<Particle_spicies>, attribute::Scalar_records_names::momentum_x>(Particle<Particle_spicies>& particle);


    template <>
    attribute::traits::Type<Particle<Particle_spicies>, attribute::Scalar_records_names::weighting>
        attribute::get_attribute<Particle<Particle_spicies>, attribute::Scalar_records_names::weighting>(Particle<Particle_spicies>& particle);

    template <>
    void attribute::set_attribute<Particle<Particle_spicies>, attribute::Scalar_records_names::momentum_x>(Particle<Particle_spicies>& particle,
            attribute::traits::Type<Particle<Particle_spicies>, attribute::Scalar_records_names::momentum_x> value);

    template <>
    void attribute::set_attribute<Particle<Particle_spicies>, attribute::Scalar_records_names::weighting>(Particle<Particle_spicies>& particle,
            attribute::traits::Type<Particle<Particle_spicies>, attribute::Scalar_records_names::weighting> value);
}
