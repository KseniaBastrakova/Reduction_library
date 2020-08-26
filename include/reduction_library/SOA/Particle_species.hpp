#pragma once

#include <tuple>
#include "reduction_library/helpers/Tuple_idx_getters.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/SOA/Particle.hpp"
#include "reduction_library/particle_species/Type.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"


namespace reduction_library{
namespace SOA{

    template <typename T_First_record, typename T_Second_record>
    class Particle_species{
    public:
        using MyParticle = Particle<Particle_species>;
        using Records = std::tuple<T_First_record, T_Second_record>;
        using Names = std::tuple<record::Name::Momentum, record::Name::Weighting>;
        int size;

    public:
        Records records;
        Particle_species(){}
        Particle_species(T_First_record first_record, T_Second_record second_record):
            records(first_record, second_record)
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

    template<typename T_record_name, typename T_First_record, typename T_Second_record>

    struct Type<T_record_name, SOA::Particle_species<T_First_record, T_Second_record>>
    {
        using Species = SOA::Particle_species<T_First_record, T_Second_record>;
        using Names = typename SOA::Particle_species<T_First_record, T_Second_record>::Names;
        using type = typename std::tuple_element_t<
                helpers::Index<T_record_name, Names>::value,
            typename SOA::Particle_species<T_First_record,T_Second_record>::Records
         >;
    };


} // namespace traits

    template<typename T_record_name, typename T_First_record, typename T_Second_record>
    struct Getting_value<T_record_name, SOA::Particle_species<T_First_record, T_Second_record>>
    {
    public:
        auto& operator() (SOA::Particle_species<T_First_record,T_Second_record>& particle_species)
        {
            using Names = typename SOA::Particle_species<T_First_record, T_Second_record>::Names;
            constexpr auto idx = helpers::Index<T_record_name, Names>::value;
            return std::get< idx >( particle_species.records );
        }
    };


} // namespace particle_spicies
} // reduction_library
