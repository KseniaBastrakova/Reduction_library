/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <alpaka/alpaka.hpp>
#include <algorithm>

namespace reduction_library{
namespace thinning{

/** @file
 * Alpaka kernel for all "thinning-based" algorithms
 * provides redistribution of particle processing
 * between different nodes and threads,
 * running all base steps of each algorithm:
 * 0) Initialization with base structure of parameters
 * (tuple with different parameters for different algorithms)
 * 1) collecting all particles, and all necessary for algorithm particles data
 * 2) processing: computing algorithm - depends quantities
 * 3) reducing: assign new weight to each particle.
 * (we mark particle to be deleted if weight = 0)
 *
 */
    /** Base implementation of Alpaka kernel,
     * that make reduction according to algorithm
     * \tparam Acc Alpaka accelerator type
     * \tparam T_Algorithm type of thinning reduction algorithm
     * \tparam T_Algorithm::Parameters type of algorithm-depended reduction parameters
     *
     */
    template<typename T_Algorithm>
    struct Thinning_alpaka_kernell{
    private:
        typename T_Algorithm::Parameters algorihtm_parameters;
    public:
        void init (typename T_Algorithm::Parameters algorihtm_parameters)
        {
            this->algorihtm_parameters = algorihtm_parameters;
        }
        /** Base particle reduction functor
         * that make reduction according to algorithm
         * \tparam Acc Alpaka accelerator type
         * \tparam T_Particle_Species type of input particle
         * (should allow all necessary functions and getters for each algorithm)
         * \tparam particles - input particles to reduce
         * \tparam patch_size - amount of particles, that can effectively process
         * independent
         *
         */
        template<typename Acc, typename T_Particle_Species>
        ALPAKA_FN_ACC void operator()(Acc const& acc, const T_Particle_Species& particles, std::size_t patch_size) const
        {
            using namespace alpaka;
            auto grid_block_idx = idx::getIdx<Grid, Blocks>(acc)[0];
            std::size_t start_particles_idx = grid_block_idx * patch_size;
            std::size_t particles_size = particle_species::get_size(particles);
            std::size_t end_particles_idx = math::min(acc, start_particles_idx  + patch_size, particles_size);

            auto threadIdx = alpaka::idx::getIdx<alpaka::Grid, alpaka::Threads>(acc)[0];

            using T_Particle_type = typename particle_species::traits::Particle_Type<T_Particle_Species>::type;

            auto &algorithm( alpaka::block::shared::st::allocVar<T_Algorithm, __COUNTER__>(acc));

            // 0.  Initialization part

            algorithm.init(algorihtm_parameters);
            block::sync::syncBlockThreads(acc);

            auto const blockSize = alpaka::workdiv::getWorkDiv<alpaka::Block, alpaka::Threads>(acc);

            auto const global_thread_idx = idx::getIdx<alpaka::Grid, alpaka::Threads>(acc);
            auto const global_thread_extent = workdiv::getWorkDiv<alpaka::Grid, alpaka::Threads>(acc);
            auto const linearized_global_threadIdx = idx::mapIdx<1u>(global_thread_idx, global_thread_extent)[0];
            auto generator = alpaka::rand::generator::createDefault(acc, linearized_global_threadIdx, 0);
            auto distribution(alpaka::rand::distribution::createUniformReal<float>(acc));

            auto random_value_generator = [&]{ return distribution(generator); };
            T_Particle_Species& current_particles = const_cast<T_Particle_Species&>(particles);

            // 1. collecting part
            for(int i = start_particles_idx + grid_block_idx; i < end_particles_idx; i = i + blockSize.prod())
            {
                auto& particle = particle_species::get_particle(current_particles, i);

                algorithm.collect(acc, particle, random_value_generator);
            }

            block::sync::syncBlockThreads(acc);

            // 2. processing part
            if (threadIdx == 0)
            {
                algorithm.process(acc, random_value_generator);
            }

            block::sync::syncBlockThreads(acc);

            // 3. reducing part
            for(int i = start_particles_idx + grid_block_idx; i< end_particles_idx; i = i + blockSize.prod())
            {
                auto& particle = particle_species::get_particle(current_particles, i);
                algorithm.reduce(acc, particle, random_value_generator);
            }
        }

    };

} //namespace thinning
}// namespace reduction_library
