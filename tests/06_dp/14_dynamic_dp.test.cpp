#include "../common.hpp"
#include "../../templates/06_dp/14_dynamic_dp.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 40);
        vector<vector<int>> g(n);
        vector<int> par(n, -1);
        for (int v = 1; v < n; v++) {
            int u = rnd(0, 2) ? rnd(0, v - 1) : v - 1;
            g[u].push_back(v), g[v].push_back(u), par[v] = u;
        }
        auto a = rnd_vec(n, -20, 20);
        DynamicDP dp(g, a);
        auto brute = [&]() {   // 编号大的点一定是编号小的点的后代，倒序做树形 DP
            vector<ll> f0(n, 0), f1(n, 0);
            for (int v = n - 1; v >= 0; v--) {
                f1[v] += a[v];
                if (par[v] != -1) f0[par[v]] += max(f0[v], f1[v]), f1[par[v]] += f0[v];
            }
            return max(f0[0], f1[0]);
        };
        CHECK(dp.answer() == brute());
        for (int q = 0; q < 100; q++) {
            int x = rnd(0, n - 1);
            ll v = rnd(-20, 20);
            dp.modify(x, v), a[x] = v;
            CHECK(dp.answer() == brute());
        }
    }
    return 0;
}
