#pragma once

#include "reduction_library/SOA/Particle_species.hpp"
#include "reduction_library/thinning/Thinning.hpp"
#include "reduction_library/thinning/In_kernel_thinning.hpp"
#include <alpaka/alpaka.hpp>
#include <algorithm>
#include "In_kernel_thinning.hpp"

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

    	std::size_t threadIdx = alpaka::idx::getIdx<alpaka::Grid, alpaka::Threads>(acc);
    	if (threadIdx == 0)	{
			PMACC_SMEM( acc, algorithm, In_kernel_thinning<T_Particle_spicies::Particle> );
			algorithm.init();
    	}

    	block::sync::syncBlockThreads(acc);

        for( int i = start_block_idx + grid_block_idx; i< end_block_idx; i=+patch_size){
        	algorithm.collect(particles[i]);
        }

        block::sync::syncBlockThreads(acc);

        if (threadIdx == 0)	{
        	algorithm.process();
        }

        block::sync::syncBlockThreads(acc);

        for( int i=start_block_idx + grid_block_idx; i< end_block_idx; i=+patch_size){
        	algorithm.reduce(particles[i]);
        }


  //  void operator()(T_particles& particles){}
    }

};

} //namespace thinning
}// namespace reduction_library
