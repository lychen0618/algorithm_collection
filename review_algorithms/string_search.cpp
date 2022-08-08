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

void get_next(const string& pattern, vector<int>& next) {
    int n = static_cast<int>(pattern.size());
    next.resize(n);
    next[0] = 0;
    int k = 0;
    for (int i = 1; i < n; ++i) {
        while (k > 0 && pattern[k] != pattern[i])
            k = next[k - 1];
        if (pattern[k] == pattern[i])
            ++k;
        next[i] = k;
    }
}

int kmp(const string& s, const string& pattern) {
    vector<int> next;
    get_next(pattern, next);
    int m = static_cast<int>(s.size());
    int n = static_cast<int>(pattern.size());
    for (int i = 0, j = 0; i < m;) {
        if (s[i] == pattern[j]) {
            ++j;
            if (j == n)
                return i + 1 - n;
        } else {
            if (j != 0) {
                j = next[j - 1];
                continue;
            }
        }
        ++i;
    }
    return m;
}