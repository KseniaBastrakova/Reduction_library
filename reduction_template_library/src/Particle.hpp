#pragma once

template<class Particle_type>
class Particle{
public:
	int idx;
	Particle_type &baseParticles;
	Particle(int idx, Particle_type &baseParticles):
		idx(idx), baseParticles(baseParticles){}
};


//template <>
//double& get_attribute<Particle, Attribute::momentum>(Particle& particle)
//{
	//return 0; //particle.momentum;
//}


//template <>
//double& get_attribute<Particle, Attribute::weighting>(Particle& particle)
//{
//	return 0; //particle.weighting;
//}
