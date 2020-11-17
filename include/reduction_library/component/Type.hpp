#pragma once

namespace reduction_library{
namespace component{
/** Component object traits
 *  represent compile time type for given template component
*/

namespace traits{

//---------------------------------------------------------------------------------------
//! Returns component's storage type
template<typename T_Component>
struct Type;

} //traits

//---------------------------------------------------------------------------------------
//! Returns typename of component's storage type
template<typename T_Component>
using Type = typename traits::Type<T_Component>::type;

}//component
}//reduction_library
