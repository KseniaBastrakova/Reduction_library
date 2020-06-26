#pragma once
#include <vector>
#include "Particle.hpp"


class Particles{
	public:
	std::vector<double> weights;
	std::vector<double> momentum;

	Particles(std::vector<double>& weights,
			 std::vector<double>& momentum):
				weights(weights), momentum(momentum){}

	Particle& getParticle(int idx){

		return new(Particle(idx, *this));
	}
	int getSize(){
		return weights.size();
	}

};



