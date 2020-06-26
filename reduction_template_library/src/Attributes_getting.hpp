#pragma once

#include "Atributes_types.hpp"


template<typename T_particle, Attribute attribute>
double& get_attribute(T_particle & particle);


template<typename T_particle>
double& get_momentum(T_particle& particle)
{
	return get_attribute<T_particle, Attribute::momentum>(particle);
}

template<typename T_particle>
double& get_weighting(T_particle& particle)
{
	return get_attribute<T_particle, Attribute::weighting>(particle);
}

