#pragma once
#include "attribute/Type.hpp"
#include "Attributes_types.hpp"
#include "Base_attributes_getters.hpp"

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
    attribute::Type<Particle<Particles>, Attribute::momentum_x>& set_attribute<Particle<Particles>, Attribute::momentum_x>(Particle<Particles>& particle);


    template <>
    attribute::Type<Particle<Particles>, Attribute::weighting>& set_attribute<Particle<Particles>, Attribute::weighting>(Particle<Particles>& particle);

    template <>
    attribute::Type<Particle<Particles>, Attribute::momentum_x> get_attribute<Particle<Particles>, Attribute::momentum_x>(Particle<Particles>& particle);


    template <>
    attribute::Type<Particle<Particles>, Attribute::weighting> get_attribute<Particle<Particles>, Attribute::weighting>(Particle<Particles>& particle);
}
