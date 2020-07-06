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

	Particles Read(){

		Series series = Series(
				file_name,
		        Access::READ_ONLY
		    );
		Iteration i = series.iterations[100];
		openPMD::ParticleSpecies electrons = i.particles["electrons"];
		std::shared_ptr<double> momentum_ptr = electrons["momentum"]["x"].loadChunk<double>();
		std::vector<std::uint64_t> momentum_extent = electrons["momentum"]["x"].getExtent();
		series.flush();
		int size_of_series = momentum_extent[0];
		std::shared_ptr<double> weights_ptr = electrons["weighting"]
														[openPMD::RecordComponent::SCALAR].loadChunk<double>();
		std::vector<std::uint64_t> weights_extent = electrons["weighting"]
															  [openPMD::RecordComponent::SCALAR].getExtent();

		series.flush();
		std::vector<double> weights;
				weights.assign(weights_ptr.get(),  weights_ptr.get() + size_of_series);

		std::vector<double> momentum;
		momentum.assign(momentum_ptr.get(),  momentum_ptr.get() + size_of_series);

		Particles result_particles(weights, momentum);

		return result_particles;

	}

};
