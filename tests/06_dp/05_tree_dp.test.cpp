#include "../common.hpp"
#include "../../templates/06_dp/05_tree_dp.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 12);
        vector<vector<int>> g(n);
        vector<int> par(n, -1);
        for (int v = 1; v < n; v++) {
            int u = rnd(0, v - 1);
            g[u].push_back(v), g[v].push_back(u), par[v] = u;
        }
        auto w = rnd_vec(n, -5, 20);
        ll best = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            bool ok = true;
            ll s = 0;
            for (int v = 0; v < n; v++)
                if (mask >> v & 1) {
                    s += w[v];
                    if (par[v] != -1 && (mask >> par[v] & 1)) ok = false;
                }
            if (ok) best = max(best, s);
        }
        CHECK(max_independent_set(g, w, 0) == best);
        // 换根：所有点到 u 的距离之和
        auto S = sum_dist_all_roots(g);
        for (int u = 0; u < n; u++) {
            vector<int> d(n, -1), q{u};
            d[u] = 0;
            for (size_t i = 0; i < q.size(); i++)
                for (int v : g[q[i]])
                    if (d[v] == -1) d[v] = d[q[i]] + 1, q.push_back(v);
            CHECK(S[u] == accumulate(d.begin(), d.end(), 0LL));
        }
        // 树上背包：森林（随机断开一些父子关系），最多选 m 个，选点必须先选父亲
        vector<int> fp(n, -1);
        for (int v = 1; v < n; v++) fp[v] = rnd(0, 3) ? par[v] : -1;
        auto ws = rnd_vec(n, 0, 20);
        int m = rnd(0, n);
        ll bk = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) > m) continue;
            bool ok = true;
            ll s = 0;
            for (int v = 0; v < n; v++)
                if (mask >> v & 1) {
                    s += ws[v];
                    if (fp[v] != -1 && !(mask >> fp[v] & 1)) ok = false;
                }
            if (ok) bk = max(bk, s);
        }
        CHECK(tree_knapsack(fp, ws, m) == bk);
    }
    return 0;
}
