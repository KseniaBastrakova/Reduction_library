#pragma once

#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/attribute/Attributes_types.hpp"
#include "reduction_library/attribute/Type.hpp"

namespace reduction_library{
namespace attribute{

    template<typename T_particle, Attribute T_attribute>
    HDNLINE void set_attribute(T_particle & particle, attribute::traits::Type<T_particle, T_attribute> value );

    template<typename T_particle, Attribute T_attribute>
    HDNLINE
    attribute::traits::Type<T_particle, T_attribute> get_attribute(T_particle & particle);

//    template<typename T_particle>
  //  double& get_momentum(T_particle& particle)
   // {
   // return get_attribute<T_particle, Attribute::momentum_x>(particle);
   // }

   // template<typename T_particle>
   // double& get_weighting(T_particle& particle)
   // {
   // return get_attribute<T_particle, Attribute::weighting>(particle);
   // }

} //attribute
} //reduction_library
