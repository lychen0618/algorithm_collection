#ifndef INSERT_MERGE_SORT_H__
#define INSERT_MERGE_SORT_H__
#include <functional>

namespace chapter02
{
    template <typename Iterator, typename CompareType = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void insert_sort(const Iterator begin, const Iterator end, CompareType compare = CompareType())
    {
        typedef typename std::iterator_traits<Iterator>::value_type T;
        auto size = std::distance(begin, end);
        if (size <= 1)
            return;
        for (auto iter = begin + 1; iter != end; ++iter)
        {
            T temp_value = *iter;
            auto forward_iter = iter;
            while (forward_iter != begin)
            {
                if (compare(*(forward_iter - 1), temp_value))
                    break;
                *forward_iter = *(forward_iter - 1);
                forward_iter--;
            }
            *forward_iter = temp_value;
        }
    }

    template <typename Iterator, typename CompareType = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void _merge(const Iterator begin, const Iterator end, const Iterator mid, CompareType compare = CompareType())
    {
        typedef typename std::iterator_traits<Iterator>::value_type T;
        std::vector<T> left(begin, mid);
        //哨兵
        left.emplace_back(INT32_MAX);
        std::vector<T> right(mid, end);
        right.emplace_back(INT32_MAX);
        auto left_iter = left.begin();
        auto right_iter = right.begin();
        for(auto iter = begin; iter != end; ++iter){
            if(compare(*left_iter, *right_iter)) *iter = *left_iter++;
            else *iter = *right_iter++;
        }
    }

    template <typename Iterator, typename CompareType = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void merge_sort(const Iterator begin, const Iterator end, CompareType compare = CompareType())
    {
        auto size = std::distance(begin, end);
        if (size <= 1)
            return;
        auto mid = begin + size / 2;
        merge_sort(begin, mid, compare);
        merge_sort(mid, end, compare);
        _merge(begin, end, mid);
    }
}

#endif /* INSERT_MERGE_SORT_H__ */