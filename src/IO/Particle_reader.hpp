#pragma once
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>

#include "reduction_library/SOA/Particle_spicies.hpp"

namespace reduction_library{
namespace IO{

using namespace attribute;

    class Particle_reader{
        std::string file_name;
        openPMD::Series& series;

    public:
        Particle_reader(std::string file_name, openPMD::Series& series):
            file_name(file_name), series(series){}

        template<Scalar_records_names T_attribute, class T_Value>
        std::vector<double> Read_attribute(Scalar_records_names attribute, openPMD::ParticleSpecies particle_species){

            std::pair<std::string, std::string> attribute_name = state.at(attribute);
            openPMD::RecordComponent current_record = particle_species[attribute_name.first][attribute_name.second];

            std::shared_ptr<double> values_ptr = current_record.loadChunk<double>();
            series.flush();

            std::vector<std::uint64_t> values_extent = current_record.getExtent();
            int size_of_series = values_extent[0];
            series.flush();

            std::vector<T_Value> record_component_values;
            record_component_values.assign(values_ptr.get(), values_ptr.get() + size_of_series);

            return record_component_values;
        }


        SOA::Particle_spicies Read()
        {

        }

    };
} //IO
} //reduction_library{
