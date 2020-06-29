//============================================================================

//============================================================================

#include <iostream>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include <vector>
#include <memory>
#include <typeinfo>
#include "Attributes_getting.hpp"
#include "Thinning.hpp"
#include "Particles.hpp"
#include "Particles_attributes.hpp"
#include "Thinning_particles_spicialization.hpp"
#include <stdlib.h>
#include "Particle_reader.hpp"
#include"Particle_writer.hpp"

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
	std::shared_ptr<Particles> particles = reader.Read();
	Thinning testRandomThinning_v2(ratioDeletedParticles);
	testRandomThinning_v2.operator ()<Particles>(*particles.get());

	std::string file_path_result("/home/kseniia/Documents/example-3d/hdf5/result%T.h5");
	Particle_writer writter(file_path_result);
	writter.write(*particles.get());



 //   for (int i=0; i < startNumberParticles; i++){

   // 		 std::cout<<weighting[i]<<std::endl;
    //	}

//	int input = 5;
	//static A a;
	//auto ret = switchType< int >(Datatype::INT, a, input);
	//std::cout << ret;


	//std::vector<std::string> names;
	//names.push_back("name1");
	//names.push_back("name2");
	//names.push_back("name3");
//Loader loader;
//	switchType< void >(Datatype::INT, loader, names);

	 //   ParticleSpecies electrons = particles[0];
	   // auto chargeRecord = electrons["charge"][openPMD::RecordComponent::SCALAR];

	return 0;
}
