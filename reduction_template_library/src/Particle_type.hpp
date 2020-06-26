/*
 * particle_type.hpp
 *
 *  Created on: Jun 25, 2020
 *      Author: kseniia
 */

#pragma once
#include "Attributes_getting.hpp"

struct Particle {
	double weighting;
	double momentum;

	Particle(): weighting(42.), momentum(43.) {}
};

template <>
double& get_attribute<Particle, Attribute::momentum>(Particle& particle)
{
	return particle.momentum;
}


template <>
double& get_attribute<Particle, Attribute::weighting>(Particle& particle)
{
	return particle.weighting;
}



