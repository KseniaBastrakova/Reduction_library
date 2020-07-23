#pragma once

#include "reduction_library/Scalar_records_names.hpp"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/record_component/Traits.hpp"
#include <vector>
#include <iostream>

namespace reduction_library{
namespace attribute{

    template<Scalar_records_names T_scalar_record, class T_Value>
    class Record_component {
        std::vector<T_Value> values;
        int macroWeighted;
        double weightingPower;
    public:
        Record_component(std::vector<T_Value>& values):
            values(values), weightingPower(42), macroWeighted(1){}
        std::vector<T_Value>& get(){
            return values;
        }
        double get_weighting_power(){
            return weightingPower;
        }
        int get_macro_weighted(){
            return weightingPower;
        }

    };




} //attribute
} //reduction_library
