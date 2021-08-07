#pragma once
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>

namespace chapter07
{
    int partition(std::vector<int> &array, size_t p, size_t r)
    {
        int pivot_value = array[r];
        size_t i = p - 1;
        for (size_t j = p; j < r; ++j)
        {
            if (array[j] <= pivot_value)
            {
                i++;
                std::swap(array[i], array[j]);
            }
        }
        i++;
        std::swap(array[i], array[r]);
        return i;
    }

    void basic_quick_sort_helper(std::vector<int> &array_copy, int p, int r)
    {
        if (p < r)
        {
            int q = partition(array_copy, p, r);
            basic_quick_sort_helper(array_copy, p, q - 1);
            basic_quick_sort_helper(array_copy, q + 1, r);
        }
    }

    void basic_quick_sort(std::vector<int> &array_copy)
    {
        basic_quick_sort_helper(array_copy, 0, array_copy.size() - 1);
    }
}