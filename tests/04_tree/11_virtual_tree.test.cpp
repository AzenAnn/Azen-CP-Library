#include "../common.hpp"
#include "../../templates/04_tree/11_virtual_tree.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(2, 30);
        vector<vector<pair<int, ll>>> g(n);
        vector<int> par(n, -1), dep(n, 0);
        vector<ll> pw(n, 0);   // 到父亲的边权
        for (int v = 1; v < n; v++) {
            int u = rnd(0, v - 1);
            ll w = rnd(1, 20);
            g[u].push_back({v, w}), g[v].push_back({u, w}), par[v] = u, dep[v] = dep[u] + 1, pw[v] = w;
        }
        VirtualTree vt(g);
        auto lca = [&](int a, int b) {
            while (dep[a] > dep[b]) a = par[a];
            while (dep[b] > dep[a]) b = par[b];
            while (a != b) a = par[a], b = par[b];
            return a;
        };
        for (int q = 0; q < 20; q++) {
            int k = rnd(1, min(n - 1, 6));
            vector<int> cand(n - 1);
            iota(cand.begin(), cand.end(), 1);
            shuffle(cand.begin(), cand.end(), test_rng);
            vector<int> keys(cand.begin(), cand.begin() + k);
            // 暴力闭包：关键点及两两 LCA
            set<int> clo(keys.begin(), keys.end());
            for (int a : keys)
                for (int b : keys) clo.insert(lca(a, b));
            auto [A, vp] = vt.build(keys);
            CHECK(set<int>(A.begin(), A.end()) == clo);
            for (size_t i = 0; i < A.size(); i++) {
                int x = par[A[i]], expect = -1;   // 虚树父亲 = 闭包中最近的真祖先
                while (x != -1 && !clo.count(x)) x = par[x];
                expect = x;
                CHECK(vp[i] == expect);
            }
            // 消耗战：与整棵树上的 DP 对比
            vector<bool> key(n, false);
            for (int v : keys) key[v] = true;
            vector<ll> h(n, 0);
            vector<bool> has(n, false);
            vector<int> order{0};
            for (size_t i = 0; i < order.size(); i++)
                for (auto [v, w] : g[order[i]])
                    if (v != par[order[i]]) order.push_back(v);
            for (int i = n - 1; i > 0; i--) {
                int v = order[i];
                ll sub = 0;
                bool any = key[v];
                for (auto [c, w] : g[v])
                    if (c != par[v] && has[c]) sub += h[c], any = true;
                has[v] = any;
                if (any) h[v] = key[v] ? pw[v] : min(pw[v], sub);
            }
            ll expect = 0;
            for (auto [c, w] : g[0])
                if (has[c]) expect += h[c];
            CHECK(vt.min_cut_keys(keys) == expect);
        }
    }
    return 0;
}
