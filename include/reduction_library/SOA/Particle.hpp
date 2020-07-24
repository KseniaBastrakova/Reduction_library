#pragma once

#include "reduction_library/component/Interfaces.hpp"
//#include "reduction_library/component/Name.hpp"
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
    class Particle_spicies;


  //  template <>
  //  record_component::traits::Type<record_component::Name::x>
  //  record_component::get_attribute<Particle<Particle_spicies>, record_component::Name::x>(Particle<Particle_spicies>& particle);

   // template <>
 //   record_component::traits::Type<record_component::Name::y>
//    record_component::get_attribute<Particle<Particle_spicies>, record_component::Name::y>(Particle<Particle_spicies>& particle);
//

 //   };




}
