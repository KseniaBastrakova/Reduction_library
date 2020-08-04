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

    using X_component = Component<component::Name::x, double>;
    using Y_component = Component<component::Name::y, double>;
    using Z_component = Component<component::Name::z, double>;

    template<record::Name T_record>
    struct Record_3d : public X_component, public Y_component, public Z_component{
    private:
        int macroWeighted;
        double weightingPower;
        std::vector<component::Name> component_names;
        record::Name record_name;

    public:
        Record_3d(const std::vector<double>& x_values,
               const std::vector<double>& y_values,
               const std::vector<double>& z_values):
               X_component(x_values),
               Y_component(y_values),
               Z_component(z_values),
               record_name(T_record),
               macroWeighted(7),
               weightingPower(42.){
               component_names.push_back(component::Name::x);
               component_names.push_back(component::Name::y);
               component_names.push_back(component::Name::z);
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

    template<>
    HDNLINE typename record::traits::Type<component::Name::x, SOA::Record_3d<record::Name::momentum>>::type
    record::get<component::Name::x, SOA::Record_3d<record::Name::momentum>>(SOA::Record_3d<record::Name::momentum>& record)
    {
        double result = 777.0;
        return result;
    }

    template<record::Name T_record>
    struct record::Geting_weighting_power<SOA::Record_3d<T_record>>
    {
    public:
      double operator() (SOA::Record_3d<T_record>& record)
      {
          double weighting_power = record.get_weighting_power();
          return weighting_power;
      }

    };


    template<record::Name T_record>
    struct record::Geting_macro_weighted<SOA::Record_3d<T_record>>
    {
    public:
      double operator() (SOA::Record_3d<T_record>&& record)
      {
          double weighting_power = record.get_macro_weighted();
          return weighting_power;
      }

    };

}// reduction_library

