#pragma once

#include <vector>
#include <iostream>

namespace reduction_library{
namespace attribute{

    template<Attribute T_attribute, class T_Value>
    class AtrributeChunk {
        std::vector<T_Value> values;
        int macroWeighted;
        double weightingPower;
    public:
        AtrributeChunk(std::vector<T_Value>& values):
            values(values), macroWeighted(42){}
        std::vector<T_Value>& get(){
            return values;
        }

    };

} //attribute
} //reduction_library
