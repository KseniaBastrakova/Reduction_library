#pragma once

#include <string>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include <algorithm>

#include "../../include/reduction_library/AOS_f/Particle_spicies.hpp"

namespace reduction_library{
namespace IO{

using namespace attribute;

    class Particle_writer{
        std::string file_name;

    public:
        Particle_writer(std::string file_name):
            file_name(file_name){}

        void write(AOS::Particle_spicies particles_to_write){

            AOS::Momentums momentum = static_cast<AOS::Momentums>(particles_to_write);
            AOS::Weights weights = static_cast<AOS::Weights>(particles_to_write);

            std::vector<double> momentum_values = momentum.get();
            std::vector<double> weights_values  = weights.get();
            std::shared_ptr<double> type_ptr = std::make_shared<double>(momentum_values[0]);

            openPMD::Series series = openPMD::Series(
                     file_name,
                     openPMD::Access::CREATE
                );

             unsigned int series_size = momentum_values.size();
             openPMD::ParticleSpecies& e = series.iterations[100].particles["e"];
             openPMD::Extent dims{series_size};
             openPMD::Datatype dtype = openPMD::determineDatatype(type_ptr);
             openPMD::Dataset d = openPMD::Dataset(dtype, dims);
             e["momentum"]["x"].resetDataset(d);
             series.flush();

             e["momentum"]["x"].storeChunk(momentum_values);
             series.flush();

             e["weighting"][openPMD::RecordComponent::SCALAR].resetDataset(d);
             e["weighting"][openPMD::RecordComponent::SCALAR].storeChunk(weights_values);
             series.flush();

        }

    };
} //IO
} //reduction_library{

