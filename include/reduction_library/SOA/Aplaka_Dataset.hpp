#pragma once
#include <vector>
#include <iostream>
#include <alpaka/alpaka.hpp>

namespace reduction_library{
namespace SOA{

template<typename T_Bufer, typename T_Value>
struct Aplaka_Dataset{
public:
    using Value_type = typename T_Bufer::Data;
private:
    T_Bufer values;
public:
    Aplaka_Dataset(){}
    Aplaka_Dataset(T_Bufer values):
        values(values){}

    std::vector<Value_type> get_values(){
        return values;
    }
    void set_values(T_Bufer new_values){
        values = new_values;
    }
    std::size_t get_size(){
    	return T_Bufer::Idx;
    }
    auto* start(){
    	return alpaka::mem::view::getPtrNative(values);
    }

    Value_type& operator[](int idx)
    {
    	auto p_values = alpaka::mem::view::getPtrNative(values);
        return p_values[idx];
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
