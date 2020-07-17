#pragma once

#include <vector>

#include "reduction_library/thinning/KernelThinning.hpp"

namespace reduction_library{
namespace thinning{

    class Thinning{
    private:
        double ratioDeletedPaticles;
    public:
        Thinning(double ratioDeletedPaticles):
            ratioDeletedPaticles(ratioDeletedPaticles){}

        template<class T_particle>
        void operator()(std::vector<T_particle>& particles){
            KernelThinning<T_particle> thinningKernell(ratioDeletedPaticles);
             for (T_particle& particle : particles){
                 thinningKernell.collect(particle);
             }
             thinningKernell.process();

             for (T_particle& particle : particles){
                 thinningKernell.reduce(particle);
            }
        }
        template<class T_particles>
        void operator()(T_particles& particles){}

    };
} //thinning
} //reduction_library