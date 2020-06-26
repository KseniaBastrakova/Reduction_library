/*
 * particle_type.hpp
 *
 *  Created on: Jun 25, 2020
 *      Author: kseniia
 */

#pragma once
#include "Attributes_getting.hpp"

struct Particle_st {
	double weighting;
	double momentum;

	Particle_st(): weighting(42.), momentum(43.) {}
};

template <>
double& get_attribute<Particle_st, Attribute::momentum>(Particle_st& particle)
{
	return particle.momentum;
}


template <>
double& get_attribute<Particle_st, Attribute::weighting>(Particle_st& particle)
{
	return particle.weighting;
}



