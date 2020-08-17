
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



void testRawVectorsUseCase()
{
    using namespace reduction_library;

    // Use case: client app has data as raw arrays or vectors
    // here we mark these as ..._raw variables
    auto px_values_raw = std::vector<double>{1., 2., 3., 4., 5., 6., 7., 8., 9.};
    auto py_values_raw = std::vector<double>{1., 2., 3., 4., 5., 6., 7., 8., 9.};
    auto pz_values_raw = std::vector<double>{1., 2., 3., 4., 5., 6., 7., 8., 9.};
    auto weights_raw = std::vector<double>{11., 12., 13., 14., 15., 16., 17., 18., 19.};

    // make a data set out of a raw vector, later will be constructor/factory
    auto weights_dataset = SOA::Dataset<double>{};
    weights_dataset.set_values(weights_raw);

    // make a component for weights
    auto weights_component = SOA::Component<double>{};
    weights_component.set_dataset(weights_dataset);


    /// TODO
    auto weights_record = SOA::makeScalarRecord( weights_component );
    auto & weights_component_again = record::get< component::Name::SCALAR >( weights_record );
    /// check that
    // a) weights_component_again is of correct type
    // b) it allows accessing and changing data through component interface
    // c) when you change values, the actual record data changes

    /// TODO
    auto momentum_record = SOA::makeVectorRecord( px_component, py_component, pz_component );

    using type_double_scalar_record = reduction_library::SOA::Scalar_record<double>;
    reduction_library::SOA::Scalar_record<double> weighting_record;
    auto record = reduction_library::SOA::Record_creation<type_double_component>::create(scalar_component);
    record.print_component();
}



int main(){

    testRawVectorsUseCase();

    std::cout<<"start of reduction"<<std::endl;



    // **** we build record for scalar component ****


    using type_double_scalar_record = reduction_library::SOA::Scalar_record<double>;
    using type_double_component = reduction_library::SOA::Component<double>;

    reduction_library::SOA::Scalar_record<double> weighting_record;


    auto record = reduction_library::SOA::Record_creation<type_double_component>::create(scalar_component);
    record.print_component();
    using test_particle_type = reduction_library::Particle<type_double_scalar_record>;
    reduction_library::Particle<type_double_scalar_record> test_particle_weighting(1, record);


    auto value = reduction_library::component::get<component::Name::SCALAR, record::Name::weighting, test_particle_type>(test_particle_weighting);
    std::cout<<"getting first values in weighting dataset : should be 12  "<<value<<std::endl;
    /// auto weight0 = component::getWeighting( test_particle_weighting );
    /// auto px0 = component::getMomentumX( test_particle_weighting );


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
