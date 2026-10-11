#include "../common.hpp"
#include "../../templates/06_dp/06_bitmask_dp.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 7);
        vector<vector<ll>> d(n, vector<ll>(n));
        for (auto &r : d)
            for (auto &x : r) x = rnd(1, 30);
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        ll best = n == 1 ? 0 : LLONG_MAX;
        if (n > 1) do {
                ll s = 0;
                for (int i = 0; i < n; i++) s += d[p[i]][p[(i + 1) % n]];
                best = min(best, s);
            } while (next_permutation(p.begin() + 1, p.end()));
        CHECK(tsp(d) == best);
        int R = rnd(1, 4), C = rnd(1, 4);
        vector<vector<int>> f(R, vector<int>(C));
        for (auto &r : f)
            for (auto &x : r) x = rnd(0, 3) > 0;
        ll cnt = 0;
        for (int mask = 0; mask < (1 << (R * C)); mask++) {
            bool ok = true;
            for (int i = 0; i < R; i++)
                for (int j = 0; j < C; j++) {
                    if (!(mask >> (i * C + j) & 1)) continue;
                    if (!f[i][j]) ok = false;
                    if (j + 1 < C && (mask >> (i * C + j + 1) & 1)) ok = false;
                    if (i + 1 < R && (mask >> ((i + 1) * C + j) & 1)) ok = false;
                }
            cnt += ok;
        }
        CHECK(corn_fields(f, 100000000) == cnt % 100000000);
        int m = rnd(0, 6);
        auto a = rnd_vec(1 << m, -10, 10);
        auto s = sos_subset_sum(a, m);
        for (int mask = 0; mask < (1 << m); mask++) {
            ll t = 0;
            for (int sub = 0; sub < (1 << m); sub++)
                if ((sub & mask) == sub) t += a[sub];
            CHECK(s[mask] == t);
        }
    }
    return 0;
}
