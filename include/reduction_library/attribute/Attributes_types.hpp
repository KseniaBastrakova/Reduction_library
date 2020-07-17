#pragma once

#include <string>
#include <iostream>
#include <map>

namespace reduction_library{
namespace attribute{

    enum class Attribute{
        momentum_x,
        weighting

    };

    typedef std::map<Attribute, std::pair<std::string, std::string>> statemap_t;

    const statemap_t state = {
        { Attribute::momentum_x, std::pair<std::string, std::string>{"momentum", "x"} },
        { Attribute::weighting,  std::pair<std::string, std::string>{"weighting", "SCALAR"}}
    };

} //attribute
} //reduction_library


