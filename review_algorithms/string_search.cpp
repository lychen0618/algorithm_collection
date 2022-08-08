#include "string_search.h"

#include <iostream>

#include "big_prime.h"
using ll = long long;

int rabin_karp(const string& s, const string& pattern) {
    BigPrime bp(int(10e20));
    ll prime = bp.get_big_prime();
    std::cout << "prime:" << prime << std::endl;
    ll base = 257;
    ll mul = 1;
    int m = static_cast<int>(s.size());
    int n = static_cast<int>(pattern.size());
    for (int i = 0; i < n - 1; ++i) {
        mul = (mul * base) % prime;
    }
    ll pattern_num = 0, s_num = 0;
    for (int i = 0; i < n; ++i) {
        pattern_num = (pattern_num * base + pattern[i] + 1) % prime;
        s_num = (s_num * base + s[i] + 1) % prime;
    }
    if (s_num == pattern_num)
        return 0;
    for (int i = n; i < m; ++i) {
        s_num = (s_num - mul * (s[i - n] + 1) + prime) % prime;
        s_num = (s_num * base + s[i] + 1) % prime;
        if (s_num == pattern_num)
            return i - n + 1;
    }
    return m;
}