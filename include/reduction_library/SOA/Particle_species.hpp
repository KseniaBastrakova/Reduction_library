#pragma once

#include <tuple>
#include "reduction_library/helpers/Tuple_idx_getters.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/SOA/Particle.hpp"
#include "reduction_library/particle_species/Type.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"
#include "reduction_library/helpers/Type_list.hpp"



namespace reduction_library{
namespace SOA{

    template <typename T_Names_list, typename T_Record_type_list>
    class Particle_species{
    public:
        using My_particle = Particle<Particle_species>;
        using Records = T_Record_type_list;
        using Names = T_Names_list;
        int size;
    public:
        Records records;
        Particle_species(){}
        Particle_species(T_Record_type_list records):
            records(records){}

        My_particle getParticle(int idx){
            return MyParticle(idx, *this);
        }
        int getSize(){
            return size;
        }

    };

} // SOA

namespace particle_species{
namespace traits{

    template<typename T_record_name, typename T_Names_list, typename T_Record_type_list>
    struct Type<T_record_name, SOA::Particle_species<T_Names_list, T_Record_type_list>>
    {
        using Species = SOA::Particle_species<T_Names_list, T_Record_type_list>;
        using Names = typename Species::Names;
        using type = typename std::tuple_element_t<
                helpers::Index<T_record_name, Names>::value,
                typename Species::Records
         >;
    };
} // namespace traits

    template<typename T_record_name, typename T_Names_list, typename T_Record_type_list>
    struct Getting_value<T_record_name, SOA::Particle_species<T_Names_list, T_Record_type_list>>
    {
    public:
        auto& operator() (SOA::Particle_species<T_Names_list, T_Record_type_list>& particle_species)
        {
            using Names = typename SOA::Particle_species<T_Names_list, T_Record_type_list>::Names;
            constexpr auto idx = helpers::Index<T_record_name, Names>::value;
            return std::get< idx >( particle_species.records );
        }
    };

    template<typename ... T_Names, typename ... T_Record_types>
    auto make_species(T_Record_types& ...  records)
    {
        using Names = helpers::Type_list< T_Names ... >;
        using Record_types = helpers::Type_list<T_Record_types ...>;
        using Species = SOA::Particle_species< Names, Record_types>;
        Record_types input_records(records...);
        Species species(input_records);
        return species;
    }


} // namespace particle_spicies
} // reduction_library
