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
    using Dataset_type = component::traits::Type<T_component>;

 static Scalar_record<Dataset_type> create(T_component component){

     Scalar_record<Dataset_type>  result_dataset;
     return result_dataset;
 }
};


}
}
