#pragma once

#include <tuple>
#include "reduction_library/record/Name.hpp"
#include "reduction_library/SOA/Particle.hpp"
#include "reduction_library/particle_species/Type.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"


namespace reduction_library{
namespace SOA{

    template <typename T_First_record, typename T_Second_record>
    class Particle_species{
    public:
        int size;
        T_First_record first_record;
        T_Second_record second_record;
    public:
        using MyParticle = Particle<Particle_species>;
        Particle_species(T_First_record first_record, T_Second_record second_record):
            first_record(first_record), second_record(second_record)
        {
            size = 5.;
        }

        MyParticle getParticle(int idx){
            return MyParticle(idx, *this);
        }
        int getSize(){
            return size;
        }

    };

} // SOA

namespace particle_species{
namespace traits{

    template<typename T_First_record, typename T_Second_record>
    struct Type<record::Name::momentum, SOA::Particle_species<T_First_record,T_Second_record>>
    {
        using type = T_First_record;
    };

    template<typename T_First_record, typename T_Second_record>
    struct Type<record::Name::weighting, SOA::Particle_species<T_First_record,T_Second_record>>
    {
        using type = T_Second_record;
    };

} // namespace traits

template<typename T_First_record, typename T_Second_record>
struct Getting_value<record::Name::momentum, SOA::Particle_species<T_First_record,T_Second_record>>
{
public:
    typename traits::Type<record::Name::momentum, SOA::Particle_species<T_First_record,T_Second_record>>::type &
        operator() (SOA::Particle_species<T_First_record,T_Second_record>& particle_species)
    {
        return particle_species.first_record;
    }

};


template<typename T_First_record, typename T_Second_record>
struct Getting_value<record::Name::weighting, SOA::Particle_species<T_First_record,T_Second_record>>
{
public:
    typename traits::Type<record::Name::weighting, SOA::Particle_species<T_First_record,T_Second_record>>::type &
        operator() (SOA::Particle_species<T_First_record,T_Second_record>& particle_species)
    {
        return particle_species.second_record;
    }

};

} // namespace particle_spicies
} // reduction_library
