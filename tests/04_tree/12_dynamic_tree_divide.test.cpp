#include "../common.hpp"
#include "../../templates/04_tree/12_dynamic_tree_divide.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 40);
        vector<vector<int>> g(n);
        for (int v = 1; v < n; v++) {
            int u = rnd(0, 2) ? rnd(0, v - 1) : v - 1;   // 混合随机树和长链
            g[u].push_back(v), g[v].push_back(u);
        }
        auto w = rnd_vec(n, -10, 10);
        DynamicTreeDivide dt(g, w);
        vector<vector<int>> dist(n, vector<int>(n, -1));
        for (int s = 0; s < n; s++) {
            vector<int> q = {s};
            dist[s][s] = 0;
            for (size_t h = 0; h < q.size(); h++)
                for (int v : g[q[h]])
                    if (dist[s][v] < 0) dist[s][v] = dist[s][q[h]] + 1, q.push_back(v);
        }
        for (int q = 0; q < 200; q++) {
            int x = rnd(0, n - 1);
            if (rnd(0, 1)) {
                ll d = rnd(-10, 10);
                dt.modify(x, d), w[x] += d;
            } else {
                int k = rnd(0, n);
                ll s = 0;
                for (int v = 0; v < n; v++)
                    if (dist[x][v] <= k) s += w[v];
                CHECK(dt.query(x, k) == s);
            }
        }
    }
    return 0;
}
