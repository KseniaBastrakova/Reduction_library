#pragma once
#include "Particles.hpp"
#include "Attributes_getting.hpp"

class Particles;
class Particle{
public:
	int idx;
	Particles &baseParticles;
	Particle(int idx, Particles &baseParticles):
		idx(idx), baseParticles(baseParticles){}
};

