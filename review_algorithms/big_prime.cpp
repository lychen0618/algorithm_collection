#include "big_prime.h"

BigPrime::ll BigPrime::get_big_prime() {
    while (true) {
        ll prime = get_pseudo_prime();
        // if (miller_rabin(prime))
        //     return prime;
        return prime;
    }
}

BigPrime::ll BigPrime::get_pseudo_prime() {
    if (small_primes_.size() == 0) {
        std::vector<bool> num_map(size_, true);
        for (int i = 2; i < size_; ++i) {
            if (!num_map[i])
                continue;
            small_primes_.push_back(i);
            int pos = i * 2;
            while (pos < size_) {
                num_map[pos] = false;
                pos += i;
            }
        }
    }
    bool is_prime = false;
    ll prime;
    while (!is_prime) {
        prime = u_(e_);
        is_prime = true;
        for (auto& p : small_primes_) {
            if (prime % p == 0) {
                is_prime = false;
                break;
            }
        }
    }
    return prime;
}

bool BigPrime::miller_rabin(ll prime) {
    if (prime == 2)
        return true;
    if (prime < 2 || prime % 2 == 0)
        return false;
    int k = 0, t = prime - 1;
    while (!(t & 1)) {
        k++;
        t >>= 1;
    }
    for (int i = 0; i < 20; ++i) {
        ll a = u_(e_) % (prime - 1) + 1;
        ll b = quick_power_mod(a, t, prime);
        ll y;
        for (int j = 0; j < k; ++j) {
            y = quick_muliply_mod(b, b, prime);
            if (y == 1 && b != 1 && b != (prime - 1))
                return false;
            b = y;
        }
        if (y != 1)
            return false;
    }
    return true;
}

BigPrime::ll BigPrime::quick_muliply_mod(ll a, ll b, ll m) {
    ll ans = 0, temp = a;
    while (b) {
        if (b & 1) {
            ans = (ans + temp) % m;
        }
        temp = 2 * temp % m;
        b >>= 1;
    }
    return ans;
}

BigPrime::ll BigPrime::quick_power_mod(ll a, ll b, ll m) {
    ll ans = 1, temp = a;
    while (b) {
        if (b & 1) {
            ans = quick_muliply_mod(ans, temp, m);
        }
        temp = quick_muliply_mod(temp, temp, m);
        b >>= 1;
    }
    return ans;
}