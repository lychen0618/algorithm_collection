#pragma once
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "util.hpp"

namespace chapter07
{
    int partition(std::vector<int> &array, size_t p, size_t r, bool &is_random)
    {
        if (is_random)
        {
            int random_chose_pivot_index = util::randint(p, r);
            std::swap(array[random_chose_pivot_index], array[r]);
        }
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

    void basic_quick_sort_helper(std::vector<int> &array_copy, int p, int r, bool &is_random)
    {
        if (p < r)
        {
            int q = partition(array_copy, p, r, is_random);
            basic_quick_sort_helper(array_copy, p, q - 1, is_random);
            basic_quick_sort_helper(array_copy, q + 1, r, is_random);
        }
    }

    void basic_quick_sort(std::vector<int> &array_copy)
    {
        bool is_random = false;
        basic_quick_sort_helper(array_copy, 0, array_copy.size() - 1, is_random);
    }

    void random_quick_sort(std::vector<int> &array_copy){
        bool is_random = true;
        basic_quick_sort_helper(array_copy, 0, array_copy.size() - 1, is_random);
    }
}