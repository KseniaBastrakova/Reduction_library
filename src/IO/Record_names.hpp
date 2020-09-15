#pragma once
#include "reduction_library/record/Name.hpp"
#include <string>
#include <tuple>

namespace traits{
    template<typename T_Record_name>
    std::string get_record_name(){
        using namespace reduction_library;
        auto string_names = ("Charge", "Momentum", "Position", "Weighting");
        using struct_names = std::tuple<record::Name::Charge, record::Name::Momentum, record::Name::Position, record::Name::Weighting>;


    }
}
