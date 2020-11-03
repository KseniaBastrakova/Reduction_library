#pragma once

#include <tuple>

namespace helpers{

    template<class ... T>
    using Type_list = std::tuple<T...>;

    template<template <typename> typename T_function, typename T_list>
    struct apply_meta;

    template<template <typename> typename T_function, class ... T>
    struct apply_meta<T_function, Type_list<T ...>>{
        using type = Type_list<T_function<T>...>;
    };

    template <template <typename> typename T_function, typename T_list>
    using apply_meta_t =  typename apply_meta<T_function, T_list>::type;


} //namespace helpers
