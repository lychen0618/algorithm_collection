#ifndef UTIL_H__
#define UTIL_H__
#include <random>
#define EXPECT_EQUAL(a, b) \
    do                     \
    {                      \
        assert(a == b);    \
    } while (0);

#define EXPECT_LESSEQ(a, b) \
    do                      \
    {                       \
        assert(a <= b);     \
    } while (0);
namespace util
{

    //左闭右闭
    int randint(int l, int r)
    {
        static std::default_random_engine e;
        static std::uniform_int_distribution<> u(l, r);
        if (l != u.min() || r != u.max())
            u = std::uniform_int_distribution<>(l, r);
        return u(e);
    }

    template <typename Iterator>
    inline void check_non_decending_order(const Iterator begin, const Iterator end)
    {
        auto iter = begin;
        auto size = std::distance(begin, end);
        if (size <= 1)
            return;
        for (iter++; iter != end; ++iter)
        {
            EXPECT_LESSEQ(*(iter - 1), *iter);
        }
    }
}

#endif /* UTIL_H__ */