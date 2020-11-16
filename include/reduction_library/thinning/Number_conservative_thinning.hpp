#pragma once

#include <vector>
#include <functional>
#include <alpaka/alpaka.hpp>
#include "reduction_library/Particle.hpp"
#include "reduction_library/thinning/helpers/Sample_getting.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"

namespace reduction_library{
namespace thinning{

class Number_conservative_thinning{
private:
    double ratio_deleted_paticles;
    double *weights;
    double sum_weights;
    int number_particles;

public:
    ALPAKA_FN_ACC Number_conservative_thinning():
        ratio_deleted_paticles(0),
        sum_weights(0),
        number_particles(0),
        weights(NULL){}

    ALPAKA_FN_ACC void init(double ratioDeletedPaticles, double *p_memory, int number_particles)
    {
        this->ratio_deleted_paticles = ratioDeletedPaticles;
        this->weights = p_memory;
    }

    template<typename Acc, typename T_Particle, typename T_Random_Generator>
    ALPAKA_FN_ACC void collect(Acc const& acc, T_Particle& particle, const T_Random_Generator& generator)
    {
        using namespace alpaka;
        double weight = particle_access::get_weighting(particle);
        atomic::atomicOp<atomic::op::Add>(acc, &sum_weights, (double)weight, hierarchy::Blocks{});
        int particle_idx = particle.get_idx();
        this->weights[particle_idx] = weight;
    }

    template<typename Acc, typename T_Random_Generator>
    ALPAKA_FN_ACC void process(Acc const& acc, const T_Random_Generator& generator)
    {
        Getting_n_inc_weighted_sample<double, T_Random_Generator> sample_getter;
        std::vector<double> normalize_weights(weights, weights + number_particles);

        std::transform(normalize_weights.begin(), normalize_weights.end(), normalize_weights.begin(),
                       std::bind(std::divides<double>(), std::placeholders::_1, sum_weights));

        std::size_t m_times = (std::size_t)(-1 * number_particles * log(1 - ratio_deleted_paticles));
        std::vector<double> number_of_inc = sample_getter(normalize_weights, m_times, generator);
        for (int i = 0; i < number_of_inc.size(); i++)
        {
            weights[i] = number_of_inc[i] * sum_weights / m_times;
        }
    }

    template<typename Acc, typename T_Particle, typename T_Random_Generator>
    ALPAKA_FN_ACC void reduce(Acc const& acc, T_Particle& particle, const T_Random_Generator& generator) const
    {
        int particle_idx = particle.get_idx();
        double new_weight = weights[particle_idx];
        particle_access::set_weighting(new_weight, particle);

    }
};

} //thinning
} //reduction_library
