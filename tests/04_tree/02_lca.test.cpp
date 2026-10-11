#include "../common.hpp"
#include "../../templates/04_tree/02_lca.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 40);
        vector<vector<int>> g(n);
        vector<int> par(n, -1), dep(n, 0);
        for (int v = 1; v < n; v++) {
            int u = rnd(max(0, v - 3), v - 1);   // 偏向生成较深的树
            g[u].push_back(v), g[v].push_back(u), par[v] = u, dep[v] = dep[u] + 1;
        }
        LCA l(g, 0);
        for (int q = 0; q < 50; q++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1), x = a, y = b;
            while (dep[x] > dep[y]) x = par[x];
            while (dep[y] > dep[x]) y = par[y];
            while (x != y) x = par[x], y = par[y];
            CHECK(l.lca(a, b) == x);
            CHECK(l.dist(a, b) == dep[a] + dep[b] - 2 * dep[x]);
            int k = rnd(0, dep[a]), z = a;
            for (int i = 0; i < k; i++) z = par[z];
            CHECK(l.kth_ancestor(a, k) == z);
        }
    }
    return 0;
}
