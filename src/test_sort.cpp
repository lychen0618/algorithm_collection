#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "sort.h"
using namespace std;
#define FLAG true

#define TEST_EQUAL(A, SORT)                               \
    do                                                    \
    {                                                     \
        vector<int> arr_copy = A;                         \
        SORT(arr_copy);                                   \
        if (FLAG)                                         \
        {                                                 \
            ostream_iterator<int> oite(cout, " ");        \
            copy(arr_copy.begin(), arr_copy.end(), oite); \
            cout << endl;                                 \
        }                                                 \
        assert(is_sorted(arr_copy) == true);              \
    } while (0)

bool is_sorted(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] < arr[i - 1])
            return false;
    }
    return true;
}

void test_equal(vector<int> &arr)
{
    // compare sort
    TEST_EQUAL(arr, bubble_sort);
    TEST_EQUAL(arr, select_sort);
    TEST_EQUAL(arr, insert_sort);
    TEST_EQUAL(arr, shell_sort);
    TEST_EQUAL(arr, merge_sort);
    TEST_EQUAL(arr, quick_sort);
    TEST_EQUAL(arr, heap_sort);

    // linear sort
    TEST_EQUAL(arr, count_sort);
    TEST_EQUAL(arr, radix_sort);
    TEST_EQUAL(arr, bucket_sort);
}

int main()
{
    ostream_iterator<int> oite(cout, " ");
    int time;

    vector<int> arr1 = {1, 3, 5, 2, 3, 8, 9, 0};
    time = 100;
    while (time--)
    {
        random_shuffle(arr1.begin(), arr1.end());
        if (FLAG)
        {
            cout << "original: ";
            copy(arr1.begin(), arr1.end(), oite);
            cout << endl;
        }
        test_equal(arr1);
    }

    vector<int> arr2 = {2, 1};
    time = 100;
    while (time--)
    {
        random_shuffle(arr2.begin(), arr2.end());
        if (FLAG)
        {
            cout << "original: ";
            copy(arr2.begin(), arr2.end(), oite);
            cout << endl;
        }
        test_equal(arr2);
    }

    vector<int> arr3 = {22, 15, 99, 2, 0, 5, 356, 11, 33, 22, 88, 45, 6, 9, 0};
    time = 100;
    while (time--)
    {
        random_shuffle(arr3.begin(), arr3.end());
        if (FLAG)
        {
            cout << "original: ";
            copy(arr3.begin(), arr3.end(), oite);
            cout << endl;
        }
        test_equal(arr3);
    }

    return 0;
}