
#include <iostream>
#include <openPMD/openPMD.hpp>
#include <openPMD/Datatype.hpp>
#include <vector>
#include <memory>
#include <typeinfo>

#include "reduction_library/SOA/Record_getters.hpp"
#include "reduction_library/SOA/Particle.hpp"

#include "reduction_library/record/Name.hpp"
#include "reduction_library/SOA/Component.hpp"

#include "reduction_library/SOA/Dataset.hpp"
#include "reduction_library/SOA/Particle_species.hpp"
#include "reduction_library/SOA/Record.hpp"
#include "IO/Particle_reader.hpp"
#include "IO/Record_names.hpp"
#include "openPMD-api/OpenPMD_reduction.hpp"

#include <alpaka/alpaka.hpp>
#include "reduction_library/thinning/In_kernel_thinning.hpp"
#include "reduction_library/thinning/Thinning_out_kernell.hpp"
#include "reduction_library/thinning/Thinning_alpaka_kernell.hpp"
#include "reduction_library/SOA/Dataset_traits.hpp"
#include "reduction_library/SOA/Component_traits.hpp"
#include "reduction_library/helpers/Type_list.hpp"
#include "reduction_library/SOA/Record_traits.hpp"

#include "reduction_library/SOA/Record_getters.hpp"
#include "reduction_library/SOA/Dataset_traits.hpp"
#include "reduction_library/SOA/Record.hpp"
#include "reduction_library/helpers/Type_list.hpp"
#include <tuple>
#include "../include/reduction_library/thinning/Thinning.hpp"
#include "reduction_library/thinning/Thinning_out_kernell.hpp"
#include "reduction_library/thinning/Random_thinning.hpp"
#include "reduction_library/thinning/Leveling_thinning.hpp"
#include "reduction_library/thinning/Energy_conservative_thinning.hpp"
#include "reduction_library/SOA/Particle_species_traits.hpp"
#include "reduction_library/SOA/Species_make.hpp"


using namespace std;
using std::cout;
using namespace openPMD;
using namespace reduction_library;
using namespace alpaka;

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

/*

void test_all_factrories()
{
    using namespace reduction_library;

    // Finaly, we build complete particle species

    // we set arrays for 3-d momentum
    auto px_values_raw = std::vector<double>{1., 2., 5., 6., 77., 6., 17., 18., 59.};
    auto py_values_raw = std::vector<double>{1., 22., 35., 4., 5., 61., 77., 8., 98.};
    auto pz_values_raw = std::vector<double>{1., 23., 3., 4., 5., 64., 75., 81., 9.};

    // we build 3 components for 3-d momentum
    auto px_component = component::make_component(px_values_raw);
    auto py_component = component::make_component(py_values_raw);
    auto pz_component = component::make_component(pz_values_raw);

    // we build momentum record from 3 components
    auto momentum_record = record::make_record_XYZ(px_component, py_component, pz_component);

    // we set array for 2-d coordinates
    auto x_values_raw = std::vector<double>{2., 46., 38., 1., 116., 14., 20., 15., 14.};
    auto y_values_raw = std::vector<double>{21., 14., 0., 17., 2., 46., 38., 1., 116.};

    // we build 2 components for 2-d coordinates
    auto x_component = component::make_component(x_values_raw);
    auto y_component = component::make_component(y_values_raw);

    // we build position's record from 2 components
    auto position_record = record::make_record_XY(x_component, y_component);

    // we set arrays for weighting
    auto weighting_values_raw = std::vector<double>{15., 20., 28., 16., 30., 29., 123., 120., 8.};

    // we build 1 component for weighting
    auto weighting_component = component::make_component(weighting_values_raw);

    // we build weighting record
    auto weighting_record = record::make_record_scalar(weighting_component);

    // we set arrays for charge
    auto charge_values_raw = std::vector<double>{15., 20., 28., 16., 30., 29., 123., 120., 8.};

    // we build 1 component for charge
    auto charge_component = component::make_component(charge_values_raw);

    // we build charge record
    auto charge_record = record::make_record_scalar(charge_component);

    ////
    /// and, finaly, we build particle species: electrons
    ////

    auto electrons = particle_species::make_species<record::Name::Momentum,
                                                    record::Name::Position,
                                                    record::Name::Weighting,
                                                    record::Name::Charge>
                    (momentum_record, position_record, weighting_record, charge_record);

    /// we make point and check access
    using particle_species_type = decltype(electrons);
    Particle<particle_species_type> particle_3(2, electrons);

    // now, we print all data for third particle

    auto momentum_x = particle_access::get_momentum_x(particle_3);
    std::cout<<" momentum/x should be 5  "<<momentum_x<<std::endl;

    auto momentum_y = particle_access::get_momentum_y(particle_3);
    std::cout<<" momentum/y should be 35  "<<momentum_y<<std::endl;

    auto momentum_z = particle_access::get_momentum_z(particle_3);
    std::cout<<" momentum/z should be 3  "<<momentum_z<<std::endl;

    auto position_x = particle_access::get_position_x(particle_3);
    std::cout<<" position/x should be 38  "<<position_x<<std::endl;

    auto position_y = particle_access::get_position_y(particle_3);
    std::cout<<" position/y should be 0  "<<position_y<<std::endl;

    auto weighting = particle_access::get_weighting(particle_3);
    std::cout<<" weighting should be 28  "<<weighting<<std::endl;

    auto charge = particle_access::get_charge(particle_3);
    std::cout<<" charge should be 28  "<<charge<<std::endl;

    // now, we set new values

    particle_access::set_momentum_x(46., particle_3);
    momentum_x = particle_access::get_momentum_x(particle_3);
    std::cout<<" momentum/x should be 46.  "<<momentum_x<<std::endl;

    particle_access::set_momentum_y(28., particle_3);
    momentum_y = particle_access::get_momentum_y(particle_3);
    std::cout<<" momentum/y should be 28  "<<momentum_y<<std::endl;

    particle_access::set_momentum_z(91., particle_3);
    momentum_z = particle_access::get_momentum_z(particle_3);
    std::cout<<" momentum/z should be 91  "<<momentum_z<<std::endl;

    particle_access::set_position_x(24., particle_3);
    position_x = particle_access::get_position_x(particle_3);
    std::cout<<" position/x should be 24  "<<position_x<<std::endl;

    particle_access::set_position_y(56., particle_3);
    position_y = particle_access::get_position_y(particle_3);
    std::cout<<" position/y should be 56  "<<position_y<<std::endl;

    particle_access::set_weighting(81., particle_3);
    weighting = particle_access::get_weighting(particle_3);
    std::cout<<" weighting should be 81  "<<weighting<<std::endl;

    particle_access::set_charge(64., particle_3);
    charge = particle_access::get_charge(particle_3);
    std::cout<<" charge should be 64  "<<charge<<std::endl;

    std::cout<<"electron size == "<<electrons.get_size()<<std::endl;

}

template<typename T_Value>
auto make_vector_components_from_raw(std::vector<std::vector<T_Value>> raw_data){

    using Dataset_type = typename SOA::Dataset<T_Value>;
    using Components_type = typename SOA::Component<Dataset_type>;

    std::vector<Components_type> components;
    for (std::size_t i = 0; i < raw_data.size(); i++){
        auto component = component::make_component(raw_data[0]);
        components.push_back(component);

    }
    return components;
}

auto make_data_species_from_raw(std::map<std::string, std::vector<std::vector<double>>> data_chunk){

    /*
    auto momentum_raw = data_chunk["momentum"];
    auto momentum_components = make_vector_components_from_raw(momentum_raw);
    /*
    std::shared_ptr<Record> momentum_record;

    if (momentum_components.size() == 3)
        momentum_record = record::make_record_XYZ(momentum_components[0], momentum_components[1], momentum_components[2]);
    else
        momentum_record = record::make_record_XY(momentum_components[0], momentum_components[1]);


    auto position_raw = data_chunk["position"];
    auto position_record = make_vector_components_from_raw(position_raw);

    auto charge_raw = data_chunk["charge"];
    auto charge_record = make_vector_components_from_raw(charge_raw);
    auto weighting_raw = data_chunk["weighting"];
    auto weighting_record = make_record_from_raw(weighting_raw);

    auto electrons = particle_species::make_species<record::Name::Momentum,
                                                        record::Name::Position,
                                                        record::Name::Weighting,
                                                        record::Name::Charge>
                        (momentum_record, position_record, weighting_record, charge_record);

    return 0;

}
*/
void raw_data_reader(){


    Series series = Series(
            "/home/kseniia/Documents/openPMD-example-datasets/example-2d/hdf5/data00000%T.h5",
            Access::READ_ONLY
        );

        // std::map<std::string, std::vector<std::vector<double>>> data_chunk
    std::vector<std::string> record_names = {"charge", "momentum", "position", "weighting"};
/*
    IO::Particle_reader reader(record_names, series);
    for( auto const& i : series.iterations){
        std::size_t num_iteration = i.first;
        Iteration current_iteration = i.second;
        for( auto const& ps : current_iteration.particles) {
            ParticleSpecies species = ps.second;
            std::string name_species = ps.first;
            IO::Particle_patches patch(series, species);
            std::size_t num_patches = patch.num_patches();
            for (int patch_idx = 0; patch_idx < num_patches; patch_idx++){
                auto data_chunk = reader.get_data_chunk(num_iteration, name_species, patch_idx);
            }
        }

    }
    */


    /*
    std::cout<<"start of reduction"<<std::endl;
    std::vector<std::string> records_names = {"charge", "momentum", "position", "weighting"};



    Series series = Series(
                "/home/kseniia/Documents/openPMD-example-datasets/example-3d/hdf5/data00000%T.h5",
                Access::READ_ONLY
            );


    Iteration i = series.iterations[100];
    openPMD::ParticleSpecies electrons = i.particles["electrons"];

    int dimension_momentum = 3;
    int dimension_position = 2;


    IO::Particle_reader reader(records_names, series);
    auto dimensions = reader.get_dimensions(electrons);
    std::cout<<dimensions.first<<"   "<<dimensions.second<<std::endl;
    std::cout<<"dimensions"<<std::endl;
    if (dimensions.first == 3 && dimensions.second == 3)
        process<3, 3>(reader, electrons, records_names);


   // if (dimensions.first == 3 && dimensions.second == 2)
   //     process<3,2>(reader, electrons, records_names);

  //  if (dimensions.first == 2 && dimensions.second == 3)
   //    process<2,3>(reader, electrons, records_names);

  //  if (dimensions.first == 2 && dimensions.second == 2)
   //     process<2,2>(reader, electrons, records_names);
    * *
    */


}


void test_alpaka(){

    using namespace alpaka;

    auto px_values_raw = std::vector<double>{1., 2., 5., 6., 77., 6., 17., 18., 59.};
    auto py_values_raw = std::vector<double>{1., 22., 35., 4., 5., 61., 77., 8., 98.};
    auto pz_values_raw = std::vector<double>{1., 23., 3., 4., 5., 64., 75., 81., 9.};

    auto px_component = component::make_component(px_values_raw);
    auto py_component = component::make_component(py_values_raw);
    auto pz_component = component::make_component(pz_values_raw);

    auto momentum_record = record::make_record_XYZ(px_component, py_component, pz_component);

    auto x_values_raw = std::vector<double>{2., 46., 38., 1., 116., 14., 20., 15., 14.};
    auto y_values_raw = std::vector<double>{21., 14., 0., 17., 2., 46., 38., 1., 116.};

    auto x_component = component::make_component(x_values_raw);
    auto y_component = component::make_component(y_values_raw);

    auto position_record = record::make_record_XY(x_component, y_component);

    auto weighting_values_raw = std::vector<double>{15., 20., 28., 16., 30., 29., 123., 120., 8.};

    auto weighting_component = component::make_component(weighting_values_raw);

    auto weighting_record = record::make_record_scalar(weighting_component);

    auto charge_values_raw = std::vector<double>{15., 20., 28., 16., 30., 29., 123., 120., 8.};

    auto charge_component = component::make_component(charge_values_raw);

    auto charge_record = record::make_record_scalar(charge_component);

     particle_species::make_species<record::name::Charge>(charge_record);


   // using particle_species_type = decltype(electrons);
   // Particle<particle_species_type> particle_3(2, electrons);


  //  using particle_type = Particle<particle_species_type>;
    /*
    using Acc = alpaka::acc::Acc::AccCpuSerial<Dim, Idx>;
    std::cout << "Using alpaka accelerator: " << alpaka::acc::getAccName<Acc>() << std::endl;
    auto const device = pltf::getDevByIdx<Acc>(0u);

    using Queue = alpaka::queue::Queue<Acc, alpaka::queue::Blocking>;
    /*
    auto queue = Queue{device};
    Idx blocksPerGrid = 8;
    Idx threadsPerBlock = 1;
    Idx elementsPerThread = 1;
    using WorkDiv = workdiv::WorkDivMembers<Dim, Idx>;
    auto workDiv = WorkDiv{blocksPerGrid, threadsPerBlock, elementsPerThread};
    */












}


struct Test_random_kernel {

    template<typename Acc>
    ALPAKA_FN_ACC void operator()(Acc const & acc) const
    {

        using namespace alpaka;

        uint32_t threadIdx = idx::getIdx<Grid, Threads>(acc)[0];

        auto distribution = rand::distribution::createNormalReal<double>(acc);
        auto seed = 1;
        auto subsequence = 3;
        auto generator = rand::generator::createDefault(acc, seed, subsequence);
        auto random_value = distribution(generator);

        printf("random_value  %f \n", random_value);

    }
};

double get_random()
{
    double r = ((double) std::rand() / (RAND_MAX)) + 1;
    return r;
}
template<typename Acc>
void initialize_with_random_values(reduction_library::SOA::Alpaka_dataset<Acc, double>& dataset)
{
    for (int i = 0; i < dataset.get_size(); i++){
         dataset[i] = get_random();
     }
}

void test_species_copy()
{
    using namespace SOA;

    using namespace alpaka;

    using Dim = alpaka::dim::DimInt<1>;
    using Idx = std::size_t;
    using Acc = alpaka::acc::AccCpuSerial<Dim, Idx>;
    std::size_t test_size = 10;

    Alpaka_dataset<Acc, double> test_dataset_x(test_size);
    Alpaka_dataset<Acc, double> test_dataset_y(test_size);
    Alpaka_dataset<Acc, double> test_dataset_z(test_size);
    using T_dataset = Alpaka_dataset<Acc, double>;

    initialize_with_random_values<Acc>(test_dataset_x);
    initialize_with_random_values<Acc>(test_dataset_y);
    initialize_with_random_values<Acc>(test_dataset_z);

    Component<T_dataset> component_x(test_dataset_x);
    Component<T_dataset> component_y(test_dataset_y);
    Component<T_dataset> component_z(test_dataset_z);

    Alpaka_dataset<Acc, double> test_dataset_bx(test_size);
    Alpaka_dataset<Acc, double> test_dataset_by(test_size);
    Alpaka_dataset<Acc, double> test_dataset_bz(test_size);

    initialize_with_random_values<Acc>(test_dataset_bx);
    initialize_with_random_values<Acc>(test_dataset_by);
    initialize_with_random_values<Acc>(test_dataset_bz);

    Component<T_dataset> component_bx(test_dataset_bx);
    Component<T_dataset> component_by(test_dataset_by);
    Component<T_dataset> component_bz(test_dataset_bz);

    Alpaka_dataset<Acc, double> charge_dataset(test_size);
    initialize_with_random_values<Acc>(charge_dataset);
    Component<T_dataset> component_charge(charge_dataset);

    Alpaka_dataset<Acc, double> weighting_dataset(test_size);
    initialize_with_random_values<Acc>(weighting_dataset);
    Component<T_dataset> component_weighting(weighting_dataset);


    auto weighting_record = record::make_record_scalar(component_weighting);
    auto coords = record::make_record_XYZ(component_x, component_y, component_z);
    auto momentums = record::make_record_XYZ(component_bx, component_by, component_bz);

    auto charge = record::make_record_scalar(component_charge);

    auto electrons = particle_species::make_species<record::name::Momentum,
                                                       record::name::Position,
                                                       record::name::Weighting,
                                                       record::name::Charge>
                       (momentums, coords, weighting_record, charge);

    using Acc_new = acc::AccCpuThreads<Dim, Idx>;
    using Old_dataset_type = Alpaka_dataset<Acc, double>;
    using Dataset_new_acc = dataset::traits::Acc_dataset_t<Acc_new, Old_dataset_type>;
    Dataset_new_acc new_dataset(test_dataset_x);
  //  std::cout<<"first type == "<<typeid(test_dataset_x).name()<<std::endl;
  //  std::cout<<"second type == "<<typeid(new_dataset).name()<<std::endl;

    using Old_component_type = Component<T_dataset>;
    using Component_new_acc = component::traits::Acc_component_t<Acc_new, Old_component_type>;

    Component_new_acc new_component(component_x);
  //  std::cout<<"first type == "<<typeid(component_x).name()<<std::endl;
//    std::cout<<"second type == "<<typeid(new_component).name()<<std::endl;
    using T_Names_List = helpers::Type_list<component::name::SCALAR>;

    using Old_component_type = Component<T_dataset>;
    using T_Components_Types_List = helpers::Type_list<Old_component_type>;

    using Old_Record_type = SOA::Record<T_Names_List, T_Components_Types_List>;
    using Record_new_acc = record::traits::Acc_record_t<Acc_new, Old_Record_type>;

    T_Components_Types_List old_type_list(component_x);
    Old_Record_type::Components old_components(old_type_list);
    Record_new_acc::Components new_components(old_type_list);
  //  std::cout<<"second type == "<<typeid(new_components).name()<<std::endl;

    Record_new_acc new_record(weighting_record);

  //  std::cout<<"first type == "<<typeid(coords).name()<<std::endl;
 //   std::cout<<"second type == "<<typeid(new_record).name()<<std::endl;
    //reduction_library::particle_species::make_species_different_acc<Acc>(particles_device);
    auto electrons_diff_acc = reduction_library::particle_species::make_species_different_acc<Acc_new>(electrons);
 //   std::cout<<std::endl<<std::endl;
  //  std::cout<<"first type == "<<typeid(electrons_diff_acc).name()<<std::endl;
  //  std::cout<<"second type == "<<typeid(electrons).name()<<std::endl;
 /*   std::cout<<std::endl<<std::endl;
    for (int i = 0; i < electrons.get_size(); i++)
    {
        auto particle = electrons.get_particle(i);
        auto weighting = particle_access::get_weighting(particle);
        std::cout<<" weighting[i] == "<<weighting<<"  ";
    }
    std::cout<<"SIZE "<<electrons.get_size()<<std::endl;

    double ratio_deleted_particles = 0.5;
    using T_Particle_Species = decltype(electrons);

    std::cout<<"Test random out of kernel<"<<std::endl;

    thinning::Thinning_out_kernell<Acc, T_Particle_Species, thinning::Random_thinning> test_random;
    test_random.init(ratio_deleted_particles);
    test_random(electrons, 5);
    std::cout<<std::endl<<std::endl;


    //Test_random_kernel helloWorldKernel;

     //  auto taskRunKernel = kernel::createTaskKernel<Acc>(workDiv, helloWorldKernel);


       //queue::enqueue(queue, taskRunKernel);


   //    alpaka::wait::wait(queue);


 // * */


}



int main(){
    test_species_copy();
    /*
	test_all_factrories();
	using namespace reduction_library;
	using namespace alpaka;

    using Dim = alpaka::dim::DimInt<1>;
    using Idx = uint32_t;

	using Acc = acc::AccCpuSerial<Dim, Idx>;
	using Acc_new = acc::AccCpuThreads<Dim, Idx>;
	std::cout<<typeid(int).name();



    using tuple_type = typename std::tuple< double*, double*>;
    using result_type = typename helpers::apply_meta<std::decay_t, tuple_type>;
    result_type result;
    std::cout<<"result name "<<std::endl;
    std::cout<<typeid(result).name();

    test_species_copy();





	/*using old_dataset = typename SOA::Dataset<double>;
	using alpaka_dataset = typename SOA::Aplaka_dataset<Acc, double>;
	using old_non_alpaka = SOA::Acc_dataset_t< Acc, old_dataset>;
	auto px_values_raw = std::vector<double>{1., 2., 5., 6., 77., 6., 17., 18., 59.};
	old_dataset test(px_values_raw);
	alpaka_dataset(8);

	std::cout << typeid(old_non_alpaka).name() << '\n';
	using old_alpaka = SOA::Acc_dataset_t<alpaka_dataset, Acc>;
	std::cout << typeid(old_alpaka).name() << '\n';
	using new_alpaka = SOA::Acc_dataset_t<alpaka_dataset, Acc_new>;
	std::cout << typeid(new_alpaka).name() << '\n';
*/


   /* using namespace alpaka;

    using Dim = alpaka::dim::DimInt<1>;
    using Idx = uint32_t;


    using Acc = acc::AccCpuSerial<Dim, Idx>;


    auto const device = pltf::getDevByIdx<Acc>(0u);

    using Queue = alpaka::queue::Queue<Acc, alpaka::queue::Blocking>;
    auto queue = Queue{device};

    Idx blocksPerGrid = 8;
    Idx threadsPerBlock = 1;
    Idx elementsPerThread = 1;
    using WorkDiv = workdiv::WorkDivMembers<Dim, Idx>;
    auto workDiv = WorkDiv{blocksPerGrid, threadsPerBlock, elementsPerThread};


    Test_random_kernel helloWorldKernel;

    auto taskRunKernel = kernel::createTaskKernel<Acc>(workDiv, helloWorldKernel);


    alpaka::queue::enqueue(queue, taskRunKernel);


    alpaka::wait::wait(queue);
*/

    return 0;
}




