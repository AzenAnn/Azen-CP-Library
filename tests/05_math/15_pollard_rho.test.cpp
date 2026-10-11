#include "../common.hpp"
#include "../../templates/05_math/15_pollard_rho.hpp"

vector<u64> trial(u64 n) {
    vector<u64> r;
    for (u64 p = 2; p * p <= n; p++)
        while (n % p == 0) r.push_back(p), n /= p;
    if (n > 1) r.push_back(n);
    return r;
}

int main() {
    const int N = 1000000;
    vector<bool> comp(N + 1, false);
    for (int i = 2; i * i <= N; i++)
        if (!comp[i])
            for (int j = i * i; j <= N; j += i) comp[j] = true;
    for (int i = 0; i <= N; i++) CHECK(is_prime_mr(i) == (i >= 2 && !comp[i]));
    for (u64 c : {561ULL, 41041ULL, 3215031751ULL, 3825123056546413051ULL}) CHECK(!is_prime_mr(c));   // 伪素数
    CHECK(is_prime_mr((1ULL << 61) - 1) && is_prime_mr(1000000007ULL) && is_prime_mr(998244353ULL));
    for (int it = 0; it < 300; it++) {
        u64 n = rnd(1, 1e12);
        CHECK(factorize_big(n) == trial(n));
    }
    for (u64 n : {1000000007ULL * 998244353ULL, 999999937ULL * 999999937ULL, 4295098369ULL, (1ULL << 62) + 1}) {
        auto f = factorize_big(n);
        u64 prod = 1;
        for (u64 p : f) {
            CHECK(is_prime_mr(p));
            prod *= p;
        }
        CHECK(prod == n);
    }
    CHECK(factorize_big(1).empty());
    return 0;
}
