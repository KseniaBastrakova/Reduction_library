#pragma once

#include "reduction_library/objects/Scalar_records_names.hpp"
#include "reduction_library/objects/Type.hpp"
#include "reduction_library/HDNLINE.hpp"

namespace reduction_library{
namespace attribute{

    template<typename T_particle, Scalar_records_names T_scalar_record>
    HDNLINE void set_attribute(T_particle & particle, attribute::traits::Type<T_particle, T_scalar_record> value);

    template<typename T_particle, Scalar_records_names T_scalar_record>
    HDNLINE
    attribute::traits::Type<T_particle, T_scalar_record> get_attribute(T_particle & particle);

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
