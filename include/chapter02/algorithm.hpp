#pragma once
#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "util.hpp"

namespace chapter02
{
    //这样写不太好
    // void range_insert_sort(std::vector<int> &array, size_t p, size_t r)
    // {
    //     for (size_t index = p + 1; index <= r; ++index)
    //     {
    //         for (size_t pre_index = index; pre_index > p; --pre_index)
    //         {
    //             if (array[pre_index] >= array[pre_index - 1])
    //                 break;
    //             else
    //             {
    //                 std::swap(array[pre_index], array[pre_index - 1]);
    //             }
    //         }
    //     }
    // }

    void range_insert_sort(std::vector<int> &array, size_t p, size_t r)
    {
        for (size_t index = p + 1; index <= r; ++index)
        {
            int temp = array[index];
            for (size_t pre_index = index; pre_index > p; --pre_index)
            {
                if (array[pre_index - 1] <= temp)
                {
                    array[pre_index] = temp;
                    break;
                }
                else
                {
                    array[pre_index] = array[pre_index - 1];
                }
            }
        }
    }

    void basic_insert_sort(std::vector<int> &array)
    {
        range_insert_sort(array, 0, array.size() - 1);
    }

    void merge(std::vector<int> &array, size_t p, size_t q, size_t r)
    {
        std::vector<int> left(array.begin() + p, array.begin() + q + 1);
        left.push_back(INT32_MAX);
        std::vector<int> right(array.begin() + q + 1, array.begin() + r + 1);
        right.push_back(INT32_MAX);
        int l_index = 0, r_index = 0;
        for(; p <= r; ++p){
            if(left[l_index] <= right[r_index]){
                array[p] = left[l_index++];
            }
            else{
                array[p] = right[r_index++];
            }
        }
    }

    void merge_sort_(std::vector<int> &array, size_t p, size_t r)
    {
        if (p == r)
            return;
        size_t q = (r - p) / 2 + p;
        merge_sort_(array, p, q);
        merge_sort_(array, q + 1, r);
        merge(array, p, q, r);
    }

    void merge_sort(std::vector<int> &array)
    {
        merge_sort_(array, 0, array.size() - 1);
    }
}