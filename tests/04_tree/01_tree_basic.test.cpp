#include "../common.hpp"
#include "../../templates/04_tree/01_tree_basic.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 30);
        vector<vector<int>> g(n);
        vector<int> par(n, -1);
        for (int v = 1; v < n; v++) {
            int u = rnd(0, v - 1);
            g[u].push_back(v), g[v].push_back(u), par[v] = u;
        }
        // 暴力距离
        vector<vector<int>> d(n, vector<int>(n, 1e9));
        for (int i = 0; i < n; i++) d[i][i] = 0;
        for (int v = 1; v < n; v++) d[v][par[v]] = d[par[v]][v] = 1;
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        int diam = 0;
        for (auto &row : d) diam = max(diam, *max_element(row.begin(), row.end()));
        auto [len, a, b] = tree_diameter(g);
        CHECK(len == diam && d[a][b] == diam);

        TreeInfo t(g, 0);
        for (int v = 0; v < n; v++) {
            CHECK(t.parent[v] == par[v] && t.depth[v] == d[0][v]);
            int sz = 0;
            for (int u = 0; u < n; u++) sz += d[0][u] == d[0][v] + d[v][u];   // u 在 v 的子树中
            CHECK(t.sz[v] == sz);
        }
        // 重心：删去后最大连通块最小
        auto max_part = [&](int c) {
            int mx = 0;
            for (int v : g[c]) {
                int cnt = 0;
                for (int u = 0; u < n; u++) cnt += d[c][u] == 1 + d[v][u];
                mx = max(mx, cnt);
            }
            return mx;
        };
        int best = INT_MAX;
        for (int c = 0; c < n; c++) best = min(best, max_part(c));
        CHECK(max_part(tree_centroid(g)) == best);

        EulerTour e(g, 0);
        for (int v = 0; v < n; v++) {
            CHECK(e.ord[e.tin[v]] == v && e.tout[v] - e.tin[v] == t.sz[v]);
            for (int i = e.tin[v]; i < e.tout[v]; i++) {
                int u = e.ord[i];
                CHECK(d[0][u] == d[0][v] + d[v][u]);
            }
        }
    }
    return 0;
}
