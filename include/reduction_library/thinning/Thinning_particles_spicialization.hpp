#pragma once

#include "reduction_library/thinning/Thinning.hpp"

namespace reduction_library{
namespace thinning{

	template<>
	void Thinning::operator()<AOS::Particles>(AOS::Particles& particles)
	{
	    KernelThinning<AOS::Particles::MyParticle> thinningKernell(ratioDeletedPaticles);
		std::cout<<" particles.getSize() "<<particles.getSize()<<std::endl;
		for(int i=0; i < particles.getSize(); i++){
			thinningKernell.collect(particles.getParticle(i));
		}
		thinningKernell.process();
		for(int i=0; i < particles.getSize(); i++){
			thinningKernell.reduce(particles.getParticle(i));
		}

	}

} //thinning
} //reduction_library
