#include "../common.hpp"
#include "../../templates/03_graph/03_shortest_path.hpp"

int main() {
    for (int it = 0; it < 400; it++) {
        int n = rnd(1, 10), m = rnd(0, 25);
        bool neg = it % 2, zero_one = it % 3 == 0;
        WGraph g(n);
        vector<vector<ll>> d(n, vector<ll>(n, DIST_INF));
        for (int i = 0; i < n; i++) d[i][i] = 0;
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            ll w = zero_one ? rnd(0, 1) : neg ? rnd(-3, 10) : rnd(1, 10);
            g[u].push_back({v, w});
            d[u][v] = min(d[u][v], w);
        }
        auto f = d;
        floyd(f);
        int s = rnd(0, n - 1);
        bool negcyc = false;   // 从 s 能到达负环
        for (int v = 0; v < n; v++)
            if (f[s][v] < DIST_INF && f[v][v] < 0) negcyc = true;
        auto sp = spfa(g, s);
        if (negcyc) {
            CHECK(sp.empty());
            continue;
        }
        CHECK(!sp.empty());
        for (int v = 0; v < n; v++) CHECK(sp[v] == f[s][v]);
        if (!neg || zero_one) {
            auto dj = dijkstra(g, s);
            for (int v = 0; v < n; v++) CHECK(dj[v] == f[s][v]);
        }
        if (zero_one) {
            auto b = bfs01(g, s);
            for (int v = 0; v < n; v++) CHECK(b[v] == f[s][v]);
        }
        if (!neg && !zero_one) {
            // 最短路计数：按距离排序后 DP
            auto [dist, ways] = dijkstra_count(g, s, 1000000007);
            vector<int> ord(n);
            iota(ord.begin(), ord.end(), 0);
            sort(ord.begin(), ord.end(), [&](int a, int b) { return f[s][a] < f[s][b]; });
            vector<ll> cnt(n, 0);
            cnt[s] = 1;
            for (int u : ord) {
                if (f[s][u] >= DIST_INF) continue;
                for (auto [v, w] : g[u])
                    if (f[s][u] + w == f[s][v]) cnt[v] += cnt[u];
            }
            for (int v = 0; v < n; v++) CHECK(ways[v] == cnt[v] % 1000000007);
        }
    }
    return 0;
}
