#include "../common.hpp"
#include "../../templates/03_graph/22_dominator_tree.hpp"

int main() {
    for (int it = 0; it < 2000; it++) {
        int n = rnd(1, 10), m = rnd(0, 25), s = rnd(0, n - 1);
        vector<vector<int>> g(n);
        for (int i = 0; i < m; i++) g[rnd(0, n - 1)].push_back(rnd(0, n - 1));
        auto reach = [&](int ban) {   // 删去 ban 后从 s 可达的点
            vector<bool> vis(n);
            if (ban == s) return vis;
            vis[s] = true;
            vector<int> q = {s};
            for (size_t h = 0; h < q.size(); h++)
                for (int v : g[q[h]])
                    if (v != ban && !vis[v]) vis[v] = true, q.push_back(v);
            return vis;
        };
        auto base = reach(-1);
        // dom[u][v]：u 支配 v（删去 u 后 v 不可达）
        vector<vector<bool>> dom(n, vector<bool>(n));
        for (int u = 0; u < n; u++) {
            auto r = reach(u);
            for (int v = 0; v < n; v++) dom[u][v] = base[v] && !r[v];
        }
        auto idom = dominator_tree(g, s);
        for (int v = 0; v < n; v++) {
            if (!base[v]) {
                CHECK(idom[v] == -1);
                continue;
            }
            if (v == s) {
                CHECK(idom[v] == s);
                continue;
            }
            // idom(v)：v 的严格支配点中被其他所有严格支配点支配的那个（离 v 最近）
            int ans = -1;
            for (int u = 0; u < n; u++) {
                if (u == v || !dom[u][v]) continue;
                bool ok = true;
                for (int x = 0; x < n; x++)
                    if (x != v && x != u && dom[x][v] && !dom[x][u]) ok = false;
                if (ok) ans = u;
            }
            CHECK(idom[v] == ans);
        }
    }
    return 0;
}
