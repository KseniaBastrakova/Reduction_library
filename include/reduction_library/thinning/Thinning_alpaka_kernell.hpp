#pragma once

#include "reduction_library/SOA/Particle_species.hpp"
#include "reduction_library/thinning/Thinning.hpp"
#include "reduction_library/thinning/InKernelThinning.hpp"
#include <alpaka/alpaka.hpp>
#include <algorithm>

namespace reduction_library{
namespace thinning{

template<typename Acc, typename T_Particle_spicies>
struct Thinning_alpaka_kernell{
private:
    double ratioDeletedPaticles;
public:
    void init (double ratioDeletedPaticles){
        this->ratioDeletedPaticles = ratioDeletedPaticles;
    }

    ALPAKA_FN_ACC void operator()(Acc const& acc, T_Particle_spicies& particles, std::size_t patch_size) const{

    	using namespace alpaka;

    	uint32_t grid_block_idx = idx::getIdx<Grid, Blocks>(acc)[0];
    	std::size_t start_block_idx = grid_block_idx * patch_size;
    	std::size_t end_block_idx = std::min(grid_block_idx * patch_size, particles.size());

    	PMACC_SMEM( acc, algorithm, In_KernelThinning<T_Particle_spicies::Particle> );

      //  KernelThinning<T_particle> thinningKernell(ratioDeletedPaticles);

       // for( int i=0; i< particles.size(); i++ ){
      //  	thinningKernell.collect(particles[i]);
      //  }

       // thinningKernell.process();

       // for( int i=0; i< particles.size(); i++ ){
      //  	thinningKernell.reduce(particles[i]);
       // }


  //  void operator()(T_particles& particles){}
    }

};

} //namespace thinning
}// namespace reduction_library
