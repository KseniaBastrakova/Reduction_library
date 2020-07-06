#pragma once
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Particle.hpp"


template<class T_particle>
class IKernaellThinning{
private:
	double ratioDeletedPaticles;
	int numOfParticles;

public:
	IKernaellThinning(double ratioDeletedPaticles):
		ratioDeletedPaticles(ratioDeletedPaticles),
		numOfParticles(0){}

	void collect(T_particle particle){
		numOfParticles++;
	}

	void process(){

	}

	void reduce(T_particle particle){
		double random_value = ((double) rand() / (RAND_MAX));
		if (random_value < ratioDeletedPaticles)
		{
			double& weihgting = get_weighting<T_particle>(particle);
			weihgting = 0;
		}
	}
};








