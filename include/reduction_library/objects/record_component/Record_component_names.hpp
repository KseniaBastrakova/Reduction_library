#pragma once

#include <string>
#include <iostream>
#include <map>

namespace reduction_library{
namespace objects{
namespace record_component{

    enum class Record_component_names{
        x,
        y,
		z,
		SCALAR
    };

    typedef std::map<Record_component_names, std::string> records_names;

    const records_names state = {
        { Record_component_names::x, "x" },
		{ Record_component_names::y, "y" },
		{ Record_component_names::z, "z" },
		{ Record_component_names::SCALAR, "SCALAR" }

    };

} //record_component
} //objects
} //reduction_library

