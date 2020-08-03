#pragma once

#include "reduction_library/record/Type.hpp"
#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/record/Name.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Component.hpp"
#include "reduction_library/HDNLINE.hpp"

#include <vector>

namespace reduction_library{
namespace SOA{

    using SCALAR = Component<component::Name::SCALAR, double>;

    template<record::Name T_record>
    struct Record_3d : public SCALAR{
    private:
        int macroWeighted;
        double weightingPower;
        component::Name component_name;
        component::Name record_name;

    public:
        Record_3d(const std::vector<double>& scalar_values
               ):
                   SCALAR(x_values),
               record_name(T_record),
               macroWeighted(7),
               weightingPower(42.){
               component_name(component::Name::SCALAR);
        }

        double get_weighting_power(){
            return weightingPower;
        }
        int get_macro_weighted(){
            return weightingPower;
        }
        std::vector<component::Name> get_component_names() const{
            return component_names;
        }

    };


}//SOA

    template<record::Name T_record>
    HDNLINE std::vector<component::Name> record::get_names(const SOA::Record_3d<T_record>& record)
    {
        return record.get_component_names();

    }
