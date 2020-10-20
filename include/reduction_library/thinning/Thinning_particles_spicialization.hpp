#pragma once

#include "reduction_library/SOA/Particle_species.hpp"
#include "reduction_library/thinning/Thinning.hpp"
#include "reduction_library/thinning/In_kernel_thinning.hpp"
#include <alpaka/alpaka.hpp>

namespace reduction_library{
namespace thinning{

/*
template<typename Acc, typename T_Bufer, class T_particle>
struct Thinning_alpaka_kernell{
private:
    double ratioDeletedPaticles;
public:
    void init (double ratioDeletedPaticles){
        this->ratioDeletedPaticles = ratioDeletedPaticles;
    }

    ALPAKA_FN_ACC void operator()(Acc const& acc, T_Bufer& particles) const{

    	In_kernel_thinning<T_particle> thinningKernell(ratioDeletedPaticles);

        for( int i=0; i< particles.size(); i++ ){
        	thinningKernell.collect(particles[i]);
        }

        thinningKernell.process();

        for( int i=0; i< particles.size(); i++ ){
        	thinningKernell.reduce(particles[i]);
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
