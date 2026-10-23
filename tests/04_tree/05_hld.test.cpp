#include "../common.hpp"
#include "../../templates/04_tree/05_hld.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 30), root = rnd(0, n - 1);
        vector<vector<int>> g(n);
        for (int v = 1; v < n; v++) {
            int u = rnd(0, v - 1);
            g[u].push_back(v), g[v].push_back(u);
        }
        // 暴力：以 root 为根的父亲和深度
        vector<int> par(n, -1), dep(n, 0), order{root};
        for (size_t i = 0; i < order.size(); i++)
            for (int v : g[order[i]])
                if (v != par[order[i]]) par[v] = order[i], dep[v] = dep[order[i]] + 1, order.push_back(v);
        auto path = [&](int a, int b) {
            vector<int> p;
            while (dep[a] > dep[b]) p.push_back(a), a = par[a];
            while (dep[b] > dep[a]) p.push_back(b), b = par[b];
            while (a != b) p.push_back(a), p.push_back(b), a = par[a], b = par[b];
            p.push_back(a);
            return p;
        };
        auto in_subtree = [&](int v, int u) {   // v 是否在 u 的子树中
            while (v != -1 && v != u) v = par[v];
            return v == u;
        };
        auto w = rnd_vec(n, -10, 10);
        HLD h(g, w, root);
        for (int q = 0; q < 60; q++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1), t = rnd(0, 4);
            auto p = path(a, b);
            if (t == 0) {
                ll x = rnd(-5, 5);
                h.path_add(a, b, x);
                for (int v : p) w[v] += x;
            } else if (t == 1) {
                ll x = rnd(-5, 5);
                h.subtree_add(a, x);
                for (int v = 0; v < n; v++)
                    if (in_subtree(v, a)) w[v] += x;
            } else if (t == 2) {
                ll s = 0;
                for (int v : p) s += w[v];
                CHECK(h.path_sum(a, b) == s);
            } else if (t == 3) {
                ll s = 0;
                for (int v = 0; v < n; v++)
                    if (in_subtree(v, a)) s += w[v];
                CHECK(h.subtree_sum(a) == s);
            } else {
                int l = p.back();
                for (int v : p)
                    if (dep[v] < dep[l]) l = v;
                CHECK(h.lca(a, b) == l);
            }
        }
    }
    return 0;
}
