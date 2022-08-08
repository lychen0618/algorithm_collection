#pragma once
#include <ctime>
#include <random>
#include <vector>
// 在较短时间得到一个极有可能是素数的大整数

class BigPrime {
private:
    using ll = long long;

public:
    BigPrime(int bound) : bound_(bound), e_(std::time(0)), u_(bound_ + 1) {}

    ll get_big_prime();

private:
    ll get_pseudo_prime();

    bool miller_rabin(ll prime);

    ll quick_muliply_mod(ll a, ll b, ll m);

    ll quick_power_mod(ll a, ll b, ll m);

    const int bound_;
    std::vector<int> small_primes_;
    const int size_ = 2000;
    std::default_random_engine e_;
    std::uniform_int_distribution<ll> u_;
};