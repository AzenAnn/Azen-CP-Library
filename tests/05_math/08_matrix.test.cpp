#include "../common.hpp"
#include "../../templates/05_math/08_matrix.hpp"

int main() {
    const ll P = 1000000007;
    vector<ll> f = {0, 1};
    for (int i = 2; i <= 200; i++) f.push_back((f[i - 1] + f[i - 2]) % P);
    for (int i = 0; i <= 200; i++) CHECK(fib(i, P) == f[i]);
    CHECK(fib(1000000000000000000LL, P) == 209783453);   // F(1e18) mod 1e9+7
    for (int it = 0; it < 100; it++) {
        int n = rnd(1, 5);
        Mat a(n, vector<ll>(n));
        for (auto &r : a)
            for (auto &x : r) x = rnd(0, P - 1);
        int e = rnd(0, 8);
        Mat r(n, vector<ll>(n, 0));
        for (int i = 0; i < n; i++) r[i][i] = 1;
        for (int i = 0; i < e; i++) r = mat_mul(r, a, P);
        CHECK(mat_pow(a, e, P) == r);
    }
    // (min, +)：恰好走 k 条边的最短路，与 DP 对比
    const ll INF = LLONG_MAX / 4;
    for (int it = 0; it < 100; it++) {
        int n = rnd(1, 6), k = rnd(1, 5);
        Mat w(n, vector<ll>(n, INF));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (rnd(0, 1)) w[i][j] = rnd(1, 9);
        Mat r = w;
        for (int i = 1; i < k; i++) r = minplus_mul(r, w, INF);
        vector<ll> d(n, INF);
        d[0] = 0;
        for (int step = 0; step < k; step++) {
            vector<ll> nd(n, INF);
            for (int u = 0; u < n; u++)
                for (int v = 0; v < n; v++)
                    if (d[u] < INF && w[u][v] < INF) nd[v] = min(nd[v], d[u] + w[u][v]);
            d = nd;
        }
        for (int v = 0; v < n; v++) CHECK(r[0][v] == d[v]);
    }
    return 0;
}
