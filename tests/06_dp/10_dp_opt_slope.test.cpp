#include "../common.hpp"
#include "../../templates/06_dp/10_dp_opt_slope.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(1, 40);
        auto c = rnd_vec(n, 1, it % 2 ? 10 : 10000000);
        ll L = rnd(0, it % 2 ? 20 : 10000000);
        vector<__int128> s(n + 1, 0);
        for (int i = 1; i <= n; i++) s[i] = s[i - 1] + c[i - 1] + 1;
        vector<__int128> f(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            f[i] = -1;
            for (int j = 0; j < i; j++) {
                __int128 d = s[i] - s[j] - (L + 1), v = f[j] + d * d;
                if (f[i] < 0 || v < f[i]) f[i] = v;
            }
        }
        CHECK(toy_packing(c, L) == (ll)f[n]);
    }
    for (int it = 0; it < 300; it++) {
        LineContainer lc;
        vector<pair<ll, ll>> lines;
        for (int op = 0; op < 50; op++) {
            ll k = rnd(-1000, 1000), m = rnd(-1e6, 1e6);
            lc.add(k, m), lines.push_back({k, m});
            ll x = rnd(-1e4, 1e4), best = LLONG_MIN;
            for (auto [kk, mm] : lines) best = max(best, kk * x + mm);
            CHECK(lc.query(x) == best);
        }
    }
    return 0;
}
