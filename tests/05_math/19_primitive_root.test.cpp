#include "../common.hpp"
#include "../../templates/05_math/19_primitive_root.hpp"

int main() {
    for (ll m = 1; m <= 600; m++) {
        // 暴力：每个与 m 互质的 a 的阶
        ll ph = 0;
        for (ll a = 1; a <= m; a++) ph += __gcd(a, m) == 1;
        vector<ll> roots;
        for (ll a = 1; a < max(m, 2LL); a++) {
            if (__gcd(a, m) != 1) {
                CHECK(PrimRoot::order(a, m) == -1);
                continue;
            }
            ll d = 1, x = a % m;
            while (x != 1 % m) x = x * a % m, d++;
            CHECK(PrimRoot::order(a, m) == d);
            if (d == ph) roots.push_back(a);
        }
        if (m == 1) roots = {0};
        if (roots.empty()) {
            CHECK(PrimRoot::min_root(m) == -1 && !PrimRoot::has_root(m));
        } else {
            CHECK(PrimRoot::has_root(m) && PrimRoot::min_root(m) == roots[0]);
            CHECK(PrimRoot::all_roots(m) == roots);
        }
    }
    // 大质数：原根的阶等于 p - 1
    for (ll p : {998244353LL, 1000000007LL, 1000000009LL}) {
        ll g = PrimRoot::min_root(p);
        CHECK(PrimRoot::order(g, p) == p - 1);
    }
    CHECK(PrimRoot::min_root(998244353) == 3);
    return 0;
}
