#pragma once

#include "reduction_library/attribute/Type.hpp"
#include "reduction_library/attribute/Attributes_types.hpp"
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
    class Particles;


    template <>
    attribute::traits::Type<Particle<Particles>, attribute::Attribute::momentum_x>
        attribute::get_attribute<Particle<Particles>, attribute::Attribute::momentum_x>(Particle<Particles>& particle);


    template <>
    attribute::traits::Type<Particle<Particles>, attribute::Attribute::weighting>
        attribute::get_attribute<Particle<Particles>, attribute::Attribute::weighting>(Particle<Particles>& particle);

    template <>
    void attribute::set_attribute<Particle<Particles>, attribute::Attribute::momentum_x>(Particle<Particles>& particle,
            attribute::traits::Type<Particle<Particles>, attribute::Attribute::momentum_x> value);

    template <>
    void attribute::set_attribute<Particle<Particles>, attribute::Attribute::weighting>(Particle<Particles>& particle,
            attribute::traits::Type<Particle<Particles>, attribute::Attribute::weighting> value);
}
