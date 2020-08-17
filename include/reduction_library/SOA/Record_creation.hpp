#pragma once

#include "reduction_library/SOA/Record_scalar.hpp"

#include "reduction_library/component/Name.hpp"
#include "reduction_library/record/Name.hpp"

namespace reduction_library{
namespace SOA{

template<typename T_component>
class Record_creation
{
 public:
    using Dataset_type = typename component::traits::Type<T_component>::type;

    static Scalar_record<Dataset_type> create(T_component component){

     Scalar_record<Dataset_type> result_record;
     result_record.set_component(component);
     return result_record;
 }
};




} // namespace SOA
} // namespace reduction_library
