#include <iostream>
#include <cassert>
#include "util.hpp"
#include "chapter09/linear_select.hpp"
#include "chapter07/quick_sort.hpp"
#include "chapter02/insert_merge_sort.hpp"
using namespace std;

void test_select()
{
    vector<int> array{3, 6, 2, 1, 9};
    vector<int> array1;
    using chapter09::worst_linear_time_select;
    array1 = array;
    EXPECT_EQUAL(worst_linear_time_select(array1.begin(), array1.end(), 2), 3);
    EXPECT_EQUAL(worst_linear_time_select(array1.begin(), array1.end(), 4), 9);
    EXPECT_EQUAL(worst_linear_time_select(array1.begin(), array1.end(), 0), 1);

    using chapter09::expect_linear_time_select;
    array1 = array;
    EXPECT_EQUAL(expect_linear_time_select(array1.begin(), array1.end(), 2), 3);
    EXPECT_EQUAL(expect_linear_time_select(array1.begin(), array1.end(), 4), 9);
    EXPECT_EQUAL(expect_linear_time_select(array1.begin(), array1.end(), 0), 1);

}

void test_sort()
{
    vector<double> array{1.0, 3.3, 6.3, 4.5, 2.9, 10.9};
    vector<double> array1;
    using chapter02::insert_sort;
    array1 = array;
    insert_sort(array1.begin(), array1.end());
    util::check_non_decending_order(array1.begin(), array1.end());

    using chapter02::merge_sort;
    array1 = array;
    merge_sort(array1.begin(), array1.end());
    util::check_non_decending_order(array1.begin(), array1.end());

    using chapter07::quick_sort;
    array1 = array;
    quick_sort(array1.begin(), array1.end());
    util::check_non_decending_order(array1.begin(), array1.end());
}

int main()
{
    test_select();
    return 0;
}