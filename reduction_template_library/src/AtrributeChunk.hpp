#pragma once
#include <vector>
#include <iostream>
#include "Attributes_types.hpp"

namespace reduction_library{

    template<Attribute T_attribute, class T_Value>
    class AtrributeChunk {
        std::vector<T_Value> values;
    public:
        AtrributeChunk(std::vector<T_Value>& values):
            values(values){}
        std::vector<T_Value>& get(){
            return values;
        }

    };
}
