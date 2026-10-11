#include "../common.hpp"
#include "../../templates/05_math/08_crt.hpp"

int main() {
    vector<ll> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    for (int it = 0; it < 3000; it++) {
        int k = rnd(1, 4);
        vector<ll> m, r;
        auto ps = primes;
        shuffle(ps.begin(), ps.end(), test_rng);
        ll M = 1;
        for (int i = 0; i < k; i++) {
            ll mi = ps[i] * (rnd(0, 1) ? ps[i] : 1);   // 两两互质
            m.push_back(mi), r.push_back(rnd(-50, 50)), M *= mi;
        }
        ll x = crt(r, m);
        CHECK(0 <= x && x < M);
        for (int i = 0; i < k; i++) CHECK(((x - r[i]) % m[i] + m[i]) % m[i] == 0);
        // exCRT：模数任意，与暴力枚举对比
        vector<ll> m2, r2;
        ll L = 1;
        for (int i = 0; i < k; i++) {
            m2.push_back(rnd(1, 12)), r2.push_back(rnd(0, 30));
            L = L / __gcd(L, m2.back()) * m2.back();
        }
        ll first = -1;
        for (ll y = 0; y < L && first == -1; y++) {
            bool ok = true;
            for (int i = 0; i < k; i++) ok &= y % m2[i] == r2[i] % m2[i];
            if (ok) first = y;
        }
        auto [y, l] = excrt(r2, m2);
        CHECK(y == first);
        if (first != -1) CHECK(l == L);
    }
    // 大模数
    auto [y, l] = excrt({3, 5}, {1000000007LL, 998244353LL});
    CHECK(l == 1000000007LL * 998244353LL && y % 1000000007LL == 3 && y % 998244353LL == 5);
    return 0;
}
