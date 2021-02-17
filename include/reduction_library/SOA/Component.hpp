/* Copyright 2020 Kseniia Bastrakova, Sergei Bastrakov
 *
 * This file is part of reduction library.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "reduction_library/component/Utility.hpp"
#include "reduction_library/component/Concept.hpp"
#include "reduction_library/component/Name.hpp"
#include "reduction_library/SOA/Dataset.hpp"
#include "reduction_library/particle_species/Interfaces.hpp"
#include <vector>
#include <iostream>

namespace reduction_library{
namespace SOA{

/** @file
 *
 * Implementation Component concept (reduction_library/component/Concept.hpp)
 * for "SOA" data representation
 *
 * define all necessary functions and trait: getting Unit_SI, setting Unit_SI
 * getting type of values
 * Parameterized by "T_Dataset" type, which contains array storage with Alpaka Accelerator
 *
 */

/** Base structure for Component type
 *
 *  represent Component concept for structure of arrays data storage
 *  allows accessing to data and attributes
 *
 */
    template<typename T_Dataset>
    struct Component{
    private:
        T_Dataset dataset;
        double unit_SI;

    public:
        //-----------------------------------------------------------------------------
        //! Type of particle storage. We assume, that it's array with Alpaka accelerator
        using Dataset_type = T_Dataset;
        Component(){}

        Component(const Component& component):
            dataset(component.get_dataset()),
            unit_SI(component.get_unit_SI()){}

        template<typename T_Another_Dataset>
        Component(const Component<T_Another_Dataset>& component):
            dataset(component.get_dataset()),
            unit_SI(component.get_unit_SI()){}

        Component(T_Dataset dataset):
                unit_SI(42.),
                dataset(dataset){}

        //-----------------------------------------------------------------------------
        //! Returns link to one element in storage with index idx
        auto& operator[](int idx)
        {
            return dataset[idx];
        }

        //-----------------------------------------------------------------------------
        //! Returns a conversation factor to multiply data with to be represented in SI
        double get_unit_SI() const
        {
            return unit_SI;
        }

        //-----------------------------------------------------------------------------
        //! Set a conversation factor to multiply data with to be represented in SI
        void set_unit_SI(double new_unit_SI)
        {
            unit_SI = new_unit_SI;
        }

        //-----------------------------------------------------------------------------
        //! Access to storage to change elements
        T_Dataset& set_dataset()
        {
            return dataset;
        }

        //-----------------------------------------------------------------------------
        //! Access to storage to read-only elements
        const T_Dataset& get_dataset() const
        {
            return dataset;
        }

        //-----------------------------------------------------------------------------
        //! Returns size of storage
        ALPAKA_FN_HOST_ACC std::size_t get_size()
        {
            return dataset.get_size();
        }

    };

}//SOA


namespace component{
namespace traits{
    template<typename T_Dataset>
    struct Value_type<SOA::Component<T_Dataset>>
    {
        using type = T_Dataset;

    };
}
    // TODO: Add make alpaka dataset
    template<typename T_Value>
    auto make_component(std::vector<T_Value> values)
    {
        using Double_dataset_type = typename SOA::Dataset<double>;
        auto dataset = SOA::Dataset<double>(values);
        auto component = SOA::Component<Double_dataset_type>(dataset);
        return component;
    }

    /** Partal specialization components interface Getting_unit_SI for SOA::Component
     *
     *  return unit_SI attribute for component implementation
     *
     * \tparam T_Dataset type of components's  data storage
     * \tparam component -- component's concept SOA implementation
     */
    template<typename T_Dataset>
    struct Getting_unit_SI<SOA::Component<T_Dataset>>
    {
    public:
        double operator() (SOA::Component<T_Dataset>& component)
        {
             return component.get_unit_SI();
        }

    };

    /** Partal specialization components interface Setting_unit_SI for SOA::Component
     *
     *  set unit_SI attribute for component implementation
     *
     * \tparam T_Dataset type of components's  data storage
     * \tparam component -- component's concept SOA implementation
     * \tparam unit_si -- new conversation factor to multiply data with to be represented in SI
     */
    template<typename T_Dataset>
    struct Setting_unit_SI<SOA::Component<T_Dataset>>
    {
    public:
        void operator() (SOA::Component<T_Dataset>& component, double unit_si)
        {
            component.set_unit_SI(unit_si);
        }

    };

}// namespace component
}// namespace reduction_library

