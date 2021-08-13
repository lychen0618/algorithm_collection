#ifndef CHAPTER09_ALGORITHM_H__
#define CHAPTER09_ALGORITHM_H__
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include "chapter07/algorithm.hpp"
#include "chapter02/algorithm.hpp"

namespace chapter09
{
    void get_max_and_min(std::vector<int> &array, int *max_value, int *min_value)
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
        for (; start_index < array.size(); start_index += 2)
        {
            if (array[start_index] < array[start_index + 1])
            {
                *max_value = std::max(*max_value, array[start_index + 1]);
                *min_value = std::min(*min_value, array[start_index]);
            }
            else
            {
                *max_value = std::max(*max_value, array[start_index]);
                *min_value = std::min(*min_value, array[start_index + 1]);
            }
        }
    }

    int _expect_linear_time_select(std::vector<int> &array, size_t p, size_t r, size_t i)
    {
        if (p == r)
            return array[p];
        size_t q = chapter07::partition(array, p, r, true);
        if (q == i)
            return array[q];
        else if (q < i)
            return _expect_linear_time_select(array, q + 1, r, i);
        else
            return _expect_linear_time_select(array, p, q - 1, i);
    }

    int expect_linear_time_select(std::vector<int> &array, size_t i)
    {
        assert(i <= array.size());
        return _expect_linear_time_select(array, 0, array.size() - 1, i - 1);
    }

    int find_median(std::vector<int> &array, size_t p, size_t r)
    {
        std::vector<int> median_array;
        size_t index = p;
        for (; index <= r; index += 5)
        {
            int l_most = std::min(index + 4, r);
            chapter02::range_insert_sort(array, index, l_most);
            median_array.push_back(array[(l_most + index) / 2]);
        }
        if (r - p < 5)
            return median_array[0];
        else
        {
            return find_median(median_array, 0, median_array.size() - 1);
        }
    }

    int _worst_linear_time_select(std::vector<int> &array, size_t p, size_t r, size_t i)
    {
        int median_value = find_median(array, p, r);

        //find median_value position and swap
        for (size_t index = p; index <= r; ++index)
        {
            if (array[index] == median_value)
            {
                std::swap(array[index], array[r]);
                break;
            }
        }

        size_t q = chapter07::partition(array, p, r, false);
        if (q == i)
            return array[q];
        else if (q < i)
            return _worst_linear_time_select(array, q + 1, r, i);
        else
            return _worst_linear_time_select(array, p, q - 1, i);
    }

    int worst_linear_time_select(std::vector<int> array, size_t i)
    {
        assert(i <= array.size());
        return _worst_linear_time_select(array, 0, array.size(), i - 1);
    }
}

#endif /* CHAPTER09_ALGORITHM_H__ */