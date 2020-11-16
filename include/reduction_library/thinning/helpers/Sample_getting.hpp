#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <iostream>
#include "math.h"
#include <vector>

namespace reduction_library{
namespace thinning{

template<typename T_Random_Generator, typename T_Value>
class Getting_n_inc_weighted_sample{
private:
    std::vector<int> get_wrs(const std::vector<T_Value>& weights, int sample_size, T_Random_Generator& generator)
    {
        std::vector<double> max_values;
        for (int i = 0; i < weights.size(); i++)
        {
            double random = generator();
            double current_probability = pow(random, 1./weights[i]);
            max_values.push_back(current_probability);
        }

        std::vector<int> result = find_n_max_elements(max_values, sample_size);
        return result;
    }

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
    std::vector<double> operator()(const std::vector<double>& weights, int sample_size, T_Random_Generator& generator)
    {
        std::vector<double> number_of_includes(weights.size(), 0);
        for (int i = 0; i < sample_size; i++)
        {
            std::vector<int> num_inc_one_iteration = get_wrs(weights, sample_size, generator);
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
