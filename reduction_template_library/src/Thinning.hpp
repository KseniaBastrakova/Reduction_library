#pragma once
#include <vector>
#include "IKernellThinning.hpp"

template<class T_particle>
class Thinning{
private:
	double ratioDeletedPaticles;
public:
	Thinning(double ratioDeletedPaticles):
		ratioDeletedPaticles(ratioDeletedPaticles){}


	void operator()(std::vector<T_particle>& particles){
		IKernaellThinning<T_particle> thinningKernell(ratioDeletedPaticles);
		 for (T_particle& particle : particles){
			 thinningKernell.collect(particle);
		 }
		 thinningKernell.process();

		 for (T_particle& particle : particles){
			 thinningKernell.reduce(particle);
		}
	}
};

