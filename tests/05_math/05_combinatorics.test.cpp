#include "../common.hpp"
#include "../../templates/05_math/05_combinatorics.hpp"

int main() {
    const ll P = 1000000007;
    Comb cb(200, P);
    auto pc = pascal(100, P);
    for (int n = 0; n <= 100; n++)
        for (int k = -1; k <= n + 1; k++) {
            ll e = (k < 0 || k > n) ? 0 : pc[n][k];
            CHECK(cb.C(n, k) == e);
            if (k >= 0 && k <= n) CHECK(cb.A(n, k) == pc[n][k] * cb.f[k] % P);
        }
    vector<ll> cat = {1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862};
    for (int i = 0; i < 10; i++) CHECK(cb.catalan(i) == cat[i]);
    // Lucas 与杨辉三角（模小质数）对比
    for (ll p : {2LL, 3LL, 5LL, 7LL, 13LL}) {
        Lucas lu(p);
        auto pp = pascal(200, p);
        for (int n = 0; n <= 200; n++)
            for (int k = 0; k <= n; k++) CHECK(lu.C(n, k) == pp[n][k]);
        CHECK(lu.C(5, 7) == 0);
    }
    return 0;
}
