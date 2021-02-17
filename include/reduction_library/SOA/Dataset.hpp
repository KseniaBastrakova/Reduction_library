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

namespace reduction_library{
namespace SOA{

/** Base structure for Dataset type
 *
 *  represent set of values with type T_Value,
 *  allows setting and getting values
 *
 */
template<typename T_Value>
struct Dataset{
public:
    using Value_type = T_Value;
private:
    std::vector<Value_type> values;
public:
    Dataset(){}
    Dataset(const Dataset<T_Value>& dataset):
        values(dataset.get_values()){}

    auto operator=(const Dataset<T_Value>& dataset)
    {
        values = dataset.get_values();
        return *this;
    }

    Dataset(std::vector<Value_type> values):
        values(values){}
    //-----------------------------------------------------------------------------
    //! Get copy of values
    std::vector<Value_type> get_values() const
    {
        return values;
    }
    //-----------------------------------------------------------------------------
    //! Set values
    void set_values(const std::vector<Value_type>& new_values)
    {
        values = new_values;
    }

    Value_type& operator[](int idx)
    {
        return values[idx];
    }
    void set_value(Value_type value, int idx)
    {
        values[idx] = value;
    }
    //-----------------------------------------------------------------------------
    //! Get size of dataset
    ALPAKA_FN_HOST_ACC std::size_t get_size()
    {
    	return values.size();

    }
};

}  // namespace SOA
} // namespace reduction_library
