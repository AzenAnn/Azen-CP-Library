#include "../common.hpp"
#include "../../templates/03_graph/18_dmst.hpp"

int main() {
    for (int it = 0; it < 1000; it++) {
        int n = rnd(1, 6), m = rnd(0, 12), root = rnd(0, n - 1);
        vector<array<ll, 3>> es;
        for (int i = 0; i < m; i++) es.push_back({rnd(0, n - 1), rnd(0, n - 1), rnd(0, 20)});
        // 暴力：每个非根点选一条入边，检查没有环
        vector<vector<int>> in(n);
        for (int i = 0; i < m; i++)
            if (es[i][0] != es[i][1]) in[es[i][1]].push_back(i);
        ll best = LLONG_MAX;
        vector<int> par(n, -1);
        function<void(int, ll)> go = [&](int v, ll c) {
            if (v == n) {
                for (int x = 0; x < n; x++) {
                    int y = x;
                    for (int s = 0; s < n && y != root; s++) y = par[y];
                    if (y != root) return;
                }
                best = min(best, c);
                return;
            }
            if (v == root) return go(v + 1, c);
            for (int id : in[v]) par[v] = es[id][0], go(v + 1, c + es[id][2]);
        };
        go(0, 0);
        CHECK(directed_mst(n, es, root) == (best == LLONG_MAX ? -1 : best));
    }
    return 0;
}
