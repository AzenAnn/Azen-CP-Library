#include "../common.hpp"
#include "../../templates/03_graph/04_mst.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 7), m = rnd(0, 12);
        vector<array<ll, 3>> edges;
        vector<vector<ll>> w(n, vector<ll>(n, LLONG_MAX));
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            ll c = rnd(1, 20);
            edges.push_back({c, u, v});
            if (u != v) w[u][v] = w[v][u] = min(w[u][v], c);
        }
        // 暴力：枚举边的子集，选 n-1 条且连通的最小权
        ll best = -1;
        for (int mask = 0; mask < (1 << m); mask++) {
            if (__builtin_popcount(mask) != n - 1) continue;
            vector<int> fa(n);
            iota(fa.begin(), fa.end(), 0);
            function<int(int)> find = [&](int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); };
            ll s = 0;
            int joined = 0;
            for (int i = 0; i < m; i++)
                if (mask >> i & 1) {
                    int a = find(edges[i][1]), b = find(edges[i][2]);
                    if (a != b) fa[a] = b, joined++;
                    s += edges[i][0];
                }
            if (joined == n - 1 && (best == -1 || s < best)) best = s;
        }
        CHECK(kruskal(n, edges) == best);
        CHECK(prim(w) == best);
    }
    return 0;
}
