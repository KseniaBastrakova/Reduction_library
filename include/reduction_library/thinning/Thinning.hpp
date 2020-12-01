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

namespace reduction_library{
namespace thinning{

class Thinning{

public:
    ALPAKA_FN_ACC Thinning(){}

    ALPAKA_FN_ACC void init(){}
    template<typename Acc, typename T_Particle, typename T_Random_Generator>
    ALPAKA_FN_ACC void collect(Acc const& acc, T_Particle particle, T_Random_Generator& generator)
    {}

    template<typename Acc>
    ALPAKA_FN_ACC void process(Acc const& acc) const
    {}

    template<typename Acc, typename T_Particle>
    ALPAKA_FN_ACC void reduce(Acc const& acc, T_Particle& particle) const
    {}

};

} //thinning
} //reduction_library
