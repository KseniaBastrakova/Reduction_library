/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

/** @file
 *
 * Define component concept
 *
 * A component represents a data set of arbitrary, supposedly scalar, type.
 * The values can be in arbitrary unit system, a component defines conversion factor to SI.
 * we assume it is 1D
 *
 * Data records with logically vector data (such as momentums) are represented with several components
 * identified with name tags, see reduction_library/component/Name.hpp.
 *
 * This file defines type traits to be specialized by component types.
 * These define requirements on component concept (in informal, not C++20 standard sense).
 * /// TODO maybe there are some more requirements not stated explicitly, like copyable? Can add later to here
 * Thus we refer to a type satisfying these requirements as a "component type".
 */

namespace reduction_library{
namespace component{
namespace traits{

  /** Trait for type of values stored in component's data set
   *
   * Resulting type defined as ::type.
   *
   * \tparam T_Component component type
   */
  template<typename T_Component>
  struct Value_type;
  
} // namespace traits

/** Functor for getting conversion unit to SI
 *
 * Expected interface:
 *     HDINLINE double operator()() const;
 *
 * \tparam T_Component component type
 */
  template<typename T_Component>
  struct Getting_unit_SI;

  /** Functor for setting conversion unit to SI
   *
   * Expected interface:
   *     HDINLINE void operator()( double newValue );
   *
   * \tparam T_Component component type
   */
  /// TODO: the name is weird, maybe Get_unit_SI ?
  template<typename T_Component>
  struct Setting_unit_SI;

} // namespace component
} // namespace reduction_library
