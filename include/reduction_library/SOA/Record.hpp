#pragma once

#pragma once

#include <tuple>
#include "reduction_library/helpers/Type_list.hpp"
#include "reduction_library/SOA/Record_getters.hpp"
#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Component.hpp"
#include "reduction_library/SOA/Dataset.hpp"
#include "reduction_library/helpers/Tuple_idx_getters.hpp"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/HINLINE.hpp"

namespace reduction_library{
namespace SOA{

    template <typename T_Names_list, typename T_Component_type_list>
    struct Record{
    public:
        using This = Record<T_Names_list, T_Component_type_list>;
        using Components = T_Component_type_list;
        using Names = T_Names_list;

    private:
        int macroWeighted;
        double weightingPower;
        Names names;
        Components components;
        record::unit_dimension_type unit_dimension;

    public:
        Record():
                  macroWeighted(7),
                  weightingPower(42.),
                  unit_dimension(unit_dimension){}

        double get_weighting_power(){
            return weightingPower;
        }
        int get_macro_weighted(){
            return weightingPower;
        }
        record::unit_dimension_type get_unit_dimension() const{
            return unit_dimension;
        }
        Components& get_components(){
            return components;
        }

    };


}//SOA


namespace record{
namespace traits{

    template<class T_component_name, typename T_Names_list, typename T_Component_type_list>
    struct Type<T_component_name, SOA::Record<T_Names_list, T_Component_type_list>>
    {
        using Record = SOA::Record<T_Names_list, T_Component_type_list>;
        using Names = typename Record::Names;
        using Components = typename Record::Components;

        using type = typename std::tuple_element_t<
                helpers::Index<T_component_name, Names>::value,
                typename Components
               >;
    };
} //namespace traits


    template<class T_component_name, typename T_Names_list, typename T_Component_type_list>
    struct Getting_value<T_component_name, SOA::Record<T_Names_list, T_Component_type_list>>
    {
    public:
        typename traits::Type<T_component_name, SOA::Record<T_Names_list, T_Component_type_list>>::type &
            operator() (SOA::Record<T_Names_list, T_Component_type_list>& record)
        {
            using Record = SOA::Record<T_Names_list, T_Component_type_list>;
            using Names = typename Record::Names;
            constexpr auto idx = helpers::Index<T_component_name, Names>::value;
            return std::get< idx >( record.get_components() );
        }

    };

    template<typename T_Names_list, typename T_Component_type_list>
    struct Geting_weighting_power<SOA::Record<T_Names_list, T_Component_type_list>>
    {
    public:
      double operator() (SOA::Record<T_Names_list, T_Component_type_list>& record)
      {
          return record.get_weighting_power();
      }

    };


    template<typename T_Names_list, typename T_Component_type_list>
    struct Geting_macro_weighted<SOA::Record<T_Names_list, T_Component_type_list>>
    {
    public:
      double operator() (SOA::Record<T_Names_list, T_Component_type_list>&& record)
      {
          return record.get_macro_weighted();
      }

    };


    template<typename T_Names_list, typename T_Component_type_list>
    struct Geting_unit_dimension<SOA::Record<T_Names_list, T_Component_type_list>>
    {
    public:
      unit_dimension_type operator() (SOA::Record<T_Names_list, T_Component_type_list>& record)
      {
          return record.get_unit_dimension();
      }

    };


    template<typename ... T_Names, typename ... T_Component_types>
    auto make_species(T_Component_types& ...  records)
    {
        using Names = helpers::Type_list< T_Names ... >;
        using Record_types = helpers::Type_list<T_Component_types ... >;
        using Record = SOA::Record< Names, Record_types>;
        Record_types input_records(records...);
        Species species(input_records);
        return species;
    }
  //  SOA::Record_3d<T_X_component, T_Y_component, T_Z_component>
   //     make_momentum_record(SOA::Component<T_X_component> x_component,
    //                       SOA::Component<T_Y_component> y_component,
     //                      SOA::Component<T_Z_component> z_component)
   // {
     //     }


} // namespace record

}// reduction_library

