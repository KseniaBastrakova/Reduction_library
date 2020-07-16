#pragma once
#include "Attributes_types.hpp"
#include "attribute/Type.hpp"

#define DINLINE inline

namespace reduction_library{


    template<typename T_particle, Attribute T_attribute>
    DINLINE
    attribute::Type<T_particle, T_attribute>& set_attribute(T_particle & particle);

    template<typename T_particle, Attribute T_attribute>
    DINLINE
    attribute::Type<T_particle, T_attribute> get_attribute(T_particle & particle);

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
}
