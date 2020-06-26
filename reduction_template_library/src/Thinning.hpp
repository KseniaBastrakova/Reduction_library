#pragma once
#include <vector>
#include "IKernellThinning.hpp"
#include "Particles.hpp"


class Thinning{
private:
	double ratioDeletedPaticles;
public:
	Thinning(double ratioDeletedPaticles):
		ratioDeletedPaticles(ratioDeletedPaticles){}

	template<class T_particle>
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
	template<class T_particles>
	void operator()(T_particles& particles){}



};


