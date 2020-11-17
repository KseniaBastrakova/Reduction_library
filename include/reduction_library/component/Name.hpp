#pragma once

namespace reduction_library{
namespace component{

/** Base component names, based on openPMD standard naming
 *  https://github.com/openPMD/openPMD-standard/blob/latest/STANDARD.md
 *  include сartesian coordinate system, cylindrical coordinate system
 *  and special name for physical constants
*/
namespace Name{
    struct X {}; // x axis
    struct Y {}; // y axis
    struct Z {}; // z axis
    struct R {}; // polar axis
    struct T {}; // longitudinal axis
    struct SCALAR {}; // name for physical constants (mass, charge ...)
};

} //namespace component
} //namespace reduction_library
