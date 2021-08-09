#pragma once
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "util.hpp"

namespace chapter02
{
    void range_insert_sort(std::vector<int> &array, size_t p, size_t r)
    {
        for (size_t index = p + 1; index <= r; ++index)
        {
            for (size_t pre_index = index; pre_index > p; --pre_index)
            {
                if (array[pre_index] >= array[pre_index - 1])
                    break;
                else
                {
                    std::swap(array[pre_index], array[pre_index - 1]);
                }
            }
        }
    }

    void basic_insert_sort(std::vector<int> &array){
        range_insert_sort(array, 0, array.size() - 1);
    }
}