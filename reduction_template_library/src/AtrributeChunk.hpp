#pragma once
#include "Atributes_types.hpp"
#include <vector>

template<Attribute T_attribute , class T_Value>
class AtrributeChunk {
	std::vector<T_Value> values;
public:
	AtrributeChunk(std::vector<T_Value>& values):
		values(values){}
	std::vector<T_Value>& get(){
		return values;
	}

};
