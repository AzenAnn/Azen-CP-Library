#include "../common.hpp"
#include "../../templates/05_math/09_gauss.hpp"

int main() {
    // 模小质数：与枚举所有解对比
    for (int it = 0; it < 2000; it++) {
        ll p = vector<ll>{2, 3, 5, 7}[rnd(0, 3)];
        int n = rnd(1, 4), m = rnd(1, 4);
        vector<vector<ll>> a(n, vector<ll>(m + 1));
        for (auto &row : a)
            for (auto &v : row) v = rnd(0, p - 1);
        ll total = 1, cnt = 0;
        for (int i = 0; i < m; i++) total *= p;
        for (ll code = 0; code < total; code++) {
            vector<ll> x(m);
            ll c = code;
            for (int i = 0; i < m; i++) x[i] = c % p, c /= p;
            bool ok = true;
            for (auto &row : a) {
                ll s = 0;
                for (int j = 0; j < m; j++) s += row[j] * x[j];
                ok &= s % p == row[m];
            }
            cnt += ok;
        }
        vector<ll> x;
        int st = gauss_mod(a, x, p);
        CHECK(st == (cnt == 0 ? 0 : cnt == 1 ? 1 : 2));
        if (st) {
            for (auto &row : a) {
                ll s = 0;
                for (int j = 0; j < m; j++) s += row[j] * x[j];
                CHECK(s % p == row[m]);
            }
        }
        // 异或方程组：同一组系数取模 2
        vector<bitset<8>> b(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= m; j++) b[i][j] = a[i][j] & 1;
        int c2 = 0;
        for (int mask = 0; mask < (1 << m); mask++) {
            bool ok = true;
            for (int i = 0; i < n; i++) {
                int s = 0;
                for (int j = 0; j < m; j++) s ^= b[i][j] & (mask >> j & 1);
                ok &= s == b[i][m];
            }
            c2 += ok;
        }
        vector<int> xx;
        CHECK(gauss_xor(b, m, xx) == (c2 == 0 ? 0 : c2 == 1 ? 1 : 2));
    }
    // 实数：与模大质数的结果（秩相同的概率极高）对比，并检查解满足方程
    for (int it = 0; it < 2000; it++) {
        int n = rnd(1, 5), m = rnd(1, 5);
        vector<vector<double>> a(n, vector<double>(m + 1));
        vector<vector<ll>> ai(n, vector<ll>(m + 1));
        vector<ll> x0(m);
        for (auto &v : x0) v = rnd(-3, 3);
        bool consistent = rnd(0, 1);
        for (int i = 0; i < n; i++) {
            ll s = 0;
            for (int j = 0; j < m; j++) ai[i][j] = rnd(-1, 1) * rnd(0, 3), s += ai[i][j] * x0[j];
            ai[i][m] = consistent ? s : rnd(-10, 10);
            for (int j = 0; j <= m; j++) a[i][j] = ai[i][j];
        }
        vector<double> x;
        vector<ll> xm;
        int st = gauss_real(a, x, 1e-7), sm = gauss_mod(ai, xm, 1000000007);
        CHECK(st == sm);
        if (st)
            for (int i = 0; i < n; i++) {
                double s = 0;
                for (int j = 0; j < m; j++) s += a[i][j] * x[j];
                CHECK(fabs(s - a[i][m]) < 1e-6);
            }
    }
    return 0;
}
