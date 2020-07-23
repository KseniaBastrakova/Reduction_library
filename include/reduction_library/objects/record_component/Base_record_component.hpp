#pragma once

#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/objects/record_component/Record_component_names.hpp"
#include "reduction_library/objects/record_component/Traits.hpp"
#include <vector>


namespace reduction_library{
namespace objects{
namespace record_component{


	template<typename T_particles, Record_component_names T_scalar_record>
	HDNLINE void loadChunk(T_particles & particles, std::vector<traits::Type<T_particles, T_scalar_record>> value);

	template<typename T_particles, Record_component_names T_scalar_record>
	HDNLINE std::vector<traits::Type<T_particles, T_scalar_record>> storeChunk();

}//record_component
}//objects
}//reduction_library


