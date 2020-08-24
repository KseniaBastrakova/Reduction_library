
#include <iostream>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include <vector>
#include <memory>
#include <typeinfo>

#include "reduction_library/SOA/Record_getters.hpp"
#include "reduction_library/SOA/Particle.hpp"

#include "reduction_library/record/Name.hpp"
#include "reduction_library/SOA/Record_scalar.hpp"
#include "reduction_library/SOA/Record_3d.hpp"
#include "reduction_library/SOA/Component.hpp"

#include "reduction_library/SOA/Dataset.hpp"
#include "reduction_library/SOA/Particle_species.hpp"



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
    auto px_values_raw = std::vector<double>{1., 2., 5., 6., 77., 6., 17., 18., 59.};
    auto py_values_raw = std::vector<double>{1., 22., 35., 4., 5., 61., 77., 8., 98.};
    auto pz_values_raw = std::vector<double>{1., 23., 3., 4., 5., 64., 75., 81., 9.};
    auto weights_raw = std::vector<double>{11., 12., 13., 14., 15., 16., 17., 18., 19.};

    // make a data set out of a raw vector, later will be constructor/factory
    auto weights_dataset = SOA::Dataset<double>{};
    weights_dataset.set_values(weights_raw);

    // make a component for weights
    auto weights_component = SOA::Component<double>{};

    weights_component.set_dataset(weights_dataset);

    /// Part with scalar record
    ////
    ///


    auto weights_record = record::make_scalar_record( weights_component);
    // we print before:


    auto & weights_component_again = record::get< component::Name::SCALAR >( weights_record );
    // we check that:

    // 1) weights_component_again is of correct type


    std::cout<<" dataset before :"<<std::endl;
    weights_component.print_dataset();
    std::cout<<" dataset after (should be same) :"<<std::endl;
    weights_component_again.print_dataset();



    using type_double_scalar_record = SOA::Scalar_record<double>;
    using type_3d_vector = SOA::Record_3d<double, double, double>;
    using particle_species_type = SOA::Particle_species<type_3d_vector, type_double_scalar_record>;
    using test_particle_type = Particle<type_double_scalar_record>;




 //   auto value = component::get<component::Name::SCALAR, record::Name::weighting, particle_species_type>(test_particle_weighting);

   // auto value = get_weighting( particle );


    //// end of part with scalar record
    ///

    // make a data set out of a raw vector for 3d vector

    auto px_dataset = SOA::Dataset<double>{};
    px_dataset.set_values(px_values_raw);

    auto py_dataset = SOA::Dataset<double>{};
    py_dataset.set_values(py_values_raw);

    auto pz_dataset = SOA::Dataset<double>{};
    pz_dataset.set_values(pz_values_raw);

    auto px_component = SOA::Component<double>{};
    px_component.set_dataset(px_dataset);

    auto py_component = SOA::Component<double>{};
    py_component.set_dataset(py_dataset);

    auto pz_component = SOA::Component<double>{};
    pz_component.set_dataset(pz_dataset);

    // we build momemntum record, with three components
    auto momentum_record = record::make_momentum_record<double, double, double>(px_component, py_component, pz_component);

    SOA::Particle_species<type_3d_vector, type_double_scalar_record> simple_species_two_records(momentum_record, weights_record);

    Particle<particle_species_type> test_particle(1, simple_species_two_records);

    using particle_type = Particle<particle_species_type>;


    // we check that we can get value form particle, for both records:
    // record::Name::weighting
    // TODO : make simple function for it


    //   b) it allows accessing and changing data through component interface

    // accessing


    auto value_weighting = particle::get<component::Name::SCALAR, record::Name::Weighting, particle_type>(test_particle);
    auto value_weighting_2 = SOA::get_weighting(test_particle);

    std::cout<<"test weight value (should be 12)  : "<< value_weighting_2<<std::endl;
    std::cout<<"test weight value (should be 12)  : "<< value_weighting<<std::endl;
    auto value_x = SOA::get_momentum_x(test_particle); //component::get<component::Name::x, record::Name::momentum, particle_type>(test_particle);
    std::cout<<" test momentum  x value (should be 2)  : "<<value_x<<std::endl;

    auto value_y = SOA::get_momentum_y(test_particle); //component::get<component::Name::y, record::Name::momentum, particle_type>(test_particle);
    std::cout<<" test momentum  y value (should be 22)  : "<<value_y<<std::endl;

    auto value_z = SOA::get_momentum_z(test_particle); //component::get<component::Name::z, record::Name::momentum, particle_type>(test_particle);
    std::cout<<" test momentum  z value (should be 23)  : "<<value_z<<std::endl;


    // when we change values, the actual record data changes

    double new_weighting = 47.;
    SOA::set_weighting(new_weighting, test_particle);
   // component::set<component::Name::SCALAR, record::Name::weighting, particle_type, double>(new_weighting, test_particle);
    value_weighting = SOA::get_weighting(test_particle); //component::get<component::Name::SCALAR, record::Name::weighting, particle_type>(test_particle);
    std::cout<<"test weight value (should be 47)  : "<< value_weighting<<std::endl;

    SOA::set_weighting(48., test_particle);
    value_weighting_2 = SOA::get_weighting(test_particle);
    std::cout<<"test weight value (should be 48.)  : "<< value_weighting_2<<std::endl;

    double new_value_x = 64.;
    SOA::set_momentum_x(new_value_x, test_particle);
    //component::set<component::Name::x, record::Name::momentum, particle_type, double>(new_weighting, test_particle);
    value_x = SOA::get_momentum_x(test_particle); //component::get<component::Name::x, record::Name::momentum, particle_type>(test_particle);
    std::cout<<" test momentum  x value (should be 64)  : "<<value_x<<std::endl;


    double new_value_y = 78.;
    SOA::set_momentum_y(new_value_y, test_particle);
   // component::set<component::Name::y, record::Name::momentum, particle_type, double>(new_weighting, test_particle);
    value_y = SOA::get_momentum_y(test_particle); //component::get<component::Name::y, record::Name::momentum, particle_type>(test_particle);
    std::cout<<" test momentum  y value (should be 78)  : "<<value_y<<std::endl;

    double new_value_z = 51.;
    SOA::set_momentum_z(new_value_z, test_particle);
  //  component::set<component::Name::z, record::Name::momentum, particle_type, double>(new_weighting, test_particle);
    value_y = SOA::get_momentum_z(test_particle); //component::get<component::Name::z, record::Name::momentum, particle_type>(test_particle);
    std::cout<<" test momentum  z value (should be 51)  : "<<value_z<<std::endl;

}




int main(){
    std::cout<<"start of reduction"<<std::endl;

    testRawVectorsUseCase();





	return 0;
}

/*


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
// template<component::Name Component_name, record::Name Record_name, typename T_particle, typename T_dataset>
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

*/
