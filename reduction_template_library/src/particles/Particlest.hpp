#pragma once

#include "attribute/Type.hpp"
#include "Attributes_types.hpp"
#include "Base_attributes_getters.hpp"

namespace reduction_library{

struct Particle_st {
	double weighting;
	double momentum;

	Particle_st(): weighting(42.), momentum(43.) {}
};

//template <>
//attribute::Type<Particle_st<Particles>, Attribute::momentum_x>& get_attribute<Particle_st, Attribute::momentum>(Particle_st& particle);


//template <>
//attribute::Type<Particle_st<Particles>, Attribute::momentum_x>& get_attribute<Particle_st, Attribute::weighting>(Particle_st& particle);


}
