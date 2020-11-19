/// TODO: copyright

#pragma once


/** @file
 *
 * Define name tags to identify components inside records
 *
 * This file implements the standard openPMD component names for the scalar, Cartesian and cylindrical cases
 * https://github.com/openPMD/openPMD-standard/blob/latest/STANDARD.md#scalar-vector-and-tensor-records .
 * For these standard cases, the following names must be used.
 * For other cases, a user is free to use any unique type tags, no requirements are posed on those.
 */

namespace reduction_library{
namespace component{
/// TODO: why capitalized?
namespace Name{
        
    //! Tag for X Cartesian component
    struct X {};
    
    //! Tag for Y Cartesian component
    struct Y {};
    
    //! Tag for Z Cartesian or cylindrical component
    struct Z {};
    
    //! Tag for radial cylindrical component
    struct R {};
    
    /// TODO: old "longitudinal axis" seems wrong, clarify what is it
    struct T {};
    
    //! Tag for (the only) components of scalar records
    /// TODO: Why capitalized? The standard does not have it like that, only the API
    struct SCALAR {};
    
} /// TODO
} //namespace component
} //namespace reduction_library
