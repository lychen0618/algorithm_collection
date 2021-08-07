#pragma once
#include <vector>
#include <assert.h>
#include <iostream>

namespace chapter09
{
    void get_max_and_min(std::vector<int> array, int *max_value, int *min_value)
    {
        assert(max_value != nullptr && min_value != nullptr);
        if (array.size() == 0)
        {
            std::cout << "array size is 0" << std::endl;
            return;
        }
        std::vector<int>::size_type start_index = 0;
        *max_value = INT32_MIN;
        *min_value = INT32_MAX;
        if (array.size() % 2)
        {
            *max_value = array[0];
            *min_value = array[0];
            start_index = 1;
        }
        for(; start_index < array.size(); start_index += 2){
            if(array[start_index] < array[start_index + 1]){
                *max_value = std::max(*max_value, array[start_index + 1]);
                *min_value = std::min(*min_value, array[start_index]);
            }
            else{
                *max_value = std::max(*max_value, array[start_index]);
                *min_value = std::min(*min_value, array[start_index + 1]);
            }
        }
    }
}