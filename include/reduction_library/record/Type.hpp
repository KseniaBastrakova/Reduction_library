#pragma once

#include "reduction_library/component/Name.hpp"

namespace reduction_library{
namespace record{
namespace traits{

/** Record object traits
 *  represent types for record's attributes
*/


/** Main
 *  represent types for components's attributes
*/
template<typename T_Component_Name, typename T_Record>
    struct Type;

template<typename T_Record>
    struct Component_names;

} //traits

template<typename T_component_name, typename T_Record>
struct Type{
    using type = typename record::traits::Type<T_component_name, T_Record>::type;

};

template<typename T_Record>
struct Component_names{
    using type = typename record::traits::Component_names<T_Record>::type;

};
} //record
} //reduction_library
