#pragma once
#include <string>
#include <iostream>
#include <map>

namespace reduction_library{

    enum class Attribute{
        momentum_x,
        weighting

    };

    typedef std::map<Attribute, std::pair<std::string, std::string>> statemap_t;

    const statemap_t state = {
        { Attribute::momentum_x, std::pair<std::string, std::string>{"momentum", "x"} },
        { Attribute::weighting,  std::pair<std::string, std::string>{"weighting", "SCALAR"}}
    };
    template<typename T_particle, Attribute attribute>
    double& get_attribute(T_particle & particle);

    template<typename T_particle>
    double& get_momentum(T_particle& particle)
    {
    return get_attribute<T_particle, Attribute::momentum_x>(particle);
    }

    template<typename T_particle>
    double& get_weighting(T_particle& particle)
    {
    return get_attribute<T_particle, Attribute::weighting>(particle);
    }

}


