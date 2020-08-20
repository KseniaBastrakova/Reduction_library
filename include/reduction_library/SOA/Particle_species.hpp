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
       // T_First_record first_record;
      //  T_Second_record second_record;
    public:
        using MyParticle = Particle<Particle_species>;
        using Records = std::tuple<T_First_record, T_Second_record>;
        Records records;
        Particle_species(){}
        Particle_species(T_First_record first_record, T_Second_record second_record):
            records(first_record, second_record)
           // first_record(first_record), second_record(second_record)
        {
            size = 5.;
        }

        MyParticle getParticle(int idx){
            return MyParticle(idx, *this);
        }
        int getSize(){
            return size;
        }

        template< record::Name T_record_name >
        constexpr static size_t getIndex()
        {
            return T_record_name == record::Name::momentum ? 0 :
                T_record_name == record::Name::weighting ? 1 : 2;
        }
    };

} // SOA


namespace particle_species{
namespace traits{

constexpr size_t getIndex()
  {
      return 0;
  }

    template<record::Name T_record_name, typename T_First_record, typename T_Second_record>
    struct Type<T_record_name, SOA::Particle_species<T_First_record, T_Second_record>>
    {
        using type = std::tuple_element_t<
           getIndex(),
            SOA::Particle_species<T_First_record,T_Second_record>::Records
         >;
    };


} // namespace traits

    template<record::Name T_record_name, typename T_First_record, typename T_Second_record>
    struct Getting_value<T_record_name, SOA::Particle_species<T_First_record, T_Second_record>>
    {
    public:
        auto operator() (SOA::Particle_species<T_First_record,T_Second_record>& particle_species)
        {
            constexpr auto idx = SOA::Particle_species<T_First_record,T_Second_record>::getIndex< T_record_name >();
            return std::get< idx >( particle_species.records );
        }


    };


} // namespace particle_spicies
} // reduction_library
