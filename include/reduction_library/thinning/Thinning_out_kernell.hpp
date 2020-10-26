#pragma once

#include "reduction_library/SOA/Particle_species.hpp"
#include "reduction_library/thinning/Thinning.hpp"
#include "reduction_library/thinning/In_kernel_thinning.hpp"
#include "reduction_library/thinning/Thinning_alpaka_kernell.hpp"
#include <alpaka/alpaka.hpp>

namespace reduction_library{
namespace thinning{


template<typename Acc, typename T_Particle_spicies, typename T_particle>
struct Thinning_out_kernell{
private:
    double ratioDeletedPaticles;
public:
    void init (double ratioDeletedPaticles){
        this->ratioDeletedPaticles = ratioDeletedPaticles;
    }

    void operator()(T_Particle_spicies& particles, std::size_t patch_size) const{

    	// TODO : copy data -- host/device

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

        using QueueProperty = alpaka::queue::Blocking;
        using Queue = alpaka::queue::Queue<Acc, QueueProperty>;

        auto const devAcc = alpaka::pltf::getDevByIdx<Acc>(0u);
        using QueueProperty = alpaka::queue::Blocking;
        using QueueAcc = alpaka::queue::Queue<Acc, QueueProperty>;

        QueueAcc queue(devAcc);


        // Попытка скопировать данные с хоста на девайс

        using DevHost = alpaka::dev::DevCpu;
        auto const devHost = alpaka::pltf::getDevByIdx<DevHost>(0u);

        Thinning_alpaka_kernell kernel;
        kernel.init(ratioDeletedPaticles);


        auto const taskKernel(alpaka::kernel::createTaskKernel<Acc>(
               workDiv,
               kernel));


       alpaka::queue::enqueue(queue, taskKernel);
       alpaka::wait::wait(queue);
    }


};

} // namespace thinning
} // namespace reduction_library
