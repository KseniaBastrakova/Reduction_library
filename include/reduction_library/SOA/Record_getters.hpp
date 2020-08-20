#pragma once

#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Particle.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/component/Interfaces.hpp"

namespace reduction_library{
namespace SOA{

template <typename T_Particle_species>
auto get_weighting(Particle<T_Particle_species>& particle){
    using Particle_type = Particle<T_Particle_species>;
    auto value_weighting = component::get<component::Name::SCALAR, record::Name::weighting, Particle_type>(particle);
    return value_weighting;
}

template <typename T_Particle_species>
void set_weighting(double weighting, Particle<T_Particle_species>& particle){
    using Particle_type = Particle<T_Particle_species>;
    component::set<component::Name::SCALAR, record::Name::weighting, Particle_type, double>(weighting, particle);
}

template <typename T_Particle_species>
auto get_momentum_x(Particle<T_Particle_species>& particle){
    using Particle_type = Particle<T_Particle_species>;
    auto value = component::get<component::Name::x, record::Name::momentum, Particle_type>(particle);
    return value;
}

template <typename T_Particle_species>
auto get_momentum_y(Particle<T_Particle_species>& particle){
    using Particle_type = Particle<T_Particle_species>;
    auto value = component::get<component::Name::y, record::Name::momentum, Particle_type>(particle);
    return value;
}

template <typename T_Particle_species>
auto get_momentum_z(Particle<T_Particle_species>& particle){
    using Particle_type = Particle<T_Particle_species>;
    auto value = component::get<component::Name::z, record::Name::momentum, Particle_type>(particle);
    return value;
}

template <typename T_Particle_species, typename T_Value>
void set_momentum_x(T_Value value, Particle<T_Particle_species>& particle){
    using Particle_type = Particle<T_Particle_species>;
    component::set<component::Name::x, record::Name::momentum, Particle_type>(value, particle);
}

template <typename T_Particle_species, typename T_Value>
void set_momentum_y(T_Value value, Particle<T_Particle_species>& particle){
    using Particle_type = Particle<T_Particle_species>;
    component::set<component::Name::y, record::Name::momentum, Particle_type>(value, particle);
}

template <typename T_Particle_species, typename T_Value>
auto set_momentum_z(T_Value value, Particle<T_Particle_species>& particle){
    using Particle_type = Particle<T_Particle_species>;
    component::set<component::Name::z, record::Name::momentum, Particle_type>(value, particle);
}

} // namespace SOA
} // namespace reduction_library
