#include "../common.hpp"
#include "../../templates/04_tree/04_pseudo_tree.hpp"

int main() {
    for (int it = 0; it < 1500; it++) {
        // 生成若干个连通块，每块 = 随机树 + 一条额外的边（可能是重边或自环）
        int n = 0;
        vector<array<ll, 3>> es;
        int blocks = rnd(1, 3);
        for (int b = 0; b < blocks; b++) {
            int k = rnd(1, 4), base = n;
            for (int v = 1; v < k; v++) es.push_back({base + v, base + rnd(0, v - 1), rnd(0, 9)});
            es.push_back({base + rnd(0, k - 1), base + rnd(0, k - 1), rnd(0, 9)});
            n += k;
        }
        shuffle(es.begin(), es.end(), test_rng);
        PseudoForest pf(n, es);
        // 环：边编号连成一圈、点在环上
        for (size_t c = 0; c < pf.cycles.size(); c++) {
            auto &cy = pf.cycles[c];
            int k = cy.size();
            for (int i = 0; i < k; i++) {
                auto e = es[pf.cyc_e[c][i]];
                int a = cy[i], b = cy[(i + 1) % k];
                CHECK((e[0] == a && e[1] == b) || (e[0] == b && e[1] == a));
                CHECK(pf.cyc_w[c][i] == e[2]);
            }
            set<int> ids(pf.cyc_e[c].begin(), pf.cyc_e[c].end());
            CHECK((int)ids.size() == k);
        }
        CHECK((int)pf.cycles.size() == blocks);
        // 直径：暴力枚举所有简单路径（不重复经过点）
        vector<vector<array<ll, 2>>> g(n);
        for (auto [u, v, w] : es)
            if (u != v) g[u].push_back({v, w}), g[v].push_back({u, w});
        vector<ll> diam(blocks, 0);
        vector<bool> vis(n);
        function<void(int, ll)> dfs = [&](int u, ll len) {
            diam[pf.comp[u]] = max(diam[pf.comp[u]], len);
            for (auto [v, w] : g[u])
                if (!vis[v]) vis[v] = true, dfs(v, len + w), vis[v] = false;
        };
        for (int s = 0; s < n; s++) vis[s] = true, dfs(s, 0), vis[s] = false;
        auto got = pf.diameters();
        for (int c = 0; c < blocks; c++) CHECK(got[c] == diam[c]);
        // 最大权独立集：暴力枚举
        auto val = rnd_vec(n, 0, 20);
        ll best = 0;
        for (int S = 0; S < (1 << n); S++) {
            bool ok = true;
            for (auto [u, v, w] : es)
                if ((S >> u & 1) && (S >> v & 1)) ok = false;
            if (!ok) continue;
            ll s = 0;
            for (int v = 0; v < n; v++)
                if (S >> v & 1) s += val[v];
            best = max(best, s);
        }
        CHECK(pf.max_independent_set(val) == best);
        // 函数图
        int m = rnd(1, 12);
        vector<int> nxt(m);
        for (auto &x : nxt) x = rnd(0, m - 1);
        auto [cl, dist] = functional_graph(nxt);
        for (int v = 0; v < m; v++) {
            int u = v, d = 0;
            vector<int> seen(m, -1);
            while (seen[u] == -1) seen[u] = d++, u = nxt[u];
            CHECK(dist[v] == seen[u] && cl[v] == d - seen[u]);
        }
    }
    return 0;
}
