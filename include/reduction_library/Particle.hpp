/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <alpaka/alpaka.hpp>
#include "reduction_library/component/Name.hpp"
#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/record/Name.hpp"

namespace reduction_library{
namespace particle_access{

    template<typename Component_name, typename T_Record, typename T_Particle>
    struct Getting_value;

    template<typename Component_name, typename T_Record, typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get(T_Particle& particle)
    {
        Getting_value<Component_name, T_Record, T_Particle> v_get_functor;
        return v_get_functor.operator() (particle);
    }

    template<typename Component_name, typename Record_name, typename T_Particle, typename T_dataset>
    struct Setting_value;

    template<typename Component_name, typename Record_name, typename T_Particle, typename T_dataset>
    ALPAKA_FN_HOST_ACC void set(T_dataset value, T_Particle& particle)
    {
        Setting_value<Component_name, Record_name, T_Particle, T_dataset> v_set_functor;
        v_set_functor.operator ()(value, particle);
    }


    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_weighting(T_Particle& particle)
    {
        return get<component::name::SCALAR, record::name::Weighting>(particle);
    }

    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC void set_weighting(double weighting, T_Particle& particle)
    {
        set<component::name::SCALAR, record::name::Weighting>(weighting, particle);
    }

    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_momentum_x(T_Particle& particle)
    {
        return get<component::name::X, record::name::Momentum>(particle);
    }

    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_momentum_y(T_Particle& particle)
    {
        return get<component::name::Y, record::name::Momentum>(particle);
    }

    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_momentum_z(T_Particle& particle)
    {
        return get<component::name::Z, record::name::Momentum>(particle);
    }

    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_position_x(T_Particle& particle)
    {
        return get<component::name::X, record::name::Position>(particle);
    }

    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_position_y(T_Particle& particle)
    {
        return get<component::name::Y, record::name::Position>(particle);
    }

    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_position_z(T_Particle& particle)
    {
        return get<component::name::Z, record::name::Position>(particle);
    }

    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_charge(T_Particle& particle)
    {
        return get<component::name::SCALAR, record::name::Charge>(particle);
    }
    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_mass(T_Particle& particle)
    {
        return get<component::name::SCALAR, record::name::Mass>(particle);
    }
    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_idx(T_Particle& particle)
    {
        return get<component::name::SCALAR, record::name::Idx>(particle);
    }

    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_momentum_x(T_Value value, T_Particle& particle)
    {
        set<component::name::X, record::name::Momentum>(value, particle);
    }

    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_momentum_y(T_Value value, T_Particle& particle)
    {
        set<component::name::Y, record::name::Momentum>(value, particle);
    }

    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_momentum_z(T_Value value, T_Particle& particle)
    {
        set<component::name::Z, record::name::Momentum>(value, particle);
    }

    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_position_x(T_Value value, T_Particle& particle)
    {
        set<component::name::X, record::name::Position>(value, particle);
    }

    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_position_y(T_Value value, T_Particle& particle)
    {
        set<component::name::Y, record::name::Position>(value, particle);
    }

    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_position_z(T_Value value, T_Particle& particle)
    {
        set<component::name::Z, record::name::Position>(value, particle);
    }

    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_charge(T_Value value, T_Particle& particle)
    {
        set<component::name::SCALAR, record::name::Charge>(value, particle);
    }
    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_mass(T_Value value, T_Particle& particle)
    {
        set<component::name::SCALAR, record::name::Mass>(value, particle);
    }

} // namespace particle
} //namespace reduction_library
