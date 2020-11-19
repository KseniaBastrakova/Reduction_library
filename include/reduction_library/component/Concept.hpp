///TODO: copyright

#pragma once


/** @file
 *
 * Define component concept
 *
 * A component represents a data set of arbitrary, supposedly scalar, type.
 * The values can be in arbitrary unit system, a component defines conversion factor to SI.
 * /// TODO: do we assume it is 1D or not?
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

  ///TODO: maybe Value_type or however it is spelled?
  /** Trait for type of values stored in component's data set
   *
   * Resulting type defined as ::type.
   *
   * \tparam T_Component component type
   */
  template< typename T_Component >
  struct Type;
  
  /** Functor for getting conversion unit to SI
   *
   * Expected interface:
   *     double operator()() const;
   *
   * \tparam T_Component component type
   */
  /// TODO: the name is weird, maybe Get_unit_SI ? or at least Getting
  template< typename T_Component >
  struct Geting_unit_SI;

  /** Functor for setting conversion unit to SI
   *
   * Expected interface:
   *     void operator()( double newValue );
   *
   * \tparam T_Component component type
   */
  /// TODO: the name is weird, maybe Get_unit_SI ?
  template< typename T_Component >
  struct Setting_unit_SI;
  
} // namespace traits

/// TODO: this adds nothing, what's the purpose?
///! Returns typename of component's storage type
///template<typename T_Component>
///using Type = typename traits::Type<T_Component>::type;

} // namespace component
} // namespace reduction_library
