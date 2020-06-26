#pragma once
#include "Particle.hpp"
#include "Particles.hpp"

template <>
double& get_attribute<Particle, Attribute::momentum>(Particle& particle)
{
	return particle.baseParticles.momentum.at(particle.idx);
}

template <>
double& get_attribute<Particle, Attribute::weighting>(Particle& particle)
{
	return particle.baseParticles.weights.at(particle.idx);
};
