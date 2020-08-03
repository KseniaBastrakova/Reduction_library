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

#include "reduction_library/AOS/Particlest.hpp"
#include "reduction_library/SOA/Particle_spicies.hpp"
#include "reduction_library/Scalar_records_names.hpp"
#include "IO/Particle_reader.hpp"
#include "IO/Particle_writer.hpp"
#include "reduction_library/record/Interfaces.hpp"
#include "reduction_library/SOA/Record.hpp"
#include "reduction_library/SOA/Component.hpp"
#include "reduction_library/component/Name.hpp"

using namespace std;
using std::cout;
using namespace openPMD;
using namespace reduction_library;



int main(){
    std::cout<<"start of reduction"<<std::endl;

    std::vector<double> x_values = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
    std::vector<double> y_values = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
    std::vector<double> z_values = {1., 2., 3., 4., 5., 6., 7., 8., 9.};

    reduction_library::SOA::Component<reduction_library::component::Name::x, double> component_x(x_values);
    reduction_library::SOA::Component<reduction_library::component::Name::y, double> component_y(y_values);
    reduction_library::SOA::Component<reduction_library::component::Name::z, double> component_z(z_values);



	return 0;
}
