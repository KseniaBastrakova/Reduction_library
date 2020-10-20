#pragma once

#include <vector>

#include "reduction_library/thinning/In_kernel_thinning.hpp"

namespace reduction_library{
namespace thinning{
/*
template<class T_particles>
class Thinning_alpaka_kernell{
private:
    double ratioDeletedPaticles;
public:
    Thinning_alpaka_kernell(double ratioDeletedPaticles):
        ratioDeletedPaticles(ratioDeletedPaticles){}

    template<class T_particle>
    void operator()(std::vector<T_particle>& particles) const{

    	In_kernel_thinning<T_particle> thinningKernell(ratioDeletedPaticles);

         for (T_particle& particle : particles){
             thinningKernell.collect(particle);
         }
         thinningKernell.process();

         for (T_particle& particle : particles){
             thinningKernell.reduce(particle);
        }
    }

    void operator()(T_particles& particles){}

};*/
} //thinning
} //reduction_library
