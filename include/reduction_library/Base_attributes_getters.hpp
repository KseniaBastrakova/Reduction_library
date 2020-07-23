#pragma once

#include "reduction_library/Scalar_records_names.hpp"
#include "reduction_library/Type.hpp"
#include "reduction_library/HDNLINE.hpp"

namespace reduction_library{
namespace attribute{



    template<typename T_particles, Scalar_records_names T_scalar_record>
    class Geting_weighting_power
    {
    public:
        Geting_weighting_power (){}
        double operator() (T_particles particles);
   private:

    };

    template<typename T_particles, Scalar_records_names T_scalar_record>
    double get_weighting_power(T_particles particles){

        Geting_weighting_power<T_particles, T_scalar_record> wp_functor;
        return wp_functor.operator ()(particles);


    }


} //attribute
} //reduction_library
