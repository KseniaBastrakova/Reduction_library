#pragma once

#include "reduction_library/HDNLINE.hpp"
#include "reduction_library/attribute/Type.hpp"
#include "reduction_library/attribute/Scalar_records_names.hpp"

namespace reduction_library{
namespace attribute{

    template<typename T_particle, Scalar_records_names T_scalar_record>
    HDNLINE void set_attribute(T_particle & particle, attribute::traits::Type<T_particle, T_scalar_record> value);

    template<typename T_particle, Scalar_records_names T_scalar_record>
    HDNLINE
    attribute::traits::Type<T_particle, T_scalar_record> get_attribute(T_particle & particle);


} //attribute
} //reduction_library
