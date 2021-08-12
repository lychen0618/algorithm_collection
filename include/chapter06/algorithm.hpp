#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

namespace chapter06
{
    struct Heap
    {
        /* data */
        std::vector<int>& array;
        size_t heap_size;

        Heap(std::vector<int>& _array) : array(_array), heap_size(_array.size() - 1) {}
    };

    inline size_t get_parent(size_t i){
        return (i - 1) / 2;
    }

    inline size_t left_child(size_t i)
    {
        return 2 * i + 1;
    }

    inline size_t right_child(size_t i)
    {
        return 2 * (i + 1);
    }

    void max_heapify(Heap heap, size_t i)
    {
        size_t larget_index = i;
        size_t left_child_index = left_child(i);
        size_t right_child_index = right_child(i);
        if (left_child_index <= heap.heap_size &&
            heap.array[left_child_index] > heap.array[larget_index])
            larget_index = left_child_index;
        if (right_child_index <= heap.heap_size &&
            heap.array[right_child_index] > heap.array[larget_index])
            larget_index = right_child_index;
        if (larget_index != i)
        {
            std::swap(heap.array[i], heap.array[larget_index]);
            max_heapify(heap, larget_index);
        }
    }

    void build_max_heap(Heap heap)
    {
        for(size_t i = get_parent(heap.heap_size); i >= 0; --i){
            max_heapify(heap, i);
            if(i == 0) break;
        }
    }

    void heap_sort(std::vector<int>& array){
        Heap heap(array);
        build_max_heap(heap);
        for(int i = heap.heap_size; i > 0; --i){
            std::swap(heap.array[0], heap.array[i]);
            heap.heap_size -= 1;
            max_heapify(heap, 0);
        }
    }

    
}