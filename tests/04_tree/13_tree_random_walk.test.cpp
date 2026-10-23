#include "../common.hpp"
#include "../../templates/04_tree/13_tree_random_walk.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 9), root = rnd(0, n - 1);
        bool weighted = rnd(0, 1);
        vector<vector<pair<int, ll>>> g(n);
        for (int v = 1; v < n; v++) {
            int u = rnd(0, v - 1);
            ll w = weighted ? rnd(1, 5) : 1;
            g[u].push_back({v, w}), g[v].push_back({u, w});
        }
        TreeRandomWalk rw(g, root);
        // 暴力：对每个终点 t 解方程 E[x] = Σ (w + E[y]) / deg(x)，E[t] = 0（高斯消元）
        for (int t = 0; t < n; t++) {
            vector<vector<double>> a(n, vector<double>(n + 1, 0));
            for (int x = 0; x < n; x++) {
                a[x][x] = 1;
                if (x == t) continue;
                double deg = g[x].size();
                for (auto [y, w] : g[x]) a[x][y] -= 1 / deg, a[x][n] += w / deg;
            }
            for (int c = 0; c < n; c++) {
                int p = c;
                for (int r = c; r < n; r++)
                    if (fabs(a[r][c]) > fabs(a[p][c])) p = r;
                swap(a[c], a[p]);
                for (int r = 0; r < n; r++)
                    if (r != c) {
                        double f = a[r][c] / a[c][c];
                        for (int k = c; k <= n; k++) a[r][k] -= f * a[c][k];
                    }
            }
            for (int s = 0; s < n; s++) CHECK(fabs(rw.expected(s, t) - a[s][n] / a[s][s]) < 1e-6);
        }
    }
    return 0;
}
