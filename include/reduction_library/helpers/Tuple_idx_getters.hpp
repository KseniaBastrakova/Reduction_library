/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <tuple>

namespace helpers{
/** Helper functor for getting index for type in given tuple
 * in compile time
 * \tparam T - type of value
 * \tparam Tuple - type of Tuple
*/
template <class T, class Tuple>
struct Index;

/** Specialization for case, when value type isn't in tuple
 * \tparam T - type of value
 * \tparam Types - type of tuple's parameter pack
*/
template <class T, class... Types>
struct Index<T, std::tuple<T, Types...>>
{
    static const std::size_t value = 0;
};
/** Functor specialization for tuple type std::tuple
 * with given parameter pack of Types
 *  return value - index number of value type in std::tuple<U, Types...>
 * \tparam T - type of input value
 * \tparam Tuple - type of Tuple
*/
template <class T, class U, class... Types>
struct Index<T, std::tuple<U, Types...>>
{
    static const std::size_t value = 1 + Index<T, std::tuple<Types...>>::value;
};

} // namespace helpers
