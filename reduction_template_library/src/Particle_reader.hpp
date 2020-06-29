#pragma once
#include <string>
#include "Particles.hpp"
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>

using namespace openPMD;
class Particle_reader{
	std::string file_name;

public:
	Particle_reader(std::string file_name):
		file_name(file_name){}

	std::shared_ptr<Particles> Read(){

		Series series = Series(
				file_name,
		        Access::READ_ONLY
		    );
		Iteration i = series.iterations[100];
		openPMD::ParticleSpecies electrons = i.particles["electrons"];
		std::shared_ptr<double> momentum_ptr = electrons["momentum"]["x"].loadChunk<double>();
		std::vector<std::uint64_t> momentum_extent = electrons["momentum"]["x"].getExtent();
		series.flush();

		std::shared_ptr<double> weights_ptr = electrons["momentum"]["x"].loadChunk<double>();
				std::vector<std::uint64_t> weights_extent = electrons["momentum"]["x"].getExtent();
		series.flush();

		std::vector<double> momentum = std::vector<double>(momentum_ptr.get()[0], momentum_ptr.get()[momentum_extent[0]]);
		std::vector<double> weights = std::vector<double>(weights_ptr.get()[0], weights_ptr.get()[weights_extent[0]]);

		std::shared_ptr<Particles> result_particles = std::make_shared<Particles>(momentum, weights);

		return result_particles;

	}

};
