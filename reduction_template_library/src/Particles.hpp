#pragma once
#include <vector>
#include "AtrributeChunk.hpp"


using Momentums = AtrributeChunk<Attribute::momentum, double>;
using Weights = AtrributeChunk<Attribute::weighting, double>;


template<class Particle_type> class Particle;

template<class Particle_type> Particle<Particle_type>::Particle(int idx, Particle_type &baseParticles);

class Particles: public Momentums, public Weights {

	public:
	using MyParticle = Particle<Particles>;
	Particles(std::vector<double>& weights,
			 std::vector<double>& momentum):
				 Momentums(momentum), Weights(weights){}

	MyParticle getParticle(int idx){

		return MyParticle(idx, *this);
	}
	int getSize(){
		return 0;
	}

};



