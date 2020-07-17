#pragma once

#include "reduction_library/attribute/Scalar_records_names.hpp"
#include "reduction_library/attribute/Type.hpp"
#include "reduction_library/attribute/Base_attributes_getters.hpp"

namespace reduction_library{
namespace SOA{

struct Particle {
	double weighting;
	double momentum;

	Particle(): weighting(42.), momentum(43.) {}
};

//template <>
//attribute::Type<Particle_st<Particles>, Attribute::momentum_x>& get_attribute<Particle_st, Attribute::momentum>(Particle_st& particle);


//template <>
//attribute::Type<Particle_st<Particles>, Attribute::momentum_x>& get_attribute<Particle_st, Attribute::weighting>(Particle_st& particle);

}
}
