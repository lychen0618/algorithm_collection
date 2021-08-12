#pragma once
#include <random>

namespace util
{

    //左闭右闭
    int randint(int l, int r)
    {
        static std::default_random_engine e;
        static std::uniform_int_distribution<> u(l, r);
        if(l != u.min() || r != u.max()) u = std::uniform_int_distribution<>(l, r);
        return u(e);
    }
}