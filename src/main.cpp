
#include <iostream>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include <vector>
#include <memory>
#include <typeinfo>

#include "reduction_library/SOA/Record_getters.hpp"
#include "reduction_library/SOA/Particle.hpp"

#include "reduction_library/record/Name.hpp"
#include "reduction_library/SOA/Component.hpp"

#include "reduction_library/SOA/Dataset.hpp"
#include "reduction_library/SOA/Particle_species.hpp"
#include "reduction_library/SOA/Record.hpp"
#include "IO/Particle_reader.hpp"



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

    auto momentum_x = particle::get_momentum_x(particle_3);
    std::cout<<" momentum/x should be 5  "<<momentum_x<<std::endl;

    auto momentum_y = particle::get_momentum_y(particle_3);
    std::cout<<" momentum/y should be 35  "<<momentum_y<<std::endl;

    auto momentum_z = particle::get_momentum_z(particle_3);
    std::cout<<" momentum/z should be 3  "<<momentum_z<<std::endl;

    auto position_x = particle::get_position_x(particle_3);
    std::cout<<" position/x should be 38  "<<position_x<<std::endl;

    auto position_y = particle::get_position_y(particle_3);
    std::cout<<" position/y should be 0  "<<position_y<<std::endl;

    auto weighting = particle::get_weighting(particle_3);
    std::cout<<" weighting should be 28  "<<weighting<<std::endl;

    auto charge = particle::get_charge(particle_3);
    std::cout<<" charge should be 28  "<<charge<<std::endl;

    // now, we set new values

    particle::set_momentum_x(46., particle_3);
    momentum_x = particle::get_momentum_x(particle_3);
    std::cout<<" momentum/x should be 46.  "<<momentum_x<<std::endl;

    particle::set_momentum_y(28., particle_3);
    momentum_y = particle::get_momentum_y(particle_3);
    std::cout<<" momentum/y should be 28  "<<momentum_y<<std::endl;

    particle::set_momentum_z(91., particle_3);
    momentum_z = particle::get_momentum_z(particle_3);
    std::cout<<" momentum/z should be 91  "<<momentum_z<<std::endl;

    particle::set_position_x(24., particle_3);
    position_x = particle::get_position_x(particle_3);
    std::cout<<" position/x should be 24  "<<position_x<<std::endl;

    particle::set_position_y(56., particle_3);
    position_y = particle::get_position_y(particle_3);
    std::cout<<" position/y should be 56  "<<position_y<<std::endl;

    particle::set_weighting(81., particle_3);
    weighting = particle::get_weighting(particle_3);
    std::cout<<" weighting should be 81  "<<weighting<<std::endl;

    particle::set_charge(64., particle_3);
    charge = particle::get_charge(particle_3);
    std::cout<<" charge should be 64  "<<charge<<std::endl;

}

void raw_data_reader(){

    std::string file_name("/home/kseniia/Documents/openPMD-example-datasets/example-3d/hdf5/data00000%T.h5");
    Series series = Series(
            "/home/kseniia/Documents/openPMD-example-datasets/example-3d/hdf5/data00000%T.h5",
            Access::READ_WRITE
        );

    IO::Particle_reader reader(file_name, series);
    reader.Read();

}


int main(){
    std::cout<<"start of reduction"<<std::endl;


   // test_all_factrories();
    raw_data_reader();







	return 0;
}


