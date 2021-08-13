#ifndef LINEAR_SELECT_H__
#define LINEAR_SELECT_H__
#include <vector>
#include <functional>
#include "chapter07/quick_sort.hpp"
#include "chapter02/insert_merge_sort.hpp"
using chapter02::insert_sort;
using chapter07::partition;

namespace chapter09
{
    template <typename Iterator, typename CompareType = std::less<typename std::iterator_traits<Iterator>::value_type>>
    typename std::iterator_traits<Iterator>::value_type
    _find_median(const Iterator begin, const Iterator end, CompareType compare = CompareType())
    {
        typedef typename std::iterator_traits<Iterator>::value_type T;
        auto iter = begin;
        std::vector<T> middle_nums;
        while (iter < end)
        {
            auto from = iter;
            auto to = iter + 5;
            if (to > end)
                to = end;

            insert_sort(from, to, compare);
            middle_nums.push_back(*(from + (to - from - 1) / 2));
            iter += 5;
        }
        if (std::distance(begin, end) < 5)
            return middle_nums[0];
        else
            return _find_median(middle_nums.begin(), middle_nums.end(), compare);
    }

    template <typename Iterator, typename CompareType = std::less<typename std::iterator_traits<Iterator>::value_type>>
    typename std::iterator_traits<Iterator>::value_type
    worst_linear_time_select(const Iterator begin, const Iterator end, typename std::iterator_traits<Iterator>::difference_type rank, CompareType compare = CompareType())
    {
        typedef typename std::iterator_traits<Iterator>::value_type T;
        auto size = std::distance(begin, end);
        assert(size > 0);
        assert(rank < size);
        if (size == 1)
            return *begin;
        //find_median
        T mid_of_middles = _find_median(begin, end, compare);
        //find median_value position and swap
        auto iter = begin;
        while (std::distance(iter, end) > 0 && *iter != mid_of_middles)
        {
            iter++;
        }
        //partition
        auto mid_of_middles_iter = partition(begin, end, iter, compare);
        //judge
        auto mid_of_middles_rank = std::distance(begin, mid_of_middles_iter);
        if (mid_of_middles_rank == rank)
            return *mid_of_middles_iter;
        else if (mid_of_middles_rank < rank)
            return worst_linear_time_select(mid_of_middles_iter + 1, end, rank - mid_of_middles_rank - 1, compare);
        else
            return worst_linear_time_select(begin, mid_of_middles_iter, rank, compare);
    }

    template <typename Iterator, typename CompareType = std::less<typename std::iterator_traits<Iterator>::value_type>>
    typename std::iterator_traits<Iterator>::value_type
    expect_linear_time_select(const Iterator begin, const Iterator end, typename std::iterator_traits<Iterator>::difference_type rank, CompareType compare = CompareType())
    {
        auto size = std::distance(begin, end);
        if (size == 1)
            return *begin;
        auto partitioned_iter = partition(begin, end, begin + util::randint(0, size - 1), compare);
        auto pos = std::distance(begin, partitioned_iter);
        if (pos == rank)
            return *partitioned_iter;
        else if (pos < rank)
            return expect_linear_time_select(partitioned_iter + 1, end, rank - pos - 1, compare);
        else
            return expect_linear_time_select(begin, partitioned_iter - 1, rank);
    }
}

#endif /* LINEAR_SELECT_H__ */