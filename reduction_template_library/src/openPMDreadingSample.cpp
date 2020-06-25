//============================================================================

//============================================================================

#include <iostream>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include <vector>
#include <typeinfo>
#include "Attributes_getting.hpp"
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

	double current_momentum = get_attribute_momentum<Particle>(first_particle);
	double current_coordinates = get_attribute_coordinates<Particle>(first_particle);

	std::cout<<" current_momentum "<<current_momentum;
	std::cout<<" current_coordinates "<<current_coordinates;


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
