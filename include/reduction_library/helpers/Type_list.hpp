#pragma once

#include <tuple>

namespace helpers{

    template<class ... T>
    using Type_list = std::tuple<T...>;

} //namespace helpers
