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

#include "../include/reduction_library/AOS/Particle_spicies.hpp"
#include "reduction_library/attribute/Scalar_records_names.hpp"
#include "IO/Particle_reader.hpp"
#include "IO/Particle_writer.hpp"
#include "reduction_library/SOA/Particlest.hpp"

using namespace std;
using std::cout;
using namespace openPMD;
using namespace reduction_library;


struct A {
	template<class T>
    int operator()(int input){

		std::cout<<typeid(T).name();
		return 1;
	}

	template< int n, typename... Params >
    int operator()(int input){ return -1; }

};


struct Loader
{
	template<class T, typename... Args>
	void operator()(
			std::vector<std::string> names,
			Args &&... args)
	{
		Datatype type = Datatype::INT;
		// TODO: determine type based on names.back()
		if (names.empty())
				return;
		std::cout << "loading with name = " << names.back() << "\n";
		names.pop_back();
		std::vector<T> newArg;
		switchType< void >(Datatype::INT, *this, names, args..., newArg);
	}

	template< int n, typename... Args >
	void operator()(std::vector<std::string> names,
			Args &&... args){}
};

openPMD::ParticleSpecies get_test_electrons(std::string file_path)
{

    openPMD::Series series = openPMD::Series(
            file_path,
            openPMD::Access::READ_ONLY
             );
    openPMD::Iteration i = series.iterations[100];
    openPMD::ParticleSpecies electrons = i.particles["electrons"];
    return electrons;
}

int main(){
    std::string file_path("/home/kseniia/Documents/example-3d/hdf5/data00000%T.h5");

    openPMD::Series series = openPMD::Series(
               file_path,
               openPMD::Access::READ_ONLY
                );
    int ratioDeletedParticles = 0.1;
    openPMD::Iteration i = series.iterations[100];
    openPMD::ParticleSpecies electrons = i.particles["electrons"];

    openPMD::RecordComponent current_record = electrons["momentum"]["x"];

     std::shared_ptr<double> values_ptr = current_record.loadChunk<double>();
     series.flush();

     std::vector<std::uint64_t> values_extent = current_record.getExtent();
     int size_of_series = values_extent[0];
     series.flush();

     std::cout<<"size_of_series "<<size_of_series<<"  "<<values_ptr.get()[0]<<"  "<<std::endl;

     std::vector<double> record_component_values;
     record_component_values.assign(values_ptr.get(), values_ptr.get() + size_of_series);

     for (int i=0; i<10; i++)
         std::cout<<record_component_values[i]<<"  ";

     IO::Particle_reader reader(file_path, series);
 //   std::vector<double> momentum_x = reader.Read_attribute<reduction_library::Attribute::momentum_x, double>(reduction_library::Attribute::momentum_x, electrons);

//	Weights weights = static_cast<Weights>(particles);
//	std::vector<double> values = weights.get();
//	Thinning testRandomThinning_v2(ratioDeletedParticles);

	//testRandomThinning_v2.operator ()<Particles>(particles);

	//std::string file_path_result("/home/kseniia/Documents/example-3d/hdf5/result%T.h5");
	//Particle_writer writter(file_path_result);
	//writter.write(particles);


	return 0;
}
