#pragma once

#include <vector>

namespace reduction_library{
namespace SOA{

template<typename T_Value>
struct Dataset{
private:
    std::vector<T_Value> values;
public:
    Dataset(){}
    Dataset(std::vector<T_Value> values):
        values(values){}

    std::vector<T_Value> get_values(){
        return values;
    }
    void set_values(const std::vector<T_Value>& new_values){
        values = new_values;
    }

    T_Value& operator[](int idx)
    {
        return values[idx];
    }

    /// We use this functions only for test
    void print(){
        for (int i=0; i<values.size(); i++)
            std::cout<<values[i]<<std::endl;
    }
};

}  // namespace SOA
} // namespace reduction_library
