#pragma once

#include "reduction_library/SOA/Record3d.hpp"
#include "reduction_library/record/Name.hpp"


namespace reduction_library{
namespace SOA{

    using Momentums = SOA::Record_3d<record::Name::momentum>;
 //   using Weights = attribute::Record_component<attribute::Scalar_records_names::weighting, double>;


   // class Particle_spicies_old: public Momentums, public Weights {
    //    int size;
     //   public:
      //  using MyParticle = Particle<Particle_spicies_old>;
      //  Particle_spicies_old(std::vector<double>& weights,
       //          std::vector<double>& momentum):
       //              Momentums(momentum), Weights(weights), size(weights.size()){}

    //    MyParticle getParticle(int idx){

     //       return MyParticle(idx, *this);
      //  }
      //  int getSize(){
        //    return size;
       // }

   // };

} // SOA
} // reduction_library
