#include "../common.hpp"
#include "../../templates/02_ds/04_dsu.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 20);
        DSU d(n);
        vector<int> color(n);
        iota(color.begin(), color.end(), 0);
        for (int op = 0; op < 40; op++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1);
            bool diff = color[a] != color[b];
            CHECK(d.merge(a, b) == diff);
            int ca = color[a], cb = color[b];
            for (int &c : color)
                if (c == cb) c = ca;
            set<int> s(color.begin(), color.end());
            CHECK(d.comps == (int)s.size());
            int x = rnd(0, n - 1), y = rnd(0, n - 1);
            CHECK(d.same(x, y) == (color[x] == color[y]));
            CHECK(d.size(x) == count(color.begin(), color.end(), color[x]));
        }
        // 带权并查集 A：只加入正确的约束，全部应被接受，且 diff 与真实值一致
        vector<ll> val = rnd_vec(n, -50, 50);
        WeightedDSU w(n);
        for (int op = 0; op < 40; op++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1);
            CHECK(w.merge(a, b, val[a] - val[b]));
            int x = rnd(0, n - 1), y = rnd(0, n - 1);
            if (w.find(x) == w.find(y)) CHECK(w.diff(x, y) == val[x] - val[y]);
        }
        // 带权并查集 B：随机约束，与暴力（在已接受的约束图上 BFS 推出差值）对比
        WeightedDSU w2(n);
        vector<vector<pair<int, ll>>> adj(n);   // 边 u -> v 权 c 表示 val[u] - val[v] = c
        for (int op = 0; op < 40; op++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1);
            ll c = rnd(-3, 3);
            vector<ll> pot(n, LLONG_MIN);   // pot[v] = val[v] - val[a]
            pot[a] = 0;
            queue<int> q;
            q.push(a);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (auto [v, cc] : adj[u])
                    if (pot[v] == LLONG_MIN) pot[v] = pot[u] - cc, q.push(v);
            }
            bool consistent = pot[b] == LLONG_MIN || -pot[b] == c;
            CHECK(w2.merge(a, b, c) == consistent);
            if (consistent && pot[b] == LLONG_MIN) adj[a].push_back({b, c}), adj[b].push_back({a, -c});
        }
        // 可撤销并查集
        RollbackDSU r(n);
        vector<pair<int, int>> ops;
        for (int op = 0; op < 30; op++) ops.push_back({rnd(0, n - 1), rnd(0, n - 1)});
        int k = rnd(0, 30);
        for (int i = 0; i < k; i++) r.merge(ops[i].first, ops[i].second);
        int snap = r.snapshot();
        vector<int> before(n);
        for (int i = 0; i < n; i++) before[i] = r.find(i);
        for (int i = k; i < 30; i++) r.merge(ops[i].first, ops[i].second);
        r.rollback(snap);
        for (int i = 0; i < n; i++) CHECK(r.find(i) == before[i]);
    }
    return 0;
}
