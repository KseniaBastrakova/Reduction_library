#pragma once

#include <string>
#include "Particles.hpp"
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include <algorithm>

using namespace openPMD;
class Particle_writer{
	std::string file_name;

public:
	Particle_writer(std::string file_name):
		file_name(file_name){}

	void write(Particles particles_to_write){

		std::vector<double> momentum = particles_to_write.momentum;
		std::vector<double> weights = particles_to_write.weights;
		std::shared_ptr<double> type_ptr = std::make_shared<double>(momentum[0]);

		 Series series = Series(
				 file_name,
		        Access::CREATE
		    );
		 ParticleSpecies& e = series.iterations[100].particles["e"];
		 e["momentum"]["x"].resetDataset(Dataset(determineDatatype(type_ptr), {1}));
		 series.flush();

		 e["momentum"]["x"].storeChunk(momentum,  {1});
		 series.flush();

		 e["weighting"][openPMD::RecordComponent::SCALAR].resetDataset(Dataset(determineDatatype(type_ptr), {1}));
		 e["weighting"][openPMD::RecordComponent::SCALAR].storeChunk(weights,  {1});
		 series.flush();

	}

};
