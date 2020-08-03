#pragma once

//#include "reduction_library/component/Interfaces.hpp"
//#include "reduction_library/Scalar_records_names.hpp"
//#include "reduction_library/component/Type.hpp"

namespace reduction_library{

    template<class Particle_type>
    class Particle{
    public:
        int idx;
        Particle_type &baseParticles;
        Particle(int idx, Particle_type &baseParticles):
            idx(idx), baseParticles(baseParticles){}
    };

}
