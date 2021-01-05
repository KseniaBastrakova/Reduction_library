/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once
#include <iostream>
#include <vector>
#include <openPMD/openPMD.hpp>
#include "reduction_library/SOA/Record.hpp"
#include "reduction_library/helpers/Type_list.hpp"


using namespace reduction_library;

using namespace openPMD;

template <int Dim>
auto make_record_raw_data(std::vector<std::vector<double>> data);

template <>
auto make_record_raw_data<3>(std::vector<std::vector<double>> data){
    auto x_component = component::make_component(data[0]);
    auto y_component = component::make_component(data[1]);
    auto z_component = component::make_component(data[2]);
    return record::make_record_XYZ(x_component, y_component, z_component);
}

template <>
auto make_record_raw_data<2>(std::vector<std::vector<double>> data){
    auto x_component = component::make_component(data[0]);
    auto y_component = component::make_component(data[1]);
    return record::make_record_XY(x_component, y_component);
}

template <>
auto make_record_raw_data<1>(std::vector<std::vector<double>> data){
    auto scalar_component = component::make_component(data[0]);
    return record::make_record_scalar(scalar_component);
}


template <typename Record_name>
std::vector<std::vector<double>> read_data_chunk(Series series, ParticleSpecies species, Record_name record_name){
    std::vector<double> raw_1 ={1., 2., 3., 4., 5., 6., 7.};
    std::vector<double> raw_2 ={1., 2., 3., 4., 5., 6., 7.};
    std::vector<double> raw_3 ={1., 2., 3., 4., 5., 6., 7.};
    std::vector<std::vector<double>> result_data;
    result_data.push_back(raw_1);
    result_data.push_back(raw_2);
    result_data.push_back(raw_3);
    return result_data;

}

template <int Dim_momentum, int Dim_position>
auto make_species_raw(IO::Particle_reader& reader, ParticleSpecies species, std::pair<int, int> range){

    auto charge_data = reader.Read_record(species, "charge", range);
    auto charge_record = make_record_raw_data<1>(charge_data);

    auto momentum_data = reader.Read_record(species, "momentum", range);
    auto momentum_record = make_record_raw_data<Dim_momentum>(momentum_data);

    auto position_data = reader.Read_record(species, "position", range);
    auto position_record = make_record_raw_data<Dim_position>(position_data);

    auto weighting_data = reader.Read_record(species, "weighting", range);
    auto weighting_record = make_record_raw_data<1>(weighting_data);

    auto electrons = particle_species::make_species<record::name::Momentum,
                                                        record::name::Position,
                                                        record::name::Weighting,
                                                        record::name::Charge>
                        (momentum_record, position_record, weighting_record, charge_record);

    return electrons;
}

template <int Dim_momentum, int Dim_position>
void process(IO::Particle_reader& reader, ParticleSpecies species, std::vector<std::string> records_names){

    using namespace reduction_library;

    auto patch = reader.get_patch(species);
    std::size_t num_patches = patch.num_patches();

    for (int patch_idx = 1; patch_idx <= num_patches; patch_idx++){
        std::pair<int, int> range = patch.get(patch_idx);
        auto input_data = make_species_raw<Dim_momentum, Dim_position>(reader, species, range);


    }

}

/*

/// we make point and check access
   using particle_species_type = decltype(electrons);
   Particle<particle_species_type> particle_3(2, electrons);

   // now, we print all data for third particle

   auto momentum_x = particle::get_momentum_x(particle_3);
   std::cout<<" momentum/x should be 1.3896070749510146E-26  "<<momentum_x<<std::endl;

   auto momentum_y = particle::get_momentum_y(particle_3);
   std::cout<<" momentum/y should be 6.776452331104356E-26  "<<momentum_y<<std::endl;

   auto momentum_z = particle::get_momentum_z(particle_3);
   std::cout<<" momentum/z should be -2.4225675320180624E-26  "<<momentum_z<<std::endl;

   auto position_x = particle::get_position_x(particle_3);
   std::cout<<" position/x should be -9.600055772351497E-6  "<<position_x<<std::endl;

   auto position_y = particle::get_position_y(particle_3);
   std::cout<<" position/y should be -7.99988420951651E-6  "<<position_y<<std::endl;

   auto position_z = particle::get_position_z(particle_3);
   std::cout<<" position/z should be 4.950164701725664E-6  "<<position_z<<std::endl;

   auto weighting = particle::get_weighting(particle_3);
   std::cout<<" weighting should be 396000.00000000006  "<<weighting<<std::endl;

   auto charge = particle::get_charge(particle_3);
   std::cout<<" charge should be 1.602176565E-19;  "<<charge<<std::endl;

   */
