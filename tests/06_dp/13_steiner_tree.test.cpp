#include "../common.hpp"
#include "../../templates/06_dp/13_steiner_tree.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(1, 8), m = rnd(0, 16);
        vector<array<ll, 3>> es;
        vector<vector<pair<int, ll>>> g(n);
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            ll w = rnd(0, 20);
            es.push_back({u, v, w}), g[u].push_back({v, w}), g[v].push_back({u, w});
        }
        int k = rnd(1, n);
        vector<int> keys(n);
        iota(keys.begin(), keys.end(), 0);
        shuffle(keys.begin(), keys.end(), test_rng);
        keys.resize(k);
        // 暴力：枚举边集，检查关键点连通，取最小边权和
        ll best = STEINER_INF;
        for (int S = 0; S < (1 << m); S++) {
            vector<int> f(n);
            iota(f.begin(), f.end(), 0);
            function<int(int)> find = [&](int x) { return f[x] == x ? x : f[x] = find(f[x]); };
            ll c = 0;
            for (int i = 0; i < m; i++)
                if (S >> i & 1) f[find(es[i][0])] = find(es[i][1]), c += es[i][2];
            bool ok = true;
            for (int x : keys) ok &= find(x) == find(keys[0]);
            if (ok) best = min(best, c);
        }
        CHECK(steiner_tree_cost(g, keys) == best);
    }
    return 0;
}
