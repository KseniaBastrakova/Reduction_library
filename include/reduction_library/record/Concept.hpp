/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/record/Utility.hpp"

namespace reduction_library{
namespace record{

/** @file
 *
 * Define record concept
 *
 * A record concept represents particle properties that contains set of components
 * amount of components can be from 1(scalar) to 3(3 - dimension)
 * scalar components represents physical constants, such as mass charge, etc.
 * vector components (1, 2, 3 -d) represent vector values in Cartesian and cylindrical  coordinates
 * Coordinates, momentum, etc.
 *
 * components can be stored for the underlying particle
 * (macroWeighted = 0) or for the full macroparticle (macroWeighted = 1)
 *
 * also, stored the characterizing record's unit in SI for all components
 *
 * Records are represented with components indentufied with name tags, see reduction_library/record/Name.hpp
 * based on openPMD record:
 * https://github.com/openPMD/openPMD-standard/blob/latest/STANDARD.md
 *
 * These define requirements on component concept (in informal, not C++20 standard sense).
 */


    /** Unit dimention type: basetd on openPMD init dinesion idea
     * of powers of the 7 base measures characterizing the record's unit in SI
     * (length L, mass M, time T, electric current I,
     * thermodynamic temperature theta, amount of substance N, luminous intensity J)
    */
    using unit_dimension_type = std::array<int, 7>;

    /** Functor for getting unit dimension
     *
     * Expected interface:
     *     HDINLINE unit_dimension_type operator()() const;
     *
     * \tparam T_Record record type
     */
    template<typename T_Record>
    struct Geting_unit_dimension;

    template<typename T_Record>
    double getting_unit_dimension(T_Record& record)
    {
        Geting_unit_dimension<T_Record> ud_get_functor;
        return ud_get_functor.operator ()(record);
    }

    /** Functor for getting weighting power attribute
     *
     * weighting power attribute
     * indicates with which power of weighting the quantity
     * should be multiplied, in order to go from the
     * individual-particle representation to the full-macroparticle representation
     *
     * Expected interface:
     *     HDINLINE double operator()() const;
     *
     * \tparam T_Record record type
     */
    template<typename T_Record>
    struct Geting_weighting_power;

    template<typename T_Record>
    double get_weighting_power(T_Record& record)
    {
        Geting_weighting_power<T_Record> wp_get_functor;
        return wp_get_functor.operator ()(record);
    }

    /** Functor for getting macro weighted attribute
     *
     * indicates whether this record is for the underlying particle
     * (macroWeighted = 0) or for the full macroparticle (macroWeighted = 1)
     *
     * Expected interface:
     *     HDINLINE double operator()() const;
     *
     * \tparam T_Record record type
     */
    template<typename T_Record>
    struct Geting_macro_weighted;

    template<typename T_Record>
    double get_macro_weighted(T_Record&& record)
    {
        Geting_macro_weighted<T_Record> mw_get_functor;
        return mw_get_functor.operator ()(std::move(record));
    }

    /** Functor for getting component for given record
     *
     * return component by name (defined in reduction_library/component/Name.hpp)
     * with type that defined in reduction_library/record/Utility.hpp
     *
     * Expected interface:
     *     HDINLINE traits::Type<T_Component_Name, T_Record>::type operator()() const;
     *
     * \tparam T_Record record type
     */
    template<typename T_Component_Name, typename T_Record>
    struct Getting_value;

    template<typename T_Component_Name, typename T_Record>
    HDNLINE typename traits::Type<T_Component_Name, T_Record>::type & get(T_Record& record)
    {
        Getting_value<T_Component_Name, T_Record> v_get_functor;
        return v_get_functor.operator() (record);
    }

} // namespace record
} //namespace reduction_library
