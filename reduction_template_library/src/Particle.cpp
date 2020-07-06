#include "Particle.hpp"
#include "Particles.hpp"


template <>
double& get_attribute<Particle<Particles>, Attribute::momentum>(Particle<Particles>& particle)
{
	Momentums& momentum = static_cast<Momentums&>(particle.baseParticles);
	return momentum.get()[particle.idx];
}


template <>
double& get_attribute<Particle<Particles>, Attribute::weighting>(Particle<Particles>& particle)
{
	Weights& weights = static_cast<Weights&>(particle.baseParticles);
	return weights.get()[particle.idx];
}

