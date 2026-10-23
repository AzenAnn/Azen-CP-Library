#include "../common.hpp"
#include "../../templates/03_graph/11_diff_constraints.hpp"

int main() {
    for (int it = 0; it < 1000; it++) {
        int n = rnd(1, 7), m = rnd(0, 12);
        vector<array<ll, 3>> cons;
        const ll INF = 1e18;
        vector<vector<ll>> d(n, vector<ll>(n, INF));
        for (int i = 0; i < n; i++) d[i][i] = 0;
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            ll w = rnd(-5, 8);
            cons.push_back({u, v, w});
            d[u][v] = min(d[u][v], w);
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (d[i][k] < INF && d[k][j] < INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        bool neg = false;
        for (int i = 0; i < n; i++) neg |= d[i][i] < 0;
        auto x = diff_constraints(n, cons);
        CHECK(x.empty() == neg);
        for (auto &[u, v, w] : cons)
            if (!x.empty()) CHECK(x[v] - x[u] <= w);
        if (!x.empty())
            for (int i = 0; i < n; i++) CHECK(x[i] <= 0);
    }
    return 0;
}
