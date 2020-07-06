#pragma once
#include <vector>
#include "AtrributeChunk.hpp"
#include "Particle.hpp"


using Momentums = AtrributeChunk<Attribute::momentum, double>;
using Weights = AtrributeChunk<Attribute::weighting, double>;


class Particles: public Momentums, public Weights {
	int size;
	public:
	using MyParticle = Particle<Particles>;
	Particles(std::vector<double>& weights,
			 std::vector<double>& momentum):
				 Momentums(momentum), Weights(weights), size(weights.size()){}

	MyParticle getParticle(int idx){

		return MyParticle(idx, *this);
	}
	int getSize(){
		return size;
	}

};



