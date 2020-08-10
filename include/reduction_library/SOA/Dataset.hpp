#pragma once

#include <vector>

namespace reduction_library{
namespace SOA{

template<typename T_Dataset>
struct Dataset{
private:
    std::vector<T_Dataset> values;
public:
    Dataset(){}
    Dataset(std::vector<T_Dataset> values):
        values(values){}

    std::vector<T_Dataset> get_values(){
        return values;
    }
};

}  // namespace SOA
} // namespace reduction_library
