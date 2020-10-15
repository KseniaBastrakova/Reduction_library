#pragma once

#include "../Particle.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Particle.hpp"
#include "reduction_library/record/Name.hpp"

#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"


namespace reduction_library{
namespace particle_access{

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
        dataset.set_value(value, idx);
    }

};

} // namespace particle

} // namespace reduction_library
