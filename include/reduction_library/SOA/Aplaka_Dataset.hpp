#pragma once
#include <vector>
#include <iostream>
#include <alpaka/alpaka.hpp>

namespace reduction_library{
namespace SOA{

template<typename Acc, typename T_Value>
struct Aplaka_Dataset{
public:
    using Dim = alpaka::dim::DimInt<1u>;
    using Idx = std::size_t;
    using BufAcc = alpaka::mem::buf::Buf<Acc, T_Value, Dim, Idx>;
    using Value_type = T_Value;
private:
    BufAcc values;
public:
    Aplaka_Dataset(){}
    Aplaka_Dataset(BufAcc values):
        values(values){}

    BufAcc* get_values(){
        return values;
    }
    void set_values(BufAcc new_values){
        values = new_values;
    }
    std::size_t get_size(){
    	return Acc::Idx;
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
