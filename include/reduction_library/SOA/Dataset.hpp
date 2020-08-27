#pragma once

#include <vector>

namespace reduction_library{
namespace SOA{

template<typename T_Value>
struct Dataset{
public:
    using Value_type = T_Value;
private:
    std::vector<Value_type> values;
public:
    Dataset(){}
    Dataset(std::vector<Value_type> values):
        values(values){}

    std::vector<Value_type> get_values(){
        return values;
    }
    void set_values(const std::vector<Value_type>& new_values){
        values = new_values;
    }

    Value_type& operator[](int idx)
    {
        return values[idx];
    }
    void set_value(Value_type value, int idx){
        values[idx] = value;
    }

    /// We use this functions only for test
    void print(){
        for (int i=0; i<values.size(); i++)
            std::cout<<values[i]<<"  ";
        std::cout<<std::endl;
    }
};

}  // namespace SOA
} // namespace reduction_library
