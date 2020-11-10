#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <iostream>
#include "math.h"
#include <vector>

namespace reduction_library{
namespace thinning{

class Getting_n_inc_weighted_sample{
private:
    double get_random()
    {
        return((double) std::rand() / (RAND_MAX));
    }

    std::vector<int> get_wrs(const std::vector<int>& values, const std::vector<double>& weights, int size)
    {
        std::vector<double> max_values;
        for (int i = 0; i < values.size(); i++)
        {
            double random = get_random();
            double current_probability = pow(random, 1./weights[i]);
            max_values.push_back(current_probability);
        }

        std::vector<int> result = find_n_max_elements(max_values, size);
        return result;
    }

    std::vector<int> find_n_max_elements(const std::vector<double>& values, int n)
    {
        std::priority_queue<std::pair<double, int>, std::vector< std::pair<double, int>>, std::greater <std::pair<double, int>>> q;
        for (int i = 0; i < values.size(); ++i)
        {
            if(q.size() < n)
                q.push(std::pair<double, int>(values[i], i));
            else if(q.top().first < values[i])
            {
                q.pop();
                q.push(std::pair<double, int>(values[i], i));
            }
        }
        n = q.size();
        std::vector<int> res(n);
        for (int i = 0; i < n; ++i)
        {
            res[n - i - 1] = q.top().second;
            q.pop();
        }
        return res;
    }

public:
    std::vector<std::size_t> operator()(const std::vector<int>& values, const std::vector<double>& weights, int sample_size)
    {
        std::vector<std::size_t> num_inc(values.size(), 0);
        for (int i = 0; i < sample_size; i++)
        {
            std::vector<int> num_inc_one_iteration = get_wrs(values, weights, sample_size);
            for (int i = 0; i < num_inc_one_iteration.size(); i++)
            {
                num_inc[num_inc_one_iteration[i]]++;
            }
        }
        return num_inc;

    }
};

}
}
