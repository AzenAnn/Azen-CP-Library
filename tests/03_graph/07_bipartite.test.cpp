#include "../common.hpp"
#include "../../templates/03_graph/07_bipartite.hpp"

int main() {
    for (int it = 0; it < 400; it++) {
        int n1 = rnd(1, 6), n2 = rnd(1, 6), m = rnd(0, 12);
        vector<pair<int, int>> E;
        Kuhn ku(n1, n2);
        HopcroftKarp hk(n1, n2);
        vector<vector<int>> g(n1);
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n1 - 1), v = rnd(0, n2 - 1);
            E.push_back({u, v}), ku.add_edge(u, v), hk.add_edge(u, v), g[u].push_back(v);
        }
        int best = 0;   // 暴力：枚举边的子集
        for (int mask = 0; mask < (1 << m); mask++) {
            vector<bool> ul(n1), ur(n2);
            bool ok = true;
            for (int i = 0; i < m && ok; i++)
                if (mask >> i & 1) {
                    if (ul[E[i].first] || ur[E[i].second]) ok = false;
                    ul[E[i].first] = ur[E[i].second] = true;
                }
            if (ok) best = max(best, __builtin_popcount(mask));
        }
        int r1 = ku.run(), r2 = hk.run();
        CHECK(r1 == best && r2 == best);
        for (int u = 0; u < n1; u++)
            if (ku.ml[u] != -1) CHECK(ku.mr[ku.ml[u]] == u && count(g[u].begin(), g[u].end(), ku.ml[u]));
        for (int u = 0; u < n1; u++)
            if (hk.ml[u] != -1) CHECK(hk.mr[hk.ml[u]] == u && count(g[u].begin(), g[u].end(), hk.ml[u]));
        auto [cl, cr] = min_vertex_cover(g, n2, hk.ml, hk.mr);
        CHECK((int)(cl.size() + cr.size()) == best);
        set<int> sl(cl.begin(), cl.end()), sr(cr.begin(), cr.end());
        for (auto [u, v] : E) CHECK(sl.count(u) || sr.count(v));
    }
    // 染色判定：与"是否存在奇环"（暴力枚举 2^n 种染色）对比
    for (int it = 0; it < 400; it++) {
        int n = rnd(1, 9), m = rnd(0, 12);
        vector<vector<int>> g(n);
        vector<pair<int, int>> E;
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            g[u].push_back(v), g[v].push_back(u), E.push_back({u, v});
        }
        bool exist = false;
        for (int mask = 0; mask < (1 << n) && !exist; mask++) {
            bool ok = true;
            for (auto [u, v] : E) ok &= (mask >> u & 1) != (mask >> v & 1);
            exist |= ok;
        }
        auto c = bipartite_color(g);
        CHECK(c.empty() == !exist);
        if (!c.empty())
            for (auto [u, v] : E) CHECK(c[u] != c[v]);
    }
    return 0;
}
