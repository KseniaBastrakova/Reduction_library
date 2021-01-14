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

/** @file
 * implementation value storage for SOA component
 * provide host/device storage (depends on accelerator type)
 * with array based replacement in memory
 * more about accelerator types and how to use this, you can find
 * https://alpaka.readthedocs.io/en/latest/basic/abstraction.html
 *
 */
/** Base structure for storage for SOA component
 * \tparam T_Acc alpaka accelerator type (AccGpuCudaRt, AccCpuOmp2Blocks,AccCpuOmp2Threads, etc)
 * \tparam T_Acc type of values in storage (int, double, float, etc.)
 * provide access to values, data reading, writing, getting size of storage
 * IMPORTANT: we assume, that in copy constructor we create a soft sopy of data
 * but when we create storage with different accelerator, we make a deep copy
 *
 */
template<typename Acc, typename T_Value>
struct Alpaka_dataset{
public:
    //-----------------------------------------------------------------------------
    //! Define dimensionality to be used in kernels
    using Dim = alpaka::dim::DimInt<1u>;
    //-----------------------------------------------------------------------------
    //! Define type of indices to be used in kernels
    using Idx = std::size_t;
    //-----------------------------------------------------------------------------
    //! Define type of 1-dimensional buffer of current accelerator and current value type
    using Buf_acc = alpaka::mem::buf::Buf<Acc, T_Value, Dim, Idx>;
    using Value_type = T_Value;
private:
    //-----------------------------------------------------------------------------
    //! Pointer to buffer
    Buf_acc* buffer;
    //-----------------------------------------------------------------------------
    //! Pointer to raw data
    Value_type* data;
    std::size_t size;
public:
    Alpaka_dataset(){}

    /** Copy constructor, that makes soft copy of input data */
    Alpaka_dataset(const Alpaka_dataset& dataset)
    {
        size = dataset.get_size();
        auto const devAcc = alpaka::pltf::getDevByIdx<Acc>(0u);
        buffer = dataset.get_buffer();
        data = dataset.start();
    }
    /** Construction dataset with new accelerator from dataset with old
     *  accelerator
     *  Makes deep copy of values, using new accelerator
     *  T_Value should be same
     */
    template<typename Acc_Old>
    Alpaka_dataset(const Alpaka_dataset<Acc_Old, T_Value>& dataset)
    {
        size = dataset.get_size();
        auto const devAcc = alpaka::pltf::getDevByIdx<Acc>(0u);
        buffer = new Buf_acc(alpaka::mem::buf::alloc<T_Value, Idx>(devAcc, size));
        data = alpaka::mem::view::getPtrNative(*buffer);

        using QueueProperty = alpaka::queue::Blocking;
            using QueueAcc = alpaka::queue::Queue<
                Acc,
                QueueProperty
            >;
        QueueAcc queue { devAcc };
        alpaka::mem::view::copy(queue, *buffer, *dataset.get_buffer(), size);
    }

    /** Construction empty dataset with given size
     *  and base accelerator
     */
    Alpaka_dataset(std::size_t size)
    {
        this->size = size;
        auto const devAcc = alpaka::pltf::getDevByIdx<Acc>(0u);
        buffer = new Buf_acc(alpaka::mem::buf::alloc<T_Value, Idx>(devAcc, size));
        data = alpaka::mem::view::getPtrNative(*buffer);
    }

    /** Copy constructor, that makes deep copy of input data */
    template<typename Acc_New>
    void deep_copy(const Alpaka_dataset& dataset)
    {
        auto const devAcc = alpaka::pltf::getDevByIdx<Acc_New>(0u);
        new Buf_acc(alpaka::mem::buf::alloc<T_Value, Idx>(devAcc, size));
        data = alpaka::mem::view::getPtrNative(*buffer);

        using QueueProperty = alpaka::queue::Blocking;
                   using QueueAcc = alpaka::queue::Queue<
                           Acc_New,
                       QueueProperty
                   >;
        QueueAcc queue { devAcc };
        alpaka::mem::view::copy(queue, *buffer, *dataset.get_buffer(), size);
    }

    //-----------------------------------------------------------------------------
    //! Returns pointer to Alpaka buffer. Host/device function
    ALPAKA_FN_HOST_ACC Buf_acc* get_buffer() const
    {
        return buffer;
    }

    //-----------------------------------------------------------------------------
    //! Returns pointer to raw data. Host/device function
    ALPAKA_FN_HOST_ACC Value_type* get_values()
    {
        return data;
    }

    //-----------------------------------------------------------------------------
    //! Returns size of storage. Host/device function
    ALPAKA_FN_HOST_ACC std::size_t get_size() const
    {
    	return size;
    }

    //-----------------------------------------------------------------------------
    //! Returns pointer to beginning of storage. Host/device function
    ALPAKA_FN_HOST_ACC Value_type* start() const
    {
    	return data;
    }

    //-----------------------------------------------------------------------------
    //! Returns link to element in storage with index idx. Host/device function
    ALPAKA_FN_HOST_ACC Value_type& operator[](std::size_t idx)
    {
    	return *(data + idx);
    }

    //-----------------------------------------------------------------------------
    //! Set element in storage with index idx by value with value type. Host/device function
    ALPAKA_FN_HOST_ACC void set_value(Value_type value, int idx)
    {
        data[idx] = value;
    }

};
 /// Using for test
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
