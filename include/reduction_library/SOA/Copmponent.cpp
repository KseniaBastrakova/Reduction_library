#include "reduction_library/SOA/Component.hpp"
#include "reduction_library/component/Type.hpp"
#include "reduction_library/component/Interfaces.hpp"
#include "reduction_library/component/Name.hpp"
#include <vector>
#include <iostream>
#include "Particle_species.hpp"


namespace reduction_library{

    template <>
    component::traits::Type<SOA::Component<component::Name::x, double>>::type
        component::get<SOA::Component<component::Name::x, double>, Particle<SOA::Particle_spicies>
    (Particle<SOA::Particle_spicies>& particle)
    {
        double component_idx = particle.idx;
        auto value = component.get()[component_idx];
        return component_idx;
    };


    template <>
    void component::set<SOA::Component<component::Name::x, double>, Particle<SOA::Particle_spicies>>
    (component::traits::Type<SOA::Component<component::Name::x,
            double>>::type value, Particle<SOA::Particle_spicies>& particle)
    {
        int component_idx = particle.idx;
        component.get()[component_idx] = value;

    };

}
