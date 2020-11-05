#pragma once

#include "reduction_library/SOA/Particle_species.hpp"
#include "reduction_library/thinning/Thinning.hpp"
#include "reduction_library/thinning/In_kernel_thinning.hpp"
#include <alpaka/alpaka.hpp>
#include <algorithm>
#include "In_kernel_thinning.hpp"

namespace reduction_library{
namespace thinning{


struct Thinning_alpaka_kernell{
private:
    double ratioDeletedPaticles;
public:
    void init (double ratioDeletedPaticles){
        this->ratioDeletedPaticles = ratioDeletedPaticles;
    }

    template<typename Acc, typename T_Particle_species>
    ALPAKA_FN_ACC void operator()(Acc const& acc, T_Particle_species particles, std::size_t patch_size) const{

    	using namespace alpaka;

    	auto grid_block_idx = idx::getIdx<Grid, Blocks>(acc)[0];
    	auto start_particles_idx = grid_block_idx * patch_size;
    	auto end_particles_idx = math::min(acc, grid_block_idx * patch_size, particles.size());

    	auto threadIdx = alpaka::idx::getIdx<alpaka::Grid, alpaka::Threads>(acc);

    	using T_Particle_type = typename T_Particle_species::Particle;
    	auto &algorithm( alpaka::block::shared::st::allocVar<In_kernel_thinning<T_Particle_type>,
    	                                                    __COUNTER__>(acc));

    	algorithm.init();
    	block::sync::syncBlockThreads(acc);

    	auto const blockSize = alpaka::workdiv::getWorkDiv<alpaka::Block, alpaka::Threads>(acc);

        for(int i = start_particles_idx + grid_block_idx; i < end_particles_idx; i =+ blockSize.prod()){
        	algorithm.collect(particles[i]);
        }

        block::sync::syncBlockThreads(acc);

        if (threadIdx == 0)	{
        	algorithm.process();
        }

        block::sync::syncBlockThreads(acc);

        for(int i = start_particles_idx + grid_block_idx; i< end_particles_idx; i =+ blockSize.prod()){
        	algorithm.reduce(particles[i]);
        }

    }

};

} //namespace thinning
}// namespace reduction_library
