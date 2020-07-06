#pragma once
#include <vector>
#include "AtrributeChunk.hpp"
#include "Particle.hpp"


using Momentums = AtrributeChunk<Attribute::momentum, double>;
using Weights = AtrributeChunk<Attribute::weighting, double>;


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



