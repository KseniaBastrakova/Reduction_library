#pragma once
#include "Particles.hpp"
#include "Attributes_getting.hpp"

template<class Particle_type>
class Particle{
public:
	int idx;
	Particle_type &baseParticles;
	Particle(int idx, Particle_type &baseParticles):
		idx(idx), baseParticles(baseParticles){}
};

