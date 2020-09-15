#pragma once

#include "reduction_library/SOA/Particle_species.hpp"
#include "reduction_library/thinning/Thinning.hpp"

namespace reduction_library{
namespace thinning{

/*
template<class T_Names_list, class T_Record_type_list>
class Thinning{
private:
    double ratioDeletedPaticles;
public:
    Thinning(double ratioDeletedPaticles):
        ratioDeletedPaticles(ratioDeletedPaticles){}

    template<class T_particle>
    void operator()(std::vector<T_particle>& particles){
        KernelThinning<T_particle> thinningKernell(ratioDeletedPaticles);
         for (T_particle& particle : particles){
             thinningKernell.collect(particle);
         }
         thinningKernell.process();

         for (T_particle& particle : particles){
             thinningKernell.reduce(particle);
        }
    }

  //  void operator()(T_particles& particles){}

};

//void Thinning::operator()<SOA::Particle_spicies>(SOA::Particle_spicies& particles)
 //   template <typename T_Names_list, typename T_Record_type_list>
//	void Thinning<SOA::Particle_species<T_Names_list, T_Record_type_list>>::
	//    operator()(SOA::Particle_species<T_Names_list, T_Record_type_list>& particles)//
//	{

	/*    KernelThinning<AOS::Particle_spicies::MyParticle> thinningKernell(ratioDeletedPaticles);
		std::cout<<" particles.getSize() "<<particles.getSize()<<std::endl;
		for(int i=0; i < particles.getSize(); i++){
			thinningKernell.collect(particles.getParticle(i));
		}
		thinningKernell.process();
		for(int i=0; i < particles.getSize(); i++){
			thinningKernell.reduce(particles.getParticle(i));
		}*/

//	}



} //thinning
} //reduction_library

//  template<>
