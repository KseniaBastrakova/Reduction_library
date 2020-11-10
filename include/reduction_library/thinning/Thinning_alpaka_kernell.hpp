#pragma once

#include "reduction_library/SOA/Particle_species.hpp"
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
    void init (double ratioDeletedPaticles)
    {
        this->ratioDeletedPaticles = ratioDeletedPaticles;
    }

    template<typename Acc, typename T_Particle_Species>
    ALPAKA_FN_ACC void operator()(Acc const& acc, const T_Particle_Species& particles, std::size_t patch_size) const
    {
    	using namespace alpaka;
    	auto grid_block_idx = idx::getIdx<Grid, Blocks>(acc)[0];
    	auto start_particles_idx = grid_block_idx * patch_size;
    	auto particles_size = particles.get_size();
    	auto end_particles_idx = math::min(acc, start_particles_idx  + patch_size, particles_size);


    	auto threadIdx = alpaka::idx::getIdx<alpaka::Grid, alpaka::Threads>(acc)[0];

    	using T_Particle_type = typename T_Particle_Species::My_particle;

    	auto &algorithm( alpaka::block::shared::st::allocVar<In_kernel_thinning<T_Particle_type>,
    	                                                    __COUNTER__>(acc));

    	algorithm.init(ratioDeletedPaticles);
    	block::sync::syncBlockThreads(acc);

    	auto const blockSize = alpaka::workdiv::getWorkDiv<alpaka::Block, alpaka::Threads>(acc);

    	auto const global_thread_idx = idx::getIdx<alpaka::Grid, alpaka::Threads>(acc);
    	auto const global_thread_extent = workdiv::getWorkDiv<alpaka::Grid, alpaka::Threads>(acc);
    	auto const linearized_global_threadIdx = idx::mapIdx<1u>(global_thread_idx, global_thread_extent)[0];
    	auto generator = alpaka::rand::generator::createDefault(acc, linearized_global_threadIdx, 0);
    	auto distribution(alpaka::rand::distribution::createUniformReal<float>(acc));

    	auto random_value_generator = [&]{ return distribution(generator); };
    	//std::cout<<"blockSize.prod()"<<blockSize.prod();
    	//КОСТЫЛЬ
    	T_Particle_Species& current_particles = const_cast<T_Particle_Species&>(particles);

        for(int i = start_particles_idx + grid_block_idx; i < end_particles_idx; i = i + blockSize.prod())
        {
          //  std::cout<<"i =="<<i;
            auto particle = current_particles.get_particle(i);

        	algorithm.collect(acc, particle, random_value_generator);
        	//auto p2 =current_particles.get_particle(i);
        	//auto weighting = particle_access::get_weighting(p2);
        	//std::cout<<"particle weight "<<weighting<<std::endl;
        }

        block::sync::syncBlockThreads(acc);

        if (threadIdx == 0)
        {
        	algorithm.process(acc);
        }

        block::sync::syncBlockThreads(acc);

        for(int i = start_particles_idx + grid_block_idx; i< end_particles_idx; i = i + blockSize.prod())
        {
            auto particle = current_particles.get_particle(i);
        	algorithm.reduce(acc, particle);
        	auto weighting = particle_access::get_weighting(particle);
            std::cout<<"particle weight "<<weighting<<std::endl;
        }


    }

};

} //namespace thinning
}// namespace reduction_library
