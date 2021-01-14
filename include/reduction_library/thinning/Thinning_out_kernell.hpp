/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once
#include "reduction_library/particle_species/Interfaces.hpp"
#include "reduction_library/thinning/Thinning_alpaka_kernell.hpp"

#include <alpaka/alpaka.hpp>

namespace reduction_library{
namespace thinning{
/** @file
 * Out of Kernell particle reduction
 * Initialize all Aplaka nessesery attributes
 * copy data from host to device
 * and run "in kernel" version of algorithm
 *
 */
    /** Base implementation of "out of kernel" version
     * that make reduction according to algorithm
     *
     * \tparam Acc Alpaka accelerator type
     * \tparam T_Algorithm type of thinning reduction algorithm
     * \tparam T_Particle_Species type of input particle
     * (should allow all necessary functions and getters for each algorithm)
     * \tparam particles - input particles to reduce
     * \tparam patch_size - amount of particles, that can effectively process
     * independent
     *
     */

    template<typename Acc, typename T_Particle_Spicies, typename T_Algorithm>
    struct Thinning_out_kernell{
    private:
        typename T_Algorithm::Parameters algorihtm_parameters;
    public:
        void init(typename T_Algorithm::Parameters parameters)
        {
            this->algorihtm_parameters = parameters;
        }

        void operator()(T_Particle_Spicies& particles, std::size_t patch_size) const
        {
            std::size_t num_particles = particle_species::get_size(particles);

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

            using DevHost = alpaka::dev::DevCpu;
            auto const devHost = alpaka::pltf::getDevByIdx<DevHost>(0u);

            Thinning_alpaka_kernell<T_Algorithm> kernel;
            kernel.init(algorihtm_parameters);

            auto particles_device = reduction_library::particle_species::make_species_different_acc<Acc>(particles);
            auto const taskKernel(alpaka::kernel::createTaskKernel<Acc>(
                   workdiv,
                   kernel,
                   particles_device,
                   patch_size));

           alpaka::queue::enqueue(queue, taskKernel);
           alpaka::wait::wait(queue);

           particles = reduction_library::particle_species::make_species_different_acc<Acc>(particles_device);
        }

};

} // namespace thinning
} // namespace reduction_library
