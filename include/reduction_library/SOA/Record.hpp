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


    struct Record : public X_component, public Y_component, public Z_component{
    private:
        int macroWeighted;
        double weightingPower;
        std::vector<component::Name> component_names;

    public:
        Record(const std::vector<double>& x_values,
               const std::vector<double>& y_values,
               const std::vector<double>& z_values):
               X_component(x_values),
               Y_component(y_values),
               Z_component(z_values),
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

    template<>
    HDNLINE std::vector<component::Name> record::get_names(const SOA::Record& record)
    {
        return record.get_component_names();

    }

    template<>
    HDNLINE record::traits::Type<component::Name::x, SOA::Record>::type
    record::get<component::Name::x, SOA::Record>(SOA::Record&& record)
    {
        double result = 0.0;
        return result;
    }

    template<>
    struct record::Geting_weighting_power<SOA::Record>
    {
    public:
      double operator() (SOA::Record&& record)
      {
          double weighting_power = record.get_weighting_power();
          return weighting_power;
      }

    };

    template<>
    struct record::Geting_macro_weighted<SOA::Record>
    {
    public:
      double operator() (SOA::Record&& record)
      {
          double weighting_power = record.get_macro_weighted();
          return weighting_power;
      }

    };


}// reduction_library

