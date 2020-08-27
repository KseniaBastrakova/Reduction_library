
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
#include "reduction_library/SOA/Record.hpp"



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

    using Double_dataset_type = typename SOA::Dataset<double>;

    // make a component for weights
    auto weights_component = SOA::Component<Double_dataset_type>{};

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

    auto px_component = SOA::Component<Double_dataset_type>{};
    px_component.set_dataset(px_dataset);

    auto py_component = SOA::Component<Double_dataset_type>{};
    py_component.set_dataset(py_dataset);

    auto pz_component = SOA::Component<Double_dataset_type>{};
    pz_component.set_dataset(pz_dataset);


    // we build momemntum record, with three components
    auto momentum_record = record::make_record_XYZ(px_component, py_component, pz_component);


   // using Records = typename std::tuple<type_double_scalar_record, type_3d_vector>;
   // using Names = typename std::tuple<record::Name::Weighting, record::Name::Momentum>;
  //  Names test_names = std::make_tuple(record::Name::Weighting(), record::Name::Momentum());

  //  Records test_records = std::make_tuple(weights_record, momentum_record);

  //  SOA::Particle_species<Names, Records> simple_species_two_records(test_records);
    auto electrons_test = particle_species::make_species<record::Name::Weighting, record::Name::Momentum>( weights_record, momentum_record );

//    using particle_species_type = SOA::Particle_species<Names, Records>;
    using particle_species_type = decltype(electrons_test);
    Particle<particle_species_type> test_particle(1, electrons_test);

 //   using particle_type = Particle<particle_species_type>;


    // we check that we can get value form particle, for both records:
    // record::Name::weighting
    // TODO : make simple function for it


    //   b) it allows accessing and changing data through component interface

    // accessing


    auto value_weighting = particle::get<component::Name::SCALAR, record::Name::Weighting>(test_particle);

    auto value_momentum = particle::get<component::Name::X, record::Name::Momentum>(test_particle);

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


    /// test making of record


    auto result_3d_record = record::make_record
            <component::Name::X, component::Name::Y, component::Name::Z>(px_dataset, py_dataset, pz_dataset);

}

void test_all_factrories()
{
    using namespace reduction_library;

    // Finaly, we build complete particle species

    // we set arrays for 3-d momentum
    auto px_values_raw = std::vector<double>{1., 2., 5., 6., 77., 6., 17., 18., 59.};
    auto py_values_raw = std::vector<double>{1., 22., 35., 4., 5., 61., 77., 8., 98.};
    auto pz_values_raw = std::vector<double>{1., 23., 3., 4., 5., 64., 75., 81., 9.};

    // we build 3 components for 3-d momentum
    auto px_component = component::make_component(px_values_raw);
    auto py_component = component::make_component(py_values_raw);
    auto pz_component = component::make_component(pz_values_raw);

    // we build momentum record from 3 components
    auto momentum_record = record::make_record_XYZ(px_component, py_component, pz_component);

    // we set array for 2-d coordinates
    auto x_values_raw = std::vector<double>{2., 46., 38., 1., 116., 14., 20., 15., 14.};
    auto y_values_raw = std::vector<double>{21., 14., 0., 17., 2., 46., 38., 1., 116.};

    // we build 2 components for 2-d coordinates
    auto x_component = component::make_component(x_values_raw);
    auto y_component = component::make_component(y_values_raw);

    // we build position's record from 2 components
    auto position_record = record::make_record_XY(x_component, y_component);

    // we set arrays for weighting
    auto weighting_values_raw = std::vector<double>{15., 20., 28., 16., 30., 29., 123., 120., 8.};

    // we build 1 component for weighting
    auto weighting_component = component::make_component(weighting_values_raw);

    // we build weighting record
    auto weighting_record = record::make_record_scalar(weighting_component);

    // we set arrays for charge
    auto charge_values_raw = std::vector<double>{15., 20., 28., 16., 30., 29., 123., 120., 8.};

    // we build 1 component for charge
    auto charge_component = component::make_component(charge_values_raw);

    // we build charge record
    auto charge_record = record::make_record_scalar(charge_component);

    ////
    /// and, finaly, we build particle species: electrons
    ////

    auto electrons = particle_species::make_species<record::Name::Momentum,
                                                    record::Name::Position,
                                                    record::Name::Weighting,
                                                    record::Name::Charge>
                    (momentum_record, position_record, weighting_record, charge_record);


    /// we make point and check access
    using particle_species_type = decltype(electrons);
    Particle<particle_species_type> particle_3(2, electrons);

    // now, we print all data for third particle

    auto momentum_x = SOA::get_momentum_x(particle_3);
    std::cout<<" momentum/x should be 5  "<<momentum_x<<std::endl;

    auto momentum_y = SOA::get_momentum_y(particle_3);
    std::cout<<" momentum/y should be 35  "<<momentum_y<<std::endl;

    auto momentum_z = SOA::get_momentum_z(particle_3);
    std::cout<<" momentum/z should be 3  "<<momentum_z<<std::endl;

    auto position_x = SOA::get_position_x(particle_3);
    std::cout<<" position/x should be 38  "<<position_x<<std::endl;

    auto position_y = SOA::get_position_y(particle_3);
    std::cout<<" position/y should be 0  "<<position_y<<std::endl;

    auto weighting = SOA::get_weighting(particle_3);
    std::cout<<" weighting should be 28  "<<weighting<<std::endl;

    auto charge = SOA::get_charge(particle_3);
    std::cout<<" charge should be 28  "<<charge<<std::endl;

    // now, we set new values

    SOA::set_momentum_x(46., particle_3);
    std::cout<<" momentum/x should be 46.  "<<momentum_x<<std::endl;

    SOA::set_momentum_y(28., particle_3);
    std::cout<<" momentum/y should be 28  "<<momentum_y<<std::endl;

    SOA::set_momentum_z(91., particle_3);
    std::cout<<" momentum/z should be 91  "<<momentum_z<<std::endl;

    SOA::set_position_x(24., particle_3);
    std::cout<<" position/x should be 24  "<<position_x<<std::endl;

    SOA::set_position_y(56., particle_3);
    std::cout<<" position/y should be 56  "<<position_y<<std::endl;

    SOA::set_weighting(81., particle_3);
    std::cout<<" weighting should be 81  "<<weighting<<std::endl;

    SOA::set_charge(64., particle_3);
    std::cout<<" charge should be 64  "<<charge<<std::endl;





}




int main(){
    std::cout<<"start of reduction"<<std::endl;

   // testRawVectorsUseCase();
    test_all_factrories();







	return 0;
}


