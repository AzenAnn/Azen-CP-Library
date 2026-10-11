#include "../common.hpp"
#include "../../templates/01_basic/02_prefix_sum.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(0, 30);
        auto a = rnd_vec(n, -50, 50);
        auto s = prefix_sum(a);
        for (int l = 0; l <= n; l++)
            for (int r = l; r <= n; r++) {
                ll t = 0;
                for (int i = l; i < r; i++) t += a[i];
                CHECK(s[r] - s[l] == t);
            }
        ll k = rnd(-30, 30), cnt = 0;
        for (int l = 0; l < n; l++)
            for (int r = l + 1; r <= n; r++) cnt += s[r] - s[l] == k;
        CHECK(count_subarrays_sum_k(a, k) == cnt);

        Diff1D d(n);
        vector<ll> b(n, 0);
        for (int q = 0; q < 20 && n; q++) {
            int l = rnd(0, n - 1), r = rnd(l, n);
            ll x = rnd(-9, 9);
            d.add(l, r, x);
            for (int i = l; i < r; i++) b[i] += x;
        }
        CHECK(d.build() == b);
    }
    for (int it = 0; it < 100; it++) {
        int n = rnd(1, 8), m = rnd(1, 8);
        vector<vector<ll>> a(n, vector<ll>(m));
        for (auto &row : a)
            for (auto &x : row) x = rnd(-9, 9);
        PrefixSum2D ps(a);
        Diff2D df(n, m);
        vector<vector<ll>> b(n, vector<ll>(m, 0));
        for (int q = 0; q < 30; q++) {
            int r1 = rnd(0, n), r2 = rnd(r1, n), c1 = rnd(0, m), c2 = rnd(c1, m);
            ll t = 0;
            for (int i = r1; i < r2; i++)
                for (int j = c1; j < c2; j++) t += a[i][j];
            CHECK(ps.query(r1, c1, r2, c2) == t);
            ll x = rnd(-5, 5);
            df.add(r1, c1, r2, c2, x);
            for (int i = r1; i < r2; i++)
                for (int j = c1; j < c2; j++) b[i][j] += x;
        }
        CHECK(df.build() == b);
    }
    return 0;
}
