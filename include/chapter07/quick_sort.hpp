#ifndef QUICK_SORT_H__
#define QUICK_SORT_H__
#include <functional>
#include "util.hpp"
namespace chapter07
{
    template <typename Iterator, typename CompareType = std::less<typename std::iterator_traits<Iterator>::value_type>>
    Iterator partition(const Iterator begin, const Iterator end,
                       const Iterator partition_iter, CompareType compare = CompareType())
    {
        auto size = std::distance(begin, end);
        assert(size >= 0);
        if (size == 0)
            return end;
        if (size <= 1)
            return begin;
        assert(std::distance(begin, partition_iter) >= 0 && std::distance(partition_iter, end) > 0);
        auto smaller_next = begin;              //指向比key小的元素区间的下一个(即大于等于key元素区间的第一个），其中key为序列最后一个元素
        auto current = begin;                   //指向当前待处理的元素
        std::swap(*partition_iter, *(end - 1)); //交换partition元素到末尾
        while (current != end - 1)
        {
            if (compare(*current, *(end - 1)))
            {
                std::swap(*smaller_next, *current);
                smaller_next++;
            }
            current++;
        }
        std::swap(*smaller_next, *(end - 1)); //交换partition元素到它的位置
        return smaller_next;
    }

    template <typename Iterator, typename CompareType = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void quick_sort(const Iterator begin, const Iterator end, CompareType compare = CompareType())
    {
        auto size = std::distance(begin, end);
        if (size <= 1)
            return;
        auto partitioned_iter = partition(begin, end, begin + util::randint(0, size - 1), compare); //随机找一个划分主元
        quick_sort(begin, partitioned_iter, compare);
        quick_sort(partitioned_iter + 1, end, compare);
    }
}

#endif /* QUICK_SORT_H__ */