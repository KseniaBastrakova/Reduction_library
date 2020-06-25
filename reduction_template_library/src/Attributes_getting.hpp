#include "Particle_type.hpp"
#include "Atributes_types.hpp"


template<typename T_particle, typename T_attributes_type>
double get_attribute(T_particle particle, T_attributes_type attributes_type);


template<typename T_particle>
double get_attribute_momentum(T_particle particle);

template<typename T_particle>
double get_attribute_coordinates(T_particle particle);

template <> double get_attribute<Particle, Particle_attributes>(Particle particle, Particle_attributes attribute_type)
{
	if (attribute_type == Particle_attributes::coordinates)
		return particle.coordinates;
	if (attribute_type == Particle_attributes::momentum)
		return particle.momentum;
}

template <> double get_attribute_momentum<Particle >(Particle particle)
		{
			return get_attribute<Particle, Particle_attributes>(particle, Particle_attributes::momentum);
		}

template <> double get_attribute_coordinates<Particle >(Particle particle)
		{
			return get_attribute<Particle, Particle_attributes>(particle, Particle_attributes::coordinates);
		}
