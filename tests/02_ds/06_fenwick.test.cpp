#include "../common.hpp"
#include "../../templates/02_ds/06_fenwick.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 30);
        Fenwick f(n);
        RangeFenwick rf(n);
        vector<ll> a(n + 1, 0), b(n + 1, 0);
        for (int op = 0; op < 60; op++) {
            int i = rnd(1, n);
            ll x = rnd(0, 5);
            f.add(i, x), a[i] += x;
            int l = rnd(1, n), r = rnd(l, n);
            ll y = rnd(-5, 5);
            rf.add(l, r, y);
            for (int j = l; j <= r; j++) b[j] += y;
            int ql = rnd(1, n), qr = rnd(ql, n);
            CHECK(f.sum(ql, qr) == accumulate(a.begin() + ql, a.begin() + qr + 1, 0LL));
            CHECK(rf.sum(ql, qr) == accumulate(b.begin() + ql, b.begin() + qr + 1, 0LL));
            ll k = rnd(0, f.sum(n) + 2);
            int p = 1;
            ll s = a[1];
            while (p <= n && s < k) p++, s += (p <= n ? a[p] : 0);
            CHECK(f.lower_bound(k) == p);
        }
        auto c = rnd_vec(rnd(0, 30), -5, 5);
        ll inv = 0;
        for (size_t i = 0; i < c.size(); i++)
            for (size_t j = i + 1; j < c.size(); j++) inv += c[i] > c[j];
        CHECK(count_inversions(c) == inv);
    }
    for (int it = 0; it < 100; it++) {
        int n = rnd(1, 8), m = rnd(1, 8);
        Fenwick2D f(n, m);
        vector<vector<ll>> a(n + 1, vector<ll>(m + 1, 0));
        for (int op = 0; op < 40; op++) {
            int x = rnd(1, n), y = rnd(1, m);
            ll v = rnd(-5, 5);
            f.add(x, y, v), a[x][y] += v;
            int x1 = rnd(1, n), x2 = rnd(x1, n), y1 = rnd(1, m), y2 = rnd(y1, m);
            ll s = 0;
            for (int i = x1; i <= x2; i++)
                for (int j = y1; j <= y2; j++) s += a[i][j];
            CHECK(f.sum(x1, y1, x2, y2) == s);
        }
    }
    return 0;
}
