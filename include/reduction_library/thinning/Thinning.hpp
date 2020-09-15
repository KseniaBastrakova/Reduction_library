#pragma once

#include <vector>

#include "reduction_library/thinning/KernelThinning.hpp"

namespace reduction_library{
namespace thinning{

template<class T_particles>
class Thinning{
private:
    double ratioDeletedPaticles;
public:
    Thinning(double ratioDeletedPaticles):
        ratioDeletedPaticles(ratioDeletedPaticles){}

    template<class T_particle, typename Acc>
    ALPAKA_FN_ACC void operator()(Acc const& acc, std::vector<T_particle>& particles) const{
        KernelThinning<T_particle> thinningKernell(ratioDeletedPaticles);
        using namespace alpaka;
        uint32_t threadIdx = idx::getIdx<Grid, Threads>(acc)[0];

        auto distribution = rand::distribution::createNormalReal<double>(acc);
        auto seed = 1;
        auto subsequence = 2;
        auto generator = rand::generator::createDefault(acc, seed, subsequence);
        auto random_value = distribution(generator);
         for (T_particle& particle : particles){
             thinningKernell.collect(particle);
         }
         thinningKernell.process();

      //   T_particle particle, double random_value
         for (T_particle& particle : particles){
             thinningKernell.reduce(particle, random_value);
        }
    }

    void operator()(T_particles& particles){}

};
} //thinning
} //reduction_library
