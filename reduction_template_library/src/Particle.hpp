#pragma once
#include "Atributes_types.hpp"
#include "AtrributeChunk.hpp"

namespace reduction_library{

    template<class Particle_type>
    class Particle{
    public:
        int idx;
        Particle_type &baseParticles;
        Particle(int idx, Particle_type &baseParticles):
            idx(idx), baseParticles(baseParticles){}
    };
    class Particles;

    template <>
    double& get_attribute<Particle<Particles>, Attribute::momentum_x>(Particle<Particles>& particle);


    template <>
    double& get_attribute<Particle<Particles>, Attribute::weighting>(Particle<Particles>& particle);

}


//template<typename Particle_type>
//double& get_momentum(Particle<Particle_type>& particle)
//{
//	return 0; //get_attribute<T_particle, Attribute::momentum>(particle);
//}

//template<typename Particle_type>
//double& get_weighting(Particle<Particle_type>& particle)
//{
//	return 0; // get_attribute<T_particle, Attribute::weighting>(particle);
//}

//template<typename Particle_type, Attribute attribute>
//double& get_attribute(Particle<Particle_type>& particle){
	//return 0;

//}
