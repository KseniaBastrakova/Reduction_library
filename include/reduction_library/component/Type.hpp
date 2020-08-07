#pragma once

namespace reduction_library{
namespace component{

namespace traits{

    template<typename T_component>
    struct Type;

} //traits

    template<typename T_component>
    using Type = typename traits::Type<T_component>::type;

}//component
}//reduction_library
