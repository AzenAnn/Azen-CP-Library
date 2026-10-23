#include "../common.hpp"
#include "../../templates/02_ds/20_lct.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 15);
        LCT lct(n);
        vector<ll> val(n + 1);
        for (int i = 1; i <= n; i++) val[i] = rnd(0, 1000), lct.update(i, val[i]);
        set<pair<int, int>> edges;
        auto path = [&](int s, int t) {   // 暴力：BFS 求路径，不连通返回空
            vector<int> pre(n + 1, -1);
            vector<vector<int>> g(n + 1);
            for (auto [u, v] : edges) g[u].push_back(v), g[v].push_back(u);
            queue<int> q;
            q.push(s), pre[s] = s;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : g[u])
                    if (pre[v] == -1) pre[v] = u, q.push(v);
            }
            vector<int> p;
            if (pre[t] == -1) return p;
            for (int x = t; x != s; x = pre[x]) p.push_back(x);
            p.push_back(s);
            return p;
        };
        for (int op = 0; op < 100; op++) {
            int t = rnd(0, 3), x = rnd(1, n), y = rnd(1, n);
            auto p = path(x, y);
            if (t == 0) {
                bool ok = lct.link(x, y);
                CHECK(ok == p.empty());
                if (ok) edges.insert({min(x, y), max(x, y)});
            } else if (t == 1) {
                bool has = edges.count({min(x, y), max(x, y)});
                CHECK(lct.cut(x, y) == has);
                edges.erase({min(x, y), max(x, y)});
            } else if (t == 2) {
                val[x] = rnd(0, 1000), lct.update(x, val[x]);
            } else {
                CHECK(lct.connected(x, y) == !p.empty());
                if (p.empty()) continue;
                ll s = 0;
                for (int v : p) s ^= val[v];
                CHECK(lct.query(x, y) == s);
            }
        }
    }
    return 0;
}
