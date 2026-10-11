#include "../common.hpp"
#include "../../templates/05_math/04_inverse.hpp"

int main() {
    for (int it = 0; it < 5000; it++) {
        ll m = rnd(1, 60), a = rnd(-100, 100), expect = -1;
        for (ll x = 0; x < m; x++)
            if (((a * x - 1) % m + m) % m == 0) { expect = x; break; }
        CHECK(inv_mod(a, m) == expect);
    }
    for (ll p : {2LL, 3LL, 7LL, 1000003LL, 998244353LL}) {
        int n = min<ll>(p - 1, 5000);
        auto inv = inverses(n, p);
        for (int i = 1; i <= n; i++) CHECK((__int128)inv[i] * i % p == 1);
    }
    return 0;
}
