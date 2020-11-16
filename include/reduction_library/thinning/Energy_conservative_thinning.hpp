#pragma once

#include <vector>
#include <functional>
#include <alpaka/alpaka.hpp>
#include "reduction_library/Particle.hpp"
#include "reduction_library/thinning/helpers/Sample_getting.hpp"
#include "reduction_library/thinning/helpers/Energy_counting.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"

namespace reduction_library{
namespace thinning{

class Energy_conservative_thinning{
private:
    double ratio_deleted_paticles;
    double *energyes;
    double sum_weighted_energyes;
    int number_particles;

public:
    ALPAKA_FN_ACC Energy_conservative_thinning():
        ratio_deleted_paticles(0),
        sum_weighted_energyes(0),
        number_particles(0),
        energyes(NULL){}

    ALPAKA_FN_ACC void init(double ratioDeletedPaticles, double *p_memory, int number_particles)
    {
        this->ratio_deleted_paticles = ratioDeletedPaticles;
        this->energyes = p_memory;
    }

    template<typename Acc, typename T_Particle, typename T_Random_Generator>
    ALPAKA_FN_ACC void collect(Acc const& acc, T_Particle& particle, const T_Random_Generator& generator)
    {
        using namespace alpaka;
        Getting_particle_energy<T_Particle> counter;
        double energy = counter(particle);
        double weight = particle_access::get_weighting(particle);
        double weighted_energy = energy * weight;
        atomic::atomicOp<atomic::op::Add>(acc, &sum_weighted_energyes, (double)weighted_energy, hierarchy::Blocks{});
        int particle_idx = particle.get_idx();
        this->energyes[particle_idx] = energy;
    }

    template<typename Acc, typename T_Random_Generator>
    ALPAKA_FN_ACC void process(Acc const& acc, const T_Random_Generator& generator)
    {
        Getting_n_inc_weighted_sample<double, T_Random_Generator> sample_getter;
        std::vector<double> weighted_energy(energyes, energyes + number_particles);

        std::transform(weighted_energy.begin(), weighted_energy.end(), weighted_energy.begin(),
                       std::bind(std::divides<double>(), std::placeholders::_1, sum_weighted_energyes));

        std::size_t m_times = (std::size_t)(-1 * number_particles * log(1 - ratio_deleted_paticles));
        std::vector<double> number_of_inc = sample_getter(weighted_energy, m_times, generator);
        for (int i = 0; i < number_of_inc.size(); i++)
        {
            energyes[i] = number_of_inc[i] * sum_weighted_energyes / m_times;
        }
    }

    template<typename Acc, typename T_Particle, typename T_Random_Generator>
    ALPAKA_FN_ACC void reduce(Acc const& acc, T_Particle& particle, const T_Random_Generator& generator) const
    {
        using namespace alpaka;
        Getting_particle_energy<T_Particle> counter;
        double energy = counter(particle);
        int particle_idx = particle.get_idx();
        double new_weight = energyes[particle_idx] / energy;
        particle_access::set_weighting(new_weight, particle);

    }
};

} //thinning
} //reduction_library
