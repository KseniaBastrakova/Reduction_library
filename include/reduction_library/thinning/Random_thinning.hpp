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

#include "reduction_library/Particle_getters.hpp"
#include "reduction_library/helpers/Type_list.hpp"
#include "reduction_library/thinning/Thinning.hpp"


namespace reduction_library{
namespace thinning{
/** @file
 * Particle reduction method "number conservative"
 * the idea is that each macro-particle is either removed, with equal
 * probability p = 1−k −1 , or has its weight increased by a factor of k. This method
 * is agnostic because h ŵ i i = 0 · 1 − k −1 + kw i · k −1 = w i . The method does not
 * strictly conserve any quantities such as total weight, energy or momentum, but
 * conserves all quantities on average as any agnostic method. The method can be
 * applied to subsets of any size, which makes it possible to apply it to very small
 * volumes in phase space.
 *
 * Based on "Strategies for particle resampling in PIC simulations" --
 * A. Muraviev, A. Bashinov, E. Efimenko, V. Volokitin, I. Meyerov, A. Gonoskov
 *
 */
    /** Particle reduction with "in kernell" implementation,
     * (particles can be stored in every data structure, but each particle
     * must support functions:
     *
     * getting weight for component::name::SCALAR Componenent and
     * Record record::name::Weight
     *
     */
    class Random_thinning{
    private:
        //-----------------------------------------------------------------------------
        //! Ratio of particles to be deleted (ex: 0.1 = 10%, 0.8 = 80%)
        double ratio_deleted_paticles;
        //-----------------------------------------------------------------------------
        //! the amount of particles remaining after removal
        int num_of_left_particles;
        //-----------------------------------------------------------------------------
        //! Sum of all weights for particles that will be reduced
        double sum_reduced_weights;
        /** The amount of weight that needs to be added to the
         * remaining particles to maintain the total weight
         */
        double part_of_additional_weight;
    public:
        /** Input parameters for algorithm
         *  std:: tuple with
         *  one parameter : ratio of deleted particles (from 0 to 1)
         */
        using Parameters = helpers::Type_list<double>;
        ALPAKA_FN_ACC Random_thinning():
            ratio_deleted_paticles(0),
            num_of_left_particles(0),
            sum_reduced_weights(0.),
            part_of_additional_weight(0.){}

        /** Algorithm initialization:
         *  with tuple, contains:
         *  ratio of deleted particles (from 0 to 1) (double)
         */
          ALPAKA_FN_ACC void init(Random_thinning::Parameters parameters)
          {
              this->ratio_deleted_paticles = std::get<0>(parameters);
              num_of_left_particles = 0;
              sum_reduced_weights = 0.;
              part_of_additional_weight = 0.;
          }
          /** Collecting all particles for reducing
           *
           * make a decision, should algorithm reduce particle, or not
           * base on random value
           * compute sum of weights for deleted particles
           * and number of left particles
           *
           * \tparam Acc Alpaka accelerator type
           * \tparam T_Particle type of particle. Should provide necessary functions
           * for getting and setting parameters
           *
           * \tparam T_Random_Generator type of functor of random generator.
           * Should allow getting stream independent random number
           */
          template<typename Acc, typename T_Particle, typename T_Random_Generator>
          ALPAKA_FN_ACC void collect(Acc const& acc, T_Particle& particle, T_Random_Generator& generator)
          {
              using namespace alpaka;
              double random_value = generator();
              if (random_value < ratio_deleted_paticles)
              {
                 auto weight = particle_access::get_weighting(particle);
                 atomic::atomicOp<atomic::op::Add>(acc, &sum_reduced_weights, (double)weight, hierarchy::Blocks{});
                 particle_access::set_weighting(-1., particle);
              }
              else
              {
                  atomic::atomicOp<atomic::op::Add>(acc, &num_of_left_particles, (int)1, hierarchy::Blocks{});
              }
          }

          /** Compute the amount of weight that needs to be added to the
           * remaining particles to maintain the total weight
           *
           * input parameters (are not used. required for unified logic for all algorithms)
           * \tparam Acc Alpaka accelerator type
           * \tparam T_Random_Generator type of functor of random generator.
           * Should allow getting stream independent random number
           *
           */

          template<typename Acc, typename T_Random_Generator>
          ALPAKA_FN_ACC void process(Acc const& acc, T_Random_Generator& generator)
          {
              part_of_additional_weight = sum_reduced_weights / num_of_left_particles;
          }

          /** Assign all particles with new weight
           *
           * 0 (particles, that marks to be deleted)
           * starting weight + additional weight otherwise
           *
           * \tparam Acc Alpaka accelerator type
           * \tparam T_Random_Generator type of functor of random generator.
           * Should allow getting stream independent random number
           * \tparam T_Particle type of particle. Should provide nessary functions
           * for getting and setting parameters
           *
           */
          template<typename Acc, typename T_Particle, typename T_Random_Generator>
          ALPAKA_FN_ACC void reduce(Acc const& acc, T_Particle& particle, T_Random_Generator& generator) const
          {
              double weight = particle_access::get_weighting(particle);
              if (weight > 0)
              {
                  double result_weight = weight + part_of_additional_weight;
                  particle_access::set_weighting(result_weight, particle);
              }
              else
              {
                  particle_access::set_weighting(0, particle);
              }
          }
    };

} // namespace thinning
} // namespace reduction_library
