#pragma once

#include <tuple>

namespace helpers{
/** Represent tuple type with given objects
*/
template<class ... T>
using Type_list = std::tuple<T...>;

/** Represent type of result type for applying metafunction to types in list T_List
* \tparam T_Functions - type of metafunction
* \tparam T_List - type arguments list
*/
template<template <typename> typename T_Function, typename T_List>
struct apply_meta;

/** Represent type of fuction result type for applying metafunction to types in parameters pack
* \tparam T_Functions - type of metafunction
* \tparam T - metafunction's arguments
*/
template<template <typename> typename T_Function, class ... T>
struct apply_meta<T_Function, Type_list<T ...>>{
    using type = Type_list<T_Function<T>...>;
};

/** Represent typename of result type for applying metafunction to types in list T_List
* \tparam T_Functions - type of metafunction
* \tparam T_List - type arguments list
*/
template <template <typename> typename T_Function, typename T_List>
using apply_meta_t =  typename apply_meta<T_Function, T_List>::type;


} //namespace helpers
