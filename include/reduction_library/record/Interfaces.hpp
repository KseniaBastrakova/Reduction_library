#pragma once

#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/record/Type.hpp"

namespace reduction_library{
namespace record{

/**record object interface
 * the idea of record interface, functions and attributes
 * based on openPMD record:
 * https://github.com/openPMD/openPMD-standard/blob/latest/STANDARD.md
 * and necessity for merging and tinning algorithms
 *
 * example of defining can be founded in SOA::Record
 * This interface provides getting weighting power,
 * getting unit dimension, getting component
*/

/** Unit dimention type: basetd on openPMD init dinesion idea
 * of powers of the 7 base measures characterizing the record's unit in SI
 * (length L, mass M, time T, electric current I,
 * thermodynamic temperature theta, amount of substance N, luminous intensity J)
*/
using unit_dimension_type = std::array<int, 7>;

template<typename T_Record>
struct Geting_unit_dimension;

template<typename T_Record>
double getting_unit_dimension(T_Record& record)
{
    Geting_unit_dimension<T_Record> ud_get_functor;
    return ud_get_functor.operator ()(record);
}


template<typename T_Record>
struct Geting_weighting_power;

template<typename T_Record>
double get_weighting_power(T_Record& record)
{
    Geting_weighting_power<T_Record> wp_get_functor;
    return wp_get_functor.operator ()(record);
}

template<typename T_Record>
struct Geting_macro_weighted;

template<typename T_Record>
double get_macro_weighted(T_Record&& record)
{
    Geting_macro_weighted<T_Record> mw_get_functor;
    return mw_get_functor.operator ()(std::move(record));
}

template<typename T_Record>
struct Geting_unit_dimension;

template<typename T_Record>
unit_dimension_type get_unit_dimension(T_Record& record)
{
    Geting_unit_dimension<T_Record> ud_get_functor;
    return ud_get_functor.operator ()(record);
}

template<typename T_Component_Name, typename T_Record>
struct Getting_value;

template<typename T_Component_Name, typename T_Record>
HDNLINE typename traits::Type<T_Component_Name, T_Record>::type & get(T_Record& record){
    Getting_value<T_Component_Name, T_Record> v_get_functor;
    return v_get_functor.operator() (record);

}

} // namespace record
} //namespace reduction_library
