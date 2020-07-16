#pragma once

#include "Attributes_types.hpp"

struct Particle_st {
	double weighting;
	double momentum;

	Particle_st(): weighting(42.), momentum(43.) {}
};

//template <>
//double& get_attribute<Particle_st, Attribute::momentum>(Particle_st& particle);


//template <>
//double& get_attribute<Particle_st, Attribute::weighting>(Particle_st& particle);


