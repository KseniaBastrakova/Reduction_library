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
/** @file
 *
 * Specializations for giving access to
 * component elements in records
 * using interfaces, define in component/Utility.hpp
 * and record/Utility.hpp
 * We use pre-define names from component and record interfaces
 *
 */


/** Base functor for getting access to special component
 * in record, by component and record names
 *
 *  return element from particle
 *
 * \tparam Component_Name -- name of the component
 * \tparam Record_Name -- name of the record
 * \tparam T_Particle -- type of the input particle
 */
    template<typename Component_Name, typename Record_Name, typename T_Particle>
    struct Getting_value;

    template<typename Component_name, typename Record_Name, typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get(T_Particle& particle)
    {
        Getting_value<Component_name, Record_Name, T_Particle> v_get_functor;
        return v_get_functor.operator() (particle);
    }

    /** Base functor for changing element with given Record, Component name
     * for given particle
     *
     * \tparam Component_Name -- name of the component
     * \tparam Record_Name -- name of the record
     * \tparam T_Particle -- type of the input particle
     * \tparam T_Dataset -- type of the value in coponent
     *
     */
    template<typename Component_name, typename Record_Name, typename T_Particle, typename T_Dataset>
    struct Setting_value;

    template<typename Component_name, typename Record_Name, typename T_Particle, typename T_Dataset>
    ALPAKA_FN_HOST_ACC void set(T_Dataset value, T_Particle& particle)
    {
        Setting_value<Component_name, Record_Name, T_Particle, T_Dataset> v_set_functor;
        v_set_functor.operator ()(value, particle);
    }

    //-----------------------------------------------------------------------------
    //! Returns the number of underlying individual particles that the macroparticle represent
    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_weighting(T_Particle& particle)
    {
        return get<component::name::SCALAR, record::name::Weighting>(particle);
    }

    //-----------------------------------------------------------------------------
    //! Set the number of underlying individual particles that the macroparticle represent
    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC void set_weighting(double weighting, T_Particle& particle)
    {
        set<component::name::SCALAR, record::name::Weighting>(weighting, particle);
    }

    //-----------------------------------------------------------------------------
    //! Reruns component-wise momentum of the macroparticle, for component "X"
    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_momentum_x(T_Particle& particle)
    {
        return get<component::name::X, record::name::Momentum>(particle);
    }

    //-----------------------------------------------------------------------------
    //! Reruns component-wise momentum of the macroparticle, for component "Y"
    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_momentum_y(T_Particle& particle)
    {
        return get<component::name::Y, record::name::Momentum>(particle);
    }

    //-----------------------------------------------------------------------------
    //! Reruns component-wise momentum of the macroparticle, for component "Z"
    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_momentum_z(T_Particle& particle)
    {
        return get<component::name::Z, record::name::Momentum>(particle);
    }

    //-----------------------------------------------------------------------------
    //! Reruns component-wise position of a particle, for component "X"
    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_position_x(T_Particle& particle)
    {
        return get<component::name::X, record::name::Position>(particle);
    }

    //-----------------------------------------------------------------------------
    //! Reruns component-wise position of a particle, for component "Y"
    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_position_y(T_Particle& particle)
    {
        return get<component::name::Y, record::name::Position>(particle);
    }

    //-----------------------------------------------------------------------------
    //! Reruns component-wise position of a particle, for component "Z"
    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_position_z(T_Particle& particle)
    {
        return get<component::name::Z, record::name::Position>(particle);
    }

    //-----------------------------------------------------------------------------
    //! Reruns electric charge of the macroparticle
    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_charge(T_Particle& particle)
    {
        return get<component::name::SCALAR, record::name::Charge>(particle);
    }

    //-----------------------------------------------------------------------------
    //! Reruns mass of the macroparticle
    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_mass(T_Particle& particle)
    {
        return get<component::name::SCALAR, record::name::Mass>(particle);
    }

    //-----------------------------------------------------------------------------
    //! Reruns unique idx for each particle
    template <typename T_Particle>
    ALPAKA_FN_HOST_ACC auto get_idx(T_Particle& particle)
    {
        return get<component::name::SCALAR, record::name::Idx>(particle);
    }

    //-----------------------------------------------------------------------------
    //! Set component-wise momentum of the macroparticle, for component "X"
    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_momentum_x(T_Value value, T_Particle& particle)
    {
        set<component::name::X, record::name::Momentum>(value, particle);
    }

    //-----------------------------------------------------------------------------
    //! Set component-wise momentum of the macroparticle, for component "Y"
    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_momentum_y(T_Value value, T_Particle& particle)
    {
        set<component::name::Y, record::name::Momentum>(value, particle);
    }

    //-----------------------------------------------------------------------------
    //! Set component-wise momentum of the macroparticle, for component "Z"
    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_momentum_z(T_Value value, T_Particle& particle)
    {
        set<component::name::Z, record::name::Momentum>(value, particle);
    }

    //-----------------------------------------------------------------------------
    //! Reruns component-wise position of a particle, for component "X"
    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_position_x(T_Value value, T_Particle& particle)
    {
        set<component::name::X, record::name::Position>(value, particle);
    }

    //-----------------------------------------------------------------------------
    //! Reruns component-wise position of a particle, for component "Y"
    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_position_y(T_Value value, T_Particle& particle)
    {
        set<component::name::Y, record::name::Position>(value, particle);
    }

    //-----------------------------------------------------------------------------
    //! Reruns component-wise position of a particle, for component "Z"
    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_position_z(T_Value value, T_Particle& particle)
    {
        set<component::name::Z, record::name::Position>(value, particle);
    }

    //! Set electric charge of the macroparticle
    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_charge(T_Value value, T_Particle& particle)
    {
        set<component::name::SCALAR, record::name::Charge>(value, particle);
    }

    //-----------------------------------------------------------------------------
    //! Set mass of the macroparticle
    template <typename T_Particle, typename T_Value>
    ALPAKA_FN_HOST_ACC void set_mass(T_Value value, T_Particle& particle)
    {
        set<component::name::SCALAR, record::name::Mass>(value, particle);
    }

} // namespace particle
} //namespace reduction_library
