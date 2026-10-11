#include "../common.hpp"
#include "../../templates/03_graph/11_max_flow.hpp"

int main() {
    for (int it = 0; it < 1000; it++) {
        int n = rnd(2, 8), m = rnd(0, 16), s = 0, t = n - 1;
        Dinic d(n);
        vector<array<ll, 3>> E;
        vector<int> ids;
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            ll c = rnd(0, 10);
            E.push_back({u, v, c}), ids.push_back(d.add_edge(u, v, c));
        }
        ll best = LLONG_MAX;   // 暴力最小割
        for (int mask = 0; mask < (1 << n); mask++) {
            if (!(mask >> s & 1) || (mask >> t & 1)) continue;
            ll c = 0;
            for (auto [u, v, w] : E)
                if ((mask >> u & 1) && !(mask >> v & 1)) c += w;
            best = min(best, c);
        }
        ll f = d.max_flow(s, t);
        CHECK(f == best);
        vector<ll> net(n, 0);   // 流量守恒与容量限制
        for (int i = 0; i < m; i++) {
            ll x = d.flow(ids[i]);
            CHECK(0 <= x && x <= E[i][2]);
            net[E[i][0]] -= x, net[E[i][1]] += x;
        }
        for (int v = 1; v < n - 1; v++) CHECK(net[v] == 0);
        CHECK(net[t] == f);
        auto S = d.min_cut(s);
        CHECK(S[s] && !S[t]);
        ll c = 0;
        for (auto [u, v, w] : E)
            if (S[u] && !S[v]) c += w;
        CHECK(c == f);
    }
    return 0;
}
