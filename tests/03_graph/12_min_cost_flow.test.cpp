#include "../common.hpp"
#include "../../templates/03_graph/12_min_cost_flow.hpp"

int main() {
    for (int it = 0; it < 1500; it++) {
        int n = rnd(2, 5), m = rnd(0, 7), s = 0, t = n - 1;
        bool dag = it % 2;   // DAG 上允许负费用；一般图只用非负费用（保证无负环）
        vector<array<ll, 4>> E;
        MCMF a(n);
        MCMFDijkstra b(n);
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            if (dag) {
                if (u == v) continue;
                if (u > v) swap(u, v);
            }
            ll cap = rnd(0, 2), cost = dag ? rnd(-5, 5) : rnd(0, 5);
            E.push_back({u, v, cap, cost});
            a.add_edge(u, v, cap, cost), b.add_edge(u, v, cap, cost);
        }
        m = E.size();
        // 暴力：枚举每条边的流量
        ll bf = -1, bc = 0;
        vector<ll> f(m, 0);
        function<void(int)> rec = [&](int i) {
            if (i == m) {
                vector<ll> net(n, 0);
                ll cost = 0;
                for (int j = 0; j < m; j++) net[E[j][0]] -= f[j], net[E[j][1]] += f[j], cost += f[j] * E[j][3];
                for (int v = 0; v < n; v++)
                    if (v != s && v != t && net[v]) return;
                if (net[t] > bf || (net[t] == bf && cost < bc)) bf = net[t], bc = cost;
                return;
            }
            for (f[i] = 0; f[i] <= E[i][2]; f[i]++) rec(i + 1);
        };
        rec(0);
        auto ra = a.run(s, t), rb = b.run(s, t);
        CHECK(ra.first == bf && ra.second == bc);
        CHECK(rb.first == bf && rb.second == bc);
    }
    return 0;
}
