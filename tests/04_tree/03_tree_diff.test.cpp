#include "../common.hpp"
#include "../../templates/04_tree/03_tree_diff.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 30);
        vector<vector<int>> g(n);
        vector<int> par(n, -1), dep(n, 0);
        for (int v = 1; v < n; v++) {
            int u = rnd(0, v - 1);
            g[u].push_back(v), g[v].push_back(u), par[v] = u, dep[v] = dep[u] + 1;
        }
        auto path = [&](int a, int b) {   // 返回路径上的点
            vector<int> pa, pb;
            while (dep[a] > dep[b]) pa.push_back(a), a = par[a];
            while (dep[b] > dep[a]) pb.push_back(b), b = par[b];
            while (a != b) pa.push_back(a), pb.push_back(b), a = par[a], b = par[b];
            pa.push_back(a);
            pa.insert(pa.end(), pb.rbegin(), pb.rend());
            return pa;
        };
        TreeDiff tv(g, 0), te(g, 0);
        vector<ll> vv(n, 0), ve(n, 0);
        for (int q = 0; q < 30; q++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1);
            ll x = rnd(-5, 5);
            tv.add_path_vertices(a, b, x);
            te.add_path_edges(a, b, x);
            auto p = path(a, b);
            for (int v : p) vv[v] += x;
            int top = p[0];   // 路径上深度最小的点（LCA）不代表任何路径上的边
            for (int v : p)
                if (dep[v] < dep[top]) top = v;
            for (int v : p)
                if (v != top) ve[v] += x;
        }
        CHECK(tv.build() == vv);
        CHECK(te.build() == ve);
        auto w = rnd_vec(n, -10, 10);
        auto pre = tv.prefix(w);
        for (int q = 0; q < 30; q++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1);
            ll s = 0;
            for (int v : path(a, b)) s += w[v];
            CHECK(tv.path_sum(pre, a, b) == s);
        }
    }
    return 0;
}
