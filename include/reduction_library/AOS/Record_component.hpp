#pragma once

#include "reduction_library/objects/record_component/Record_component_names.hpp"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/objects/record_component/Traits.hpp"
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

   // Particle_spicies, attribute::Scalar_records_names::weighting
    template<>
    DNLINE std::vector<traits::Type<Record_component, Record_component_names::x>> storeChunk()
	{

	}


} //attribute
} //reduction_library
