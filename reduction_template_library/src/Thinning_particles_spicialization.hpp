#pragma once
#include "Thinning.hpp"

	template<>
	void Thinning::operator()<Particles>(Particles& particles)
	{
		IKernaellThinning<Particles::MyParticle> thinningKernell(ratioDeletedPaticles);
		for(int i=0; i < particles.getSize(); i++){
			thinningKernell.collect(particles.getParticle(i));
		}
		thinningKernell.process();
		for(int i=0; i < particles.getSize(); i++){
			thinningKernell.reduce(particles.getParticle(i));
		}

	}
