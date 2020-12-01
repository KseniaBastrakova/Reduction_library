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

#include "reduction_library/helpers/Type_list.hpp"
#include "reduction_library/thinning/Thinning.hpp"
#include "reduction_library/Particle.hpp"


namespace reduction_library{
namespace thinning{

class Random_thinning{

private:
    double ratio_deleted_paticles;
    int    num_of_left_particles;
    double sum_reduced_weights;
    double part_of_additional_weight;
public:
    using Parameters = helpers::Type_list<double>;
    ALPAKA_FN_ACC Random_thinning():
        ratio_deleted_paticles(0),
        num_of_left_particles(0),
        sum_reduced_weights(0.),
        part_of_additional_weight(0.){}

      ALPAKA_FN_ACC void init(Random_thinning::Parameters parameters)
      {
          this->ratio_deleted_paticles = std::get<0>(parameters);
          num_of_left_particles = 0;
          sum_reduced_weights = 0.;
          part_of_additional_weight = 0.;
      }

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

      template<typename Acc, typename T_Random_Generator>
      ALPAKA_FN_ACC void process(Acc const& acc, T_Random_Generator& generator)
      {
          part_of_additional_weight = sum_reduced_weights / num_of_left_particles;
      }

      template<typename Acc, typename T_Particle, typename T_Random_Generator>
      ALPAKA_FN_ACC void reduce(Acc const& acc, T_Particle& particle, T_Random_Generator& generator) const
      {
          double weight = particle_access::get_weighting(particle);
          if ( weight > 0 )
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
