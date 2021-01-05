/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once
#include "reduction_library/record/Name.hpp"
#include <string>
#include <tuple>

namespace traits{
    template<typename T_Record_name>
    std::string get_record_name(){
        using namespace reduction_library;
        auto string_names = ("Charge", "Momentum", "Position", "Weighting");
        using struct_names = std::tuple<record::name::Charge, record::name::Momentum, record::name::Position, record::name::Weighting>;


    }
}
