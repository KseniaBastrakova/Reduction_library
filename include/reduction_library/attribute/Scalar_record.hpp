#pragma once

#include <vector>
#include <iostream>

namespace reduction_library{
namespace attribute{

    template<Scalar_records_names T_scalar_record, class T_Value>
    class Scalar_record {
        std::vector<T_Value> values;
        int macroWeighted;
        double weightingPower;
    public:
        Scalar_record(std::vector<T_Value>& values):
            values(values), weightingPower(42), macroWeighted(1){}
        std::vector<T_Value>& get(){
            return values;
        }

    };
 //   template<scalar record T_scalar record, class T_particle_spicies>
  //  double get_weighting_power(Attribute attribute, T_particle_spicies particle_spicies);

} //attribute
} //reduction_library
