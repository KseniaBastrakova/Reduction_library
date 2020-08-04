//============================================================================

//============================================================================

#include <iostream>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include <vector>
#include <memory>
#include <typeinfo>
#include "reduction_library/thinning/Thinning.hpp"
#include "reduction_library/thinning/Thinning_particles_spicialization.hpp"
#include <stdlib.h>

#include "../include/reduction_library/SOA/Particle_spicies_old.hpp"
#include "../include/reduction_library/SOA/Record_3d.hpp"
#include "reduction_library/AOS/Particlest.hpp"
#include "reduction_library/Scalar_records_names.hpp"
#include "IO/Particle_reader.hpp"
#include "IO/Particle_writer.hpp"
#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/SOA/Component.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Particle.hpp"
#include "reduction_library/SOA/Record_3d.hpp"
#include "reduction_library/SOA/Record_scalar.hpp"
#include "reduction_library/record/Name.hpp"

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


    reduction_library::SOA::Component<reduction_library::component::Name::x, double> component_x(x_values);
    reduction_library::SOA::Component<reduction_library::component::Name::y, double> component_y(y_values);
    reduction_library::SOA::Component<reduction_library::component::Name::z, double> component_z(z_values);

    double get_unit_si_x = reduction_library::get_unit_SI (component_x);
    std::cout<<"get_unit_si x "<<get_unit_si_x<<std::endl;

    double get_unit_si_y = reduction_library::get_unit_SI (component_y);
    std::cout<<"get_unit_si  y "<<get_unit_si_y<<std::endl;

    double get_unit_si_z = reduction_library::get_unit_SI (component_z);
    std::cout<<"get_unit_si  z "<<get_unit_si_z<<std::endl;

    std::vector<double> weights = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
    std::vector<double> momentums = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
  //  SOA::Particle_spicies_old test_particles_spieces(momentums, weights);
   // reduction_library::Particle<SOA::Particle_spicies_old> test_particles(1, test_particles_spieces);

    //auto get_component = reduction_library::component::get<SOA::Component<component::Name::x, double>,
      //      Particle<SOA::Particle_spicies_old>>(test_particles);
/*
    std::cout<<"get_component "<<get_component<<std::endl;

    reduction_library::SOA::Scalar_record<reduction_library::record::Name::weighting> weighting_record(weights);
    reduction_library::SOA::Record_3d<reduction_library::record::Name::momentum> momentum(x_values, y_values, z_values);

    std::vector<component::Name>component_names = record::get_names(momentum);
    component::Name current_coponent = component_names[0];
    std::cout<<as_integer(current_coponent)<<std::endl;

    auto result = reduction_library::record::get<reduction_library::component::Name::x,
            reduction_library::SOA::Record_3d<record::Name::momentum>>(momentum);

    std::cout<<" result "<<result<<std::endl; */




	return 0;
}
