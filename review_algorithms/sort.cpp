#include "sort.h"
#include "heap.h"
#include <functional>
#include <algorithm>

// 小的元素不断浮出水面
void bubble_sort(std::vector<int> &array)
{
    int n = array.size();
    if (n < 2)
        return;
    bool flag;
    for (int i = 0; i < n - 1; ++i)
    {
        flag = false;
        for (int j = n - 1; j > i; --j)
        {
            if (array[j] < array[j - 1])
            {
                std::swap(array[j], array[j - 1]);
                flag = true;
            }
        }
        if (!flag)
            break;
    }
}

// 每次循环，选择一个最小的放到前面
void select_sort(std::vector<int> &array)
{
    int n = array.size();
    if (n < 2)
        return;
    for (int i = 0; i < n - 1; ++i)
    {
        int index = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (array[j] < array[index])
                index = j;
        }
        std::swap(array[i], array[index]);
    }
}

// 把元素不断插入已排好序列中
void insert_sort(std::vector<int> &array)
{
    int n = array.size();
    if (n < 2)
        return;
    for (int i = 1; i < n; ++i)
    {
        int temp = array[i];
        int j = i;
        for (; j > 0; --j)
        {
            if (array[j - 1] > temp)
                array[j] = array[j - 1];
            else break;
        }
        array[j] = temp;
    }
}

// 对插入排序，如果最小元素在末尾，那么要移动很多次才能移到最前面。希尔排序就是主要针对这点进行优化
void shell_sort(std::vector<int> &array)
{
    int n = array.size();
    if (n < 2)
        return;
    int h = 1;
    while (h < n / 3)
        h = 3 * h + 1;
    while (h >= 1)
    {
        for (int i = h; i < n; ++i)
        {
            for (int j = i; j >= h && array[j] < array[j - h]; j -= h)
                std::swap(array[j], array[j - h]);
        }
        h /= 3;
    }
}

void _merge(std::vector<int> &array, std::vector<int> &temp_array, int l, int mid, int r)
{
    copy(array.begin() + l, array.begin() + r + 1, temp_array.begin() + l);
    int left = l, right = mid + 1;
    int cur = l;
    while (left <= mid && right <= r)
    {
        if (temp_array[left] <= temp_array[right])
            array[cur++] = temp_array[left++];
        else
            array[cur++] = temp_array[right++];
    }
    while (left <= mid)
        array[cur++] = temp_array[left++];
    while (right <= r)
        array[cur++] = temp_array[right++];
}

// 递归版本的
void _merge_sort_recursion(std::vector<int> &array, std::vector<int> &temp_array, int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) / 2;
    _merge_sort_recursion(array, temp_array, l, mid);
    _merge_sort_recursion(array, temp_array, mid + 1, r);
    _merge(array, temp_array, l, mid, r);
}

// 迭代版本的
void _merge_sort_iteration(std::vector<int> &array, std::vector<int> &temp_array)
{
    int n = array.size();
    for (int l = 1; l <= n / 2; l *= 2)
    {
        for (int i = 0; i < n - l; i += 2 * l)
        {
            _merge(array, temp_array, i, i + l - 1, std::min(i + 2 * l - 1, n - 1));
        }
    }
}

void merge_sort(std::vector<int> &array)
{
    int n = array.size();
    if (n < 2)
        return;
    std::vector<int> temp_array(n, 0);
    _merge_sort_recursion(array, temp_array, 0, n - 1);
    // _merge_sort_iteration(array, temp_array, 0, n - 1);
}

int _partition(std::vector<int> &array, int l, int r)
{
    int temp = array[l];
    int i = l - 1;
    int cur = l;
    while (cur <= r)
    {
        if (array[cur] < temp)
            std::swap(array[++i], array[cur++]);
        else if (array[cur] == temp)
            ++cur;
        else
            std::swap(array[cur], array[r--]);
    }
    // int i = l - 1;
    // int temp = array[r];
    // for(int j = l; j < r; ++j){
    //     if(array[j] <= temp) std::swap(array[++i], array[j]);
    // }
    // std::swap(array[i + 1], array[r]);
    return i + 1;
}

void _quick_sort(std::vector<int> &array, int l, int r)
{
    if (l >= r)
        return;
    int mid = _partition(array, l, r);
    _quick_sort(array, l, mid - 1);
    _quick_sort(array, mid + 1, r);
}

void quick_sort(std::vector<int> &array)
{
    int n = array.size();
    if (n < 2)
        return;
    _quick_sort(array, 0, n - 1);
}

void heap_sort(std::vector<int> &array)
{
    int n = array.size();
    if (n < 2)
        return;
    heap<int, std::less<int>> my_heap(array);
    my_heap.heap_sort();
}

void count_sort(std::vector<int> &array)
{
    int n = array.size();
    if (n < 2)
        return;
}

void radix_sort(std::vector<int> &array)
{
    int n = array.size();
    if (n < 2)
        return;
}

void bucket_sort(std::vector<int> &array)
{
    int n = array.size();
    if (n < 2)
        return;
}