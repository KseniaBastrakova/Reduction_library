#pragma once

#include <alpaka/alpaka.hpp>
#include "reduction_library/component/Name.hpp"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/record/Name.hpp"

namespace reduction_library{
namespace particle_access{

    template<typename Component_name, typename T_Record, typename T_particle>
    struct Getting_value;

    template<typename Component_name, typename T_Record, typename T_particle>
    ALPAKA_FN_HOST_ACC auto get(T_particle& particle){
        Getting_value<Component_name, T_Record, T_particle> v_get_functor;
        return v_get_functor.operator() (particle);
    }

    template<typename Component_name, typename Record_name, typename T_particle, typename T_dataset>
    struct Setting_value;

    template<typename Component_name, typename Record_name, typename T_particle, typename T_dataset>
    ALPAKA_FN_HOST_ACC void set(T_dataset value, T_particle& particle){
        Setting_value<Component_name, Record_name, T_particle, T_dataset> v_set_functor;
        v_set_functor.operator ()(value, particle);
    }


    template <typename T_particle>
    ALPAKA_FN_HOST_ACC auto get_weighting(T_particle& particle){
        return get<component::Name::SCALAR, record::Name::Weighting>(particle);
    }

    template <typename T_particle>
    ALPAKA_FN_HOST_ACC void set_weighting(double weighting, T_particle& particle){
        set<component::Name::SCALAR, record::Name::Weighting>(weighting, particle);
    }

    template <typename T_particle>
    ALPAKA_FN_HOST_ACC auto get_momentum_x(T_particle& particle){
        return get<component::Name::X, record::Name::Momentum>(particle);
    }

    template <typename T_particle>
    ALPAKA_FN_HOST_ACC auto get_momentum_y(T_particle& particle){
        return get<component::Name::Y, record::Name::Momentum>(particle);
    }

    template <typename T_particle>
    ALPAKA_FN_HOST_ACC auto get_momentum_z(T_particle& particle){
        return get<component::Name::Z, record::Name::Momentum>(particle);
    }

    template <typename T_particle>
    ALPAKA_FN_HOST_ACC auto get_position_x(T_particle& particle){
        return get<component::Name::X, record::Name::Position>(particle);
    }

    template <typename T_particle>
    ALPAKA_FN_HOST_ACC auto get_position_y(T_particle& particle){
        return get<component::Name::Y, record::Name::Position>(particle);
    }

    template <typename T_particle>
    ALPAKA_FN_HOST_ACC auto get_position_z(T_particle& particle){
        return get<component::Name::Z, record::Name::Position>(particle);
    }

    template <typename T_particle>
    ALPAKA_FN_HOST_ACC auto get_charge(T_particle& particle){
        return get<component::Name::SCALAR, record::Name::Charge>(particle);
    }

    template <typename T_particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_momentum_x(T_Value value, T_particle& particle){
        set<component::Name::X, record::Name::Momentum>(value, particle);
    }

    template <typename T_particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_momentum_y(T_Value value, T_particle& particle){
        set<component::Name::Y, record::Name::Momentum>(value, particle);
    }

    template <typename T_particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_momentum_z(T_Value value, T_particle& particle){
        set<component::Name::Z, record::Name::Momentum>(value, particle);
    }

    template <typename T_particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_position_x(T_Value value, T_particle& particle){
        set<component::Name::X, record::Name::Position>(value, particle);
    }

    template <typename T_particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_position_y(T_Value value, T_particle& particle){
        set<component::Name::Y, record::Name::Position>(value, particle);
    }

    template <typename T_particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_position_z(T_Value value, T_particle& particle){
        set<component::Name::Z, record::Name::Position>(value, particle);
    }

    template <typename T_particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_charge(T_Value value, T_particle& particle){
        set<component::Name::SCALAR, record::Name::Charge>(value, particle);
    }

} // namespace particle
} //namespace reduction_library
