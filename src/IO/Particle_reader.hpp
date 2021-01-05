/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <numeric>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include "reduction_library/record/Name.hpp"
#include "reduction_library/component/Name.hpp"

namespace reduction_library{
namespace IO{
using namespace openPMD;

struct Particle_patch{
    std::vector<std::size_t> num_particles;
    std::vector<std::size_t> num_particles_offset;
    Particle_patch(const std::vector<std::size_t>& num_particles,
                   std::vector<std::size_t> num_particles_offset):
                                            num_particles(num_particles),
                                            num_particles_offset(num_particles_offset){}

    std::pair<int, int> get(int num_patch){

        return std::make_pair(num_particles_offset[num_patch - 1], num_particles_offset[num_patch]);
    }

    std::size_t num_patches(){
        return num_particles_offset.size() - 1;

    }
};


class Particle_reader{
    std::vector<std::string> record_names;
    openPMD::Series& series;

public:
    Particle_reader(std::vector<std::string> record_names, openPMD::Series& series):
        record_names(record_names), series(series){}

    auto get_data_chunk(int iteration, std::string name_species, int num_patch){
/*
        std::map<std::string, std::vector<std::vector<double>>> data_chunk;

        Iteration& i = series.iterations[iteration];
        openPMD::ParticleSpecies& species = i.particles[name_species];
        Particle_patches patch(series, species);
        std::pair<int, int> range = patch.get(num_patch);

        for (auto record_name: record_names){

            std::vector<std::vector<double>> record_values = Read_record(species, record_name, range);
            data_chunk[record_name] = record_values;
        }
        return data_chunk;
        */
        return 0;
    }

    std::vector<std::vector<double>> Read_record(openPMD::ParticleSpecies& species,
            std::string record_name, std::pair<int, int> range){

        Record& record = species[record_name];
        std::vector<std::vector<double>> record_values;
        std::cout<<"range.first  "<<range.first<<" range.second "<<range.second<<std::endl;
        for (auto com: record){
            auto current_component = com.second;
            auto ptr = current_component.loadChunk<double>();
            series.flush();
            std::vector<double> result(ptr.get() + range.first, ptr.get()+ range.second);
            series.flush();
            record_values.push_back(result);
        }
        return record_values;
    }

    IO::Particle_patch get_patch(openPMD::ParticleSpecies& species){
        ParticlePatches& particle_patches = species.particlePatches;
        std::size_t size = particle_patches["numParticles"][RecordComponent::SCALAR].getExtent()[0];
        std::vector<std::size_t> num_particles;
        std::vector<std::size_t> num_particles_offset;

        if (size == 1){
            auto it = species.begin();
            auto record = (*it).second;
            auto it_component = record.begin();
            auto component = (*it_component).second;
            std::size_t first_component_size = component.getExtent()[0];
            num_particles.push_back(first_component_size);
        }

        num_particles_offset.resize(num_particles.size());
        num_particles_offset.push_back(0);
        std::partial_sum(num_particles.begin(), num_particles.end(), num_particles_offset.begin() + 1, std::plus<std::size_t>());

        Particle_patch patch(num_particles, num_particles_offset);
        return patch;
    }
     // first one -- momentum, second one -- position
    std::pair<std::size_t, std::size_t> get_dimensions(openPMD::ParticleSpecies& species){
        std::size_t momentum_size = species["momentum"].size();
        std::size_t position_size = species["position"].size();
        return std::pair<std::size_t, std::size_t>(momentum_size, position_size);
    }

    };
} //IO
} //reduction_library






