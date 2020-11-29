/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <alpaka/alpaka.hpp>

namespace reduction_library{
namespace SOA{
/** Base structure for Dataset type with given alpaka accelerator
 *
 *  represent set of values with type T_Value, alpaka accelerator Acc
 *  allows setting and getting values
 *
 */
template<typename Acc, typename T_Value>
struct Alpaka_dataset{
public:
    using Dim = alpaka::dim::DimInt<1u>;
    using Idx = std::size_t;
    using BufAcc = alpaka::mem::buf::Buf<Acc, T_Value, Dim, Idx>;
    using Value_type = T_Value;
private:
    BufAcc* buffer;
    Value_type* data;
    std::size_t size;
public:
    Alpaka_dataset(){}
    Alpaka_dataset(const Alpaka_dataset& dataset)
    {
        size = dataset.get_size();
        auto const devAcc = alpaka::pltf::getDevByIdx<Acc>(0u);
        buffer = dataset.get_buffer();
        data = dataset.start();
   }

    template<typename Acc_new>
    Alpaka_dataset(const Alpaka_dataset<Acc_new, T_Value>& dataset)
    {
        size = dataset.get_size();
        auto const devAcc = alpaka::pltf::getDevByIdx<Acc>(0u);
        buffer = new BufAcc(alpaka::mem::buf::alloc<T_Value, Idx>(devAcc, size));
        data = alpaka::mem::view::getPtrNative(*buffer);

        using QueueProperty = alpaka::queue::Blocking;
            using QueueAcc = alpaka::queue::Queue<
                Acc,
                QueueProperty
            >;
        QueueAcc queue { devAcc };
        alpaka::mem::view::copy(queue, *buffer, *dataset.get_buffer(), size);
    }

    Alpaka_dataset(std::size_t size)
    {
        this->size = size;
        auto const devAcc = alpaka::pltf::getDevByIdx<Acc>(0u);
        buffer = new BufAcc(alpaka::mem::buf::alloc<T_Value, Idx>(devAcc, size));
        data = alpaka::mem::view::getPtrNative(*buffer);
    }

    void deep_copy(const Alpaka_dataset& dataset)
    {
      //  new BufAcc(alpaka::mem::buf::alloc<T_Value, Idx>(Acc, size));
            // data = //alpaka::mem::view::getPtrNative(*buffer);

            // using QueueProperty = alpaka::queue::Blocking;
             //    using QueueAcc = alpaka::queue::Queue<
              //       Acc,
               //      QueueProperty
               //  >;
             //QueueAcc queue { devAcc };
             //alpaka::mem::view::copy(queue, *buffer, *dataset.get_buffer(), size);

    }


    ALPAKA_FN_HOST_ACC BufAcc* get_buffer() const
    {
        return buffer;
    }

    ALPAKA_FN_HOST_ACC Value_type* get_values()
    {
        return data;
    }

    ALPAKA_FN_HOST_ACC std::size_t get_size() const
    {
    	return size;
    }
    ALPAKA_FN_HOST_ACC Value_type* start() const
    {
    	return data;
    }

    ALPAKA_FN_HOST_ACC Value_type& operator[](std::size_t idx)
    {
    	return *(data + idx);
    }
    ALPAKA_FN_HOST_ACC void set_value(Value_type value, int idx)
    {
        data[idx] = value;
    }

};

template<typename Acc, typename T_Value>
ALPAKA_FN_HOST_ACC void initialize_values(Alpaka_dataset<Acc, T_Value>& dataset, std::vector<T_Value> input){

    for (int i = 0; i < dataset.get_size(); i++ ){
        dataset[i] = input[i];
    }
}

template<typename Acc, typename T_Value>
void print(Alpaka_dataset<Acc, T_Value>& dataset){
    for (int i = 0; i < dataset.get_size(); i++ ){
        std::cout<<dataset[i]<<"  ";

    }
}

}  // namespace SOA
} // namespace reduction_library
