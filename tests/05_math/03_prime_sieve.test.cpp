#include "../common.hpp"
#include "../../templates/05_math/03_prime_sieve.hpp"

int main() {
    const int N = 20000;
    auto er = sieve_eratosthenes(N);
    LinearSieve ls(N);
    vector<int> primes;
    for (int i = 0; i <= N; i++) {
        CHECK(er[i] == is_prime(i));
        CHECK(ls.is_prime(i) == is_prime(i));
        if (is_prime(i)) primes.push_back(i);
    }
    CHECK(ls.primes == primes);
    for (int x = 2; x <= N; x++) {
        auto f = ls.factorize(x);
        vector<pair<ll, int>> f2(f.begin(), f.end());
        CHECK(f2 == factorize(x));
        ll prod = 1;
        for (auto [p, c] : f) {
            CHECK(is_prime(p));
            for (int i = 0; i < c; i++) prod *= p;
        }
        CHECK(prod == x);
    }
    for (int it = 0; it < 300; it++) {
        ll n = rnd(1, 100000);
        vector<ll> d;
        for (ll i = 1; i <= n; i++)
            if (n % i == 0) d.push_back(i);
        CHECK(divisors(n) == d);
    }
    CHECK(factorize(1000000007LL * 998244353LL) == (vector<pair<ll, int>>{{998244353, 1}, {1000000007, 1}}));
    return 0;
}
