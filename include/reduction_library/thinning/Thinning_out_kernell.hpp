#pragma once

#include "reduction_library/SOA/Particle_species.hpp"
#include "reduction_library/thinning/Thinning.hpp"
#include <alpaka/alpaka.hpp>

namespace reduction_library{
namespace thinning{


template<typename Acc, typename T_Particle_spicies>
struct Thinning_out_kernell{
private:
    double ratioDeletedPaticles;
public:
    void init (double ratioDeletedPaticles){
        this->ratioDeletedPaticles = ratioDeletedPaticles;
    }

    void operator()(T_Particle_spicies& particles, std::size_t patch_size) const{

    	std::size_t num_particles = particles.size();
    	std::size_t num_patches = std::ceil(num_particles / patch_size);


    	using Dim = alpaka::dim::DimInt<1u>;
    	using Idx = std::size_t;

        using Vec = alpaka::vec::Vec<Dim, Idx>;
        Vec const elementsPerThread(Vec::all(static_cast<Idx>(1)));
        Vec const threadsPerBlock(Vec::all(static_cast<Idx>(1)));

        Vec const blocksPerGrid(static_cast<Idx>(num_patches));

        using WorkDiv = alpaka::workdiv::WorkDivMembers<Dim, Idx>;
        WorkDiv const workdiv(
            blocksPerGrid,
            threadsPerBlock,
            elementsPerThread);

    //    KernelThinning<T_particle> thinningKernell(ratioDeletedPaticles);

      //  for( int i=0; i< particles.size(); i++ ){
       // 	thinningKernell.collect(particles[i]);
       // }

       // thinningKernell.process();

       // for( int i=0; i< particles.size(); i++ ){
        //	thinningKernell.reduce(particles[i]);
        //}
    }


};

} // namespace thinning
} // namespace reduction_library
