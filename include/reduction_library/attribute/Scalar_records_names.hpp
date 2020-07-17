#pragma once

#include <string>
#include <iostream>
#include <map>

namespace reduction_library{
namespace attribute{

    enum class Scalar_records_names{
        momentum_x,
        weighting

    };

    typedef std::map<Scalar_records_names, std::pair<std::string, std::string>> records_names;

    const records_names state = {
        { Scalar_records_names::momentum_x, std::pair<std::string, std::string>{"momentum", "x"} },
        { Scalar_records_names::weighting,  std::pair<std::string, std::string>{"weighting", "SCALAR"}}
    };

} //attribute
} //reduction_library


