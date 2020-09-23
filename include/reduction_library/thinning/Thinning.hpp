#pragma once

#include <vector>

#include "include/reduction_library/thinning/KernelThinning.hpp"

namespace reduction_library{
namespace thinning{

template<class T_particles>
class Thinning{
private:
    double ratioDeletedPaticles;
public:
    Thinning(double ratioDeletedPaticles):
        ratioDeletedPaticles(ratioDeletedPaticles){}

    template<class T_particle>
    void operator()(std::vector<T_particle>& particles) const{

        KernelThinning<T_particle> thinningKernell(ratioDeletedPaticles);

         for (T_particle& particle : particles){
             thinningKernell.collect(particle);
         }
         thinningKernell.process();

         for (T_particle& particle : particles){
             thinningKernell.reduce(particle);
        }
    }

    void operator()(T_particles& particles){}

};
} //thinning
} //reduction_library
