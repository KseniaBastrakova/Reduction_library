
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
#include "reduction_library/SOA/Record_creation.hpp"



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

    // **** we build record for scalar component ****

    std::vector<double> weights = {11., 12., 13., 14., 15., 16., 17., 18., 19.};
    reduction_library::SOA::Dataset<double> scalar_dataset;
    scalar_dataset.set_values(weights);
    reduction_library::SOA::Component<double> scalar_component;
    scalar_component.set_dataset(scalar_dataset);

    using type_double_scalar_record = reduction_library::SOA::Scalar_record<double>;
    using type_double_component = reduction_library::SOA::Component<double>;

    reduction_library::SOA::Scalar_record<double> weighting_record;


    auto record = reduction_library::SOA::Record_creation<type_double_component>::create(scalar_component);
    record.print_component();
    using test_particle_type = reduction_library::Particle<type_double_scalar_record>;
    reduction_library::Particle<type_double_scalar_record> test_particle_weighting(1, record);


    auto value = reduction_library::component::get<component::Name::SCALAR, record::Name::weighting, test_particle_type>(test_particle_weighting);
    std::cout<<"getting first values in weighting dataset : should be 12  "<<value<<std::endl;

    /// now, we change the value to 77.6
    double new_value = 77.6;
    reduction_library::component::set<component::Name::SCALAR, record::Name::weighting, test_particle_type, double>
        (new_value, test_particle_weighting);

    value = reduction_library::component::get<component::Name::SCALAR, record::Name::weighting, test_particle_type>(test_particle_weighting);
    std::cout<<"getting first values in weighting dataset : should be 77.6  "<<value<<std::endl;

    // we check attributes for component: unit_SI
    double test_si = 42.;
    reduction_library::component::set_unit_SI<type_double_component>(scalar_component, test_si);
    auto unit_si_component = reduction_library::component::get_unit_SI<type_double_component>(scalar_component);
    std::cout<<" getting unit si for scalar component : the value sould be 42.  " <<unit_si_component<<std::endl;

    // we check attributes for scalar_record: macro weighted, weighting power

    auto macro_weighted_record = reduction_library::record::get_macro_weighted<type_double_scalar_record>(std::move(record));
    std::cout<<"getting macro weighted for record :: should be  "<<macro_weighted_record<< std::endl;




	return 0;
}
