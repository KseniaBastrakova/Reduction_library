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
#include <queue>
#include <iostream>
#include "math.h"
#include <vector>

namespace reduction_library{
namespace thinning{

    /** @file
     *
     * Selection random values with probability proportional
     * to their weight, reiteration that sample_size times,
     * and counting number of times, that each value was selected
     *
     */

    /** Getting random sample from a weighted set with repetition
     *
     * Return vector with number of times, that each value was selected
     *
     *
     */
    template<typename T_Random_Generator, typename T_Value>
    class Getting_n_inc_weighted_sample{
    private:
        /** Getting random sample from a weighted set
         *
         * Return random sample with ordered indices of elements from input weights
         *
         * \tparam T_Random_Generator type of input random values generator
         * \tparam T_Value type of input weights array
         * \tparam weights weights of random sample
         * \tparam sample_size number of selection reiteration
         * \tparam generator random values generator functor, that returns random value
         *
         */
        std::vector<int> get_weighted_random_sample(const std::vector<T_Value>& weights, int sample_size, T_Random_Generator& generator)
        {
            std::vector<double> max_values;
            for (int i = 0; i < weights.size(); i++)
            {
                double random = generator();
                double current_probability = pow(random, 1./weights[i]);
                max_values.push_back(current_probability);
            }

            std::vector<int> result = find_n_max_elements(max_values, 1.);
            return result;
        }

        /** Getting n max elements from input array
         *
         * Return array of indexes max elements
         *
         * \tparam T_Value type of input array
         * \tparam values to find max elements
         * \tparam num_max_elements number of max elements to be found
         *
         */
        std::vector<int> find_n_max_elements(const std::vector<T_Value>& values, int num_max_elements)
        {
            std::priority_queue<std::pair<double, int>, std::vector< std::pair<T_Value, int>>, std::greater <std::pair<T_Value, int>>> max_elements_idxes;
            for (int i = 0; i < values.size(); ++i)
            {
                if(max_elements_idxes.size() < num_max_elements)
                    max_elements_idxes.push(std::pair<double, int>(values[i], i));
                else if(max_elements_idxes.top().first < values[i])
                {
                    max_elements_idxes.pop();
                    max_elements_idxes.push(std::pair<double, int>(values[i], i));
                }
            }

            num_max_elements = max_elements_idxes.size();
            std::vector<int> res(num_max_elements);
            for (int i = 0; i < num_max_elements; ++i)
            {
                res[num_max_elements - i - 1] = max_elements_idxes.top().second;
                max_elements_idxes.pop();
            }
            return res;
        }

    public:
        /** Getting random sample from a weighted set with repetition
           *
           * Return vector with number of times, that each value was selected
           * \tparam T_Random_Generator type of input random values generator
           * \tparam T_Value type of input weights array
           * \tparam weights weights of random sample
           * \tparam sample_size number of selection reiteration
           * \tparam generator random values generator functor, that returns random value

           */
        std::vector<double> operator()(const std::vector<double>& weights, int sample_size, T_Random_Generator& generator)
        {
            std::vector<double> number_of_includes(weights.size(), 0);
            for (int i = 0; i < sample_size; i++)
            {
                std::vector<int> num_inc_one_iteration = get_weighted_random_sample(weights, sample_size, generator);
                for (int i = 0; i < num_inc_one_iteration.size(); i++)
                {
                    number_of_includes[num_inc_one_iteration[i]]++;
                }
            }
            return number_of_includes;
        }
    };

} // namespace thinning
} // namespace reduction_library
