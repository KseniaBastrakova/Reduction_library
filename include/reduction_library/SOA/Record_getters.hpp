#pragma once

#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Particle.hpp"
#include "reduction_library/record/Name.hpp"

#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"
#include "reduction_library/Base_particle.hpp"


namespace reduction_library{
namespace particle{

template<typename Component_name, typename Record_name, class T_Particle_species>
struct Getting_value<Component_name, Record_name, Particle<T_Particle_species>>
{
public:
    auto operator() (Particle<T_Particle_species>& particle)
    {
        auto& base_particles = particle.baseParticles; // record
        auto& record_value = particle_species::get<Record_name, T_Particle_species>(base_particles);
        auto& component = record::get<Component_name>(record_value);
        auto& dataset = component.get_dataset();
        int idx = particle.idx;
        double& value = dataset[idx];
        return value;
    }

};

template<typename Component_name, typename Record_name, class T_Particle_species, typename T_Dataset>
struct Setting_value<Component_name, Record_name, Particle<T_Particle_species>, T_Dataset>
{
public:
    void operator() (T_Dataset value, Particle<T_Particle_species>& particle)
    {
        auto& base_particles = particle.baseParticles; // record
        auto& record_value = particle_species::get<Record_name, T_Particle_species>(base_particles);
        auto& component = record::get<Component_name>(record_value);
        auto& dataset = component.get_dataset();
        int idx = particle.idx;
        component.get_dataset()[idx] = value;
    }

};

} // namespace particle

namespace SOA{

template <typename T_Particle_species>
auto get_weighting(Particle<T_Particle_species>& particle){
    return particle::get<component::Name::SCALAR, record::Name::Weighting>(particle);
}

template <typename T_Particle_species>
void set_weighting(double weighting, Particle<T_Particle_species>& particle){
    particle::set<component::Name::SCALAR, record::Name::Weighting>(weighting, particle);
}

template <typename T_Particle_species>
auto get_momentum_x(Particle<T_Particle_species>& particle){
    return particle::get<component::Name::X, record::Name::Momentum>(particle);
}

template <typename T_Particle_species>
auto get_momentum_y(Particle<T_Particle_species>& particle){
    return particle::get<component::Name::Y, record::Name::Momentum>(particle);
}

template <typename T_Particle_species>
auto get_momentum_z(Particle<T_Particle_species>& particle){
    return particle::get<component::Name::Z, record::Name::Momentum>(particle);
}

template <typename T_Particle_species>
auto get_position_x(Particle<T_Particle_species>& particle){
    return particle::get<component::Name::X, record::Name::Position>(particle);
}

template <typename T_Particle_species>
auto get_position_y(Particle<T_Particle_species>& particle){
    return particle::get<component::Name::Y, record::Name::Position>(particle);
}

template <typename T_Particle_species>
auto get_position_z(Particle<T_Particle_species>& particle){
    return particle::get<component::Name::Z, record::Name::Position>(particle);
}

template <typename T_Particle_species>
auto get_charge(Particle<T_Particle_species>& particle){
    return particle::get<component::Name::SCALAR, record::Name::Charge>(particle);
}

template <typename T_Particle_species, typename T_Value>
void set_momentum_x(T_Value value, Particle<T_Particle_species>& particle){
    particle::set<component::Name::X, record::Name::Momentum>(value, particle);
}

template <typename T_Particle_species, typename T_Value>
void set_momentum_y(T_Value value, Particle<T_Particle_species>& particle){
    particle::set<component::Name::Y, record::Name::Momentum>(value, particle);
}

template <typename T_Particle_species, typename T_Value>
void set_momentum_z(T_Value value, Particle<T_Particle_species>& particle){
    particle::set<component::Name::Z, record::Name::Momentum>(value, particle);
}

template <typename T_Particle_species, typename T_Value>
void set_position_x(T_Value value, Particle<T_Particle_species>& particle){
    particle::set<component::Name::X, record::Name::Position>(value, particle);
}

template <typename T_Particle_species, typename T_Value>
void set_position_y(T_Value value, Particle<T_Particle_species>& particle){
    particle::set<component::Name::Y, record::Name::Position>(value, particle);
}

template <typename T_Particle_species, typename T_Value>
void set_position_z(T_Value value, Particle<T_Particle_species>& particle){
    particle::set<component::Name::Z, record::Name::Position>(value, particle);
}

template <typename T_Particle_species, typename T_Value>
void set_charge(T_Value value, Particle<T_Particle_species>& particle){
    particle::set<component::Name::SCALAR, record::Name::Charge>(value, particle);
}

} // namespace SOA
} // namespace reduction_library
