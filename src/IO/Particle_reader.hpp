#pragma once
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include "reduction_library/record/Name.hpp"
#include "reduction_library/component/Name.hpp"



namespace reduction_library{
namespace IO{
using namespace openPMD;

class Particle_reader{
    std::string file_name;
    openPMD::Series& series;

public:
    Particle_reader(std::string file_name, openPMD::Series& series):
        file_name(file_name), series(series){}

    std::vector<std::vector<double>> Read(){
        std::vector<std::size_t> iterations;
        for( auto const& i : series.iterations ){
                iterations.push_back(i.first);
                std::string s = typeid(i.first).name();
        }

        std::cout << '\n';
        for( auto const& i : iterations )
            std::cout<<i<<std::endl;

        Iteration i = series.iterations[iterations[0]];
        for( auto const& ps : i.particles ) {
               cout << "\n\t" << ps.first;
               for( auto const& r : ps.second ) {
                   cout << "\n\t" << r.first;
                   cout << '\n';
               }
           }


    }



   /*     template<Scalar_records_names T_attribute, class T_Value>
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
    */

        std::vector<std::vector<double>> Read_record(std::string record_name){
            std::vector<std::vector<double>> record_values;
            return record_values;
        }
        std::vector<double> Read_component(std::string component_name){

        }

    };
} //IO
} //reduction_library{
