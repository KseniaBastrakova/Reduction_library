
#include <iostream>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include <vector>
#include <memory>
#include <typeinfo>

#include "reduction_library/SOA/Particle.hpp"

#include "reduction_library/record/Name.hpp"
#include "reduction_library/SOA/Record_scalar.hpp"
#include "reduction_library/SOA/Component.hpp"
#include "reduction_library/SOA/Dataset.hpp"



using namespace std;
using std::cout;
using namespace openPMD;
using namespace reduction_library;

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}



int main(){
    std::cout<<"start of reduction"<<std::endl;

    std::vector<double> x_values = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
    std::vector<double> y_values = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
    std::vector<double> z_values = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
    reduction_library::SOA::Dataset<double> values_x;
    using test_Scalar_record = reduction_library::SOA::Scalar_record<double>;
    reduction_library::SOA::Scalar_record<double> weighting_record;
    auto & component = weighting_record.get_component();
   // reduction_library::SOA::Component<double, test_Scalar_record> component;
//
  //

	return 0;
}
