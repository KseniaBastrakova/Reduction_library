//============================================================================

//============================================================================

#include <iostream>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include <vector>
#include <memory>
#include <typeinfo>
#include "Thinning.hpp"
#include "Particles.hpp"
#include "Thinning_particles_spicialization.hpp"
#include <stdlib.h>
#include "Particle_reader.hpp"
#include "Particle_writer.hpp"

#include "Particlest.hpp"

using namespace std;
using std::cout;
using namespace openPMD;


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





int main(){
	std::string file_path("/home/kseniia/Documents/example-3d/hdf5/data00000%T.h5");
	int ratioDeletedParticles = 0.1;
	Particle_reader reader(file_path);
	Particles particles = reader.Read();

	Weights weights = static_cast<Weights>(particles);
	std::vector<double> values = weights.get();
	Thinning testRandomThinning_v2(ratioDeletedParticles);

	testRandomThinning_v2.operator ()<Particles>(particles);

	std::string file_path_result("/home/kseniia/Documents/example-3d/hdf5/result%T.h5");
	Particle_writer writter(file_path_result);
	writter.write(particles);


	return 0;
}
