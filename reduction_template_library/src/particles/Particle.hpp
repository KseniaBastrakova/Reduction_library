#pragma once
#include "AtrributeChunk.hpp"
#include "Attributes_types.hpp"
#include "attribute/Type.hpp"

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
    attribute::Type<Particle<Particles>, Attribute::momentum_x>& get_attribute<Particle<Particles>, Attribute::momentum_x>(Particle<Particles>& particle);


    template <>
    attribute::Type<Particle<Particles>, Attribute::weighting>& get_attribute<Particle<Particles>, Attribute::weighting>(Particle<Particles>& particle);

}
