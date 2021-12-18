#ifndef SORT_H
#define SORT_H
#include <vector>

void bubble_sort(std::vector<int>& array);

void select_sort(std::vector<int>& array);

void insert_sort(std::vector<int>& array);

void shell_sort(std::vector<int>& array);

void merge_sort(std::vector<int>& array);

void quick_sort(std::vector<int>& array);

void heap_sort(std::vector<int>& array);

void count_sort(std::vector<int>& array);

void radix_sort(std::vector<int>& array);

void bucket_sort(std::vector<int>& array, int bucket = 10);

#endif // SORT_H