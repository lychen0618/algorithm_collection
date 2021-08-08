#include <iostream>
#include <chapter09/algorithm.hpp>
#include <chapter07/algorithm.hpp>
using namespace std;

void test_get_max_and_min()
{
    vector<int> array1{1, 5, 3, 7, 8, 5};
    int max_value = 0, min_value = 0;
    int *max_value_pointer = &max_value;
    int *min_value_pointer = &min_value;
    chapter09::get_max_and_min(array1, max_value_pointer, min_value_pointer);
    assert((*max_value_pointer) == 8);
    assert((*min_value_pointer) == 1);

    vector<int> array2{1, 5, 3, 7, 8, 5};
    chapter09::get_max_and_min(array1, max_value_pointer, min_value_pointer);
    assert((*max_value_pointer) == 8);
    assert((*min_value_pointer) == 1);
}

void test_quicksort()
{
    vector<int> array1{1, 5, 3, 7, 8};
    vector<int> array1_copy = array1;
    chapter07::basic_quick_sort(array1_copy);
    for(size_t i = 1; i < array1_copy.size(); ++i){
        assert(array1_copy[i - 1] <= array1_copy[i]);
    }

    array1_copy = array1;
    chapter07::random_quick_sort(array1_copy);
    for(size_t i = 1; i < array1_copy.size(); ++i){
        assert(array1_copy[i - 1] <= array1_copy[i]);
    }
}

int main()
{
    test_get_max_and_min();
    test_quicksort();
    return 0;
}