#include "../common.hpp"
#include "../../templates/06_dp/11_dp_opt_quadrangle.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 40), K = rnd(1, n);
        auto a = rnd_vec(n, 1, 20);
        vector<ll> s(n + 1, 0);
        for (int i = 0; i < n; i++) s[i + 1] = s[i] + a[i];
        auto cost = [&](int j, int i) { return (s[i] - s[j]) * (s[i] - s[j]); };   // 满足四边形不等式
        const ll INF = LLONG_MAX / 4;
        vector<vector<ll>> f(K + 1, vector<ll>(n + 1, INF));
        f[0][0] = 0;
        for (int k = 1; k <= K; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 0; j < i; j++)
                    if (f[k - 1][j] < INF) f[k][i] = min(f[k][i], f[k - 1][j] + cost(j, i));
        CHECK(partition_min_cost(n, K, cost) == f[K][n]);
        // Knuth：与 O(n^3) 区间 DP 对比
        int m = rnd(1, 30);
        auto b = rnd_vec(m, 1, 50);
        vector<ll> t(m + 1, 0);
        for (int i = 0; i < m; i++) t[i + 1] = t[i] + b[i];
        vector<vector<ll>> g(m, vector<ll>(m, 0));
        for (int len = 2; len <= m; len++)
            for (int l = 0; l + len - 1 < m; l++) {
                int r = l + len - 1;
                g[l][r] = LLONG_MAX;
                for (int k = l; k < r; k++) g[l][r] = min(g[l][r], g[l][k] + g[k + 1][r] + t[r + 1] - t[l]);
            }
        CHECK(stone_merge_knuth(b) == g[0][m - 1]);
    }
    return 0;
}
