//============================================================================

//============================================================================

#include <iostream>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include <vector>
#include <typeinfo>
#include "Attributes_getting.hpp"
#include "Thinning.hpp"
#include "Particles.hpp"
#include "Particles_attributes.hpp"
#include "Thinning_particles_spicialization.hpp"
#include <stdlib.h>

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
	Particle_st first_particle;

	double current_momentum = get_momentum<Particle_st>(first_particle);

	double ratioDeletedParticles = 0.2;

	Thinning testRandomThinning(ratioDeletedParticles);

	std::vector<Particle_st> testParticles;
	int startNumberParticles = 100;
	for (int i=0; i< startNumberParticles; i++){
		Particle_st currentParticle;
		testParticles.push_back(currentParticle);

	}

	testRandomThinning.operator()<Particle_st> (testParticles);

	int numReducedParticles = 0;
	for (int i=0; i < startNumberParticles; i++){

		double& weighting = get_weighting<Particle_st>(testParticles[i]);
		if (testParticles[i].weighting == 0)
			numReducedParticles++;


	}
	std::cout<<numReducedParticles<<std::endl;
	std::cout<< "ratio reduced particles "<<(float)(numReducedParticles)/startNumberParticles;

	std::vector<double> momentums;
	std::vector<double> weighting;

	for (int i=0; i < startNumberParticles; i++){
		 momentums.push_back(5.);
		 weighting.push_back(7.);
	}

	Particles testP(momentums, weighting);
	Thinning testRandomThinning_v2(ratioDeletedParticles);
    testRandomThinning_v2.operator ()<Particles>(testP);

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
