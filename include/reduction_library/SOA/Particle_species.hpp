#pragma once

#include "reduction_library/record/Name.hpp"
#include "reduction_library/SOA/Record_scalar.hpp"
#include "reduction_library/SOA/Record_3d.hpp"
#include "reduction_library/SOA/Particle.hpp"


namespace reduction_library{
namespace SOA{

    template <typename T_First_record, typename T_Second_record>
    class Particle_spicies{
        int size;
        T_First_record first_record;
        T_Second_record second_record;
    public:
        using MyParticle = Particle<Particle_spicies>;
        Particle_spicies(T_First_record first_record, T_Second_record second_record):
            first_record(first_record), second_record(second_record)
        {
            size = first_record.get_size();
        }

        MyParticle getParticle(int idx){
            return MyParticle(idx, *this);
        }
        int getSize(){
            return size;
        }

    };

} // SOA
} // reduction_library
