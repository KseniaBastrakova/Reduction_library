//============================================================================

//============================================================================

#include <iostream>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include <vector>
#include <typeinfo>
#include "Attributes_getting.hpp"
#include "Particle_type.hpp"
#include "Thinning.hpp"
#include <stdlib.h>

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
	Particle first_particle;

	double current_momentum = get_momentum<Particle>(first_particle);

	double ratioDeletedParticles = 0.2;

	Thinning<Particle> testRandomThinning(ratioDeletedParticles);

	std::vector<Particle> testParticles;
	int startNumberParticles = 100;
	for (int i=0; i< startNumberParticles; i++){
		Particle currentParticle;
		testParticles.push_back(currentParticle);

	}

	testRandomThinning(testParticles);

	int numReducedParticles = 0;
	for (int i=0; i< startNumberParticles; i++){

		double& weihgting = get_weighting<Particle>(testParticles[i]);
		if (testParticles[i].weighting < 1)
			numReducedParticles++;


	}
	std::cout<<numReducedParticles<<std::endl;
	std::cout<< "ratio reduced particles "<<(float)(numReducedParticles)/startNumberParticles;

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
