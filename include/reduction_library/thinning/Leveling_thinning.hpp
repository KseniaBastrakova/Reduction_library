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
#include "reduction_library/thinning/Thinning.hpp"

namespace reduction_library{
namespace thinning{

class Leveling_thinning{

private:
    double ratio_deleted_paticles;
    double num_particles;
    double average_weight;
    double sum_weights;
public:
    ALPAKA_FN_ACC Leveling_thinning():
        ratio_deleted_paticles(0.),
        num_particles(0.),
        average_weight(0.),
        sum_weights(0.){}

      ALPAKA_FN_ACC void init(double ratio_deleted_paticles)
      {
          this->ratio_deleted_paticles = ratio_deleted_paticles;
          num_particles = 0;
          average_weight = 0.;
          sum_weights = 0.;
      }

      template<typename Acc, typename T_Particle, typename T_Random_Generator>
      ALPAKA_FN_ACC void collect(Acc const& acc, T_Particle particle, T_Random_Generator& generator)
      {
          using namespace alpaka;
          auto weight = particle_access::get_weighting(particle);
          atomic::atomicOp<atomic::op::Add>(acc, &sum_weights, (double)weight, hierarchy::Blocks{});
          atomic::atomicOp<atomic::op::Add>(acc, &num_particles, (int)1, hierarchy::Blocks{});
      }

      template<typename Acc>
      ALPAKA_FN_ACC void process(Acc const& acc)
      {
          average_weight = sum_weights / num_particles;
      }

      template<typename Acc, typename T_Particle, typename T_Random_Generator>
      ALPAKA_FN_ACC void reduce(Acc const& acc, T_Particle& particle, T_Random_Generator& generator)
      {
          using namespace alpaka;
          double random_value = generator();
          auto weight = particle_access::get_weighting(particle);
          if (random_value < (ratio_deleted_paticles * weight) / average_weight)
          {
              auto new_weight = average_weight / ratio_deleted_paticles;
              particle_access::set_weighting(new_weight,  particle);
          }
          else
          {
              particle_access::set_weighting(0, particle);
          }
      }

};

} // namespace thinning
} // namespace reduction_library
