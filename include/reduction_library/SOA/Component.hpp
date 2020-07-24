#pragma once

#include "reduction_library/component/Name.hpp"
#include "reduction_library/component/Interfaces.hpp"
#include <vector>

namespace reduction_library{
namespace SOA{

    template<component::Name T_scalar_record, class T_Value>
    struct Component {
    private:
        std::vector<T_Value> values;
        double unit_SI;
        double dt;
    public:
        Component(const std::vector<T_Value>& values):
            unit_SI(42.), dt(50.){}

        std::vector<T_Value>& get()
        {
            return values;
        }
        double get_unit_SI()
        {
            return unit_SI;
        }
        double get_dt()
        {
            return dt;
        }

    };

    template<>
    class attribute::Geting_weighting_power<Particle_spicies, attribute::Scalar_records_names::momentum_x>
    {
    public:
        Geting_weighting_power (){}
        double operator() (AOS::Particle_spicies particles)
        {
            AOS::Momentums& momentums = static_cast<AOS::Momentums&>(particles);
            double weighting_power = momentums.get_weighting_power();
            return weighting_power;
        }
    private:

    };
}//SOA
}// reduction_library

