#include "../common.hpp"
#include "../../templates/03_graph/16_gomory_hu.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 8), m = rnd(0, 14);
        vector<array<ll, 3>> es;
        for (int i = 0; i < m; i++) es.push_back({rnd(0, n - 1), rnd(0, n - 1), rnd(1, 10)});
        GomoryHu gh(n, es);
        auto all = gh.all_pairs();
        // 暴力：枚举点集 S，u ∈ S、v ∉ S 时割值为跨越 S 的边权和
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++) {
                if (u == v) continue;
                ll best = LLONG_MAX;
                for (int S = 0; S < (1 << n); S++) {
                    if (!(S >> u & 1) || (S >> v & 1)) continue;
                    ll c = 0;
                    for (auto [a, b, w] : es)
                        if ((S >> a & 1) != (S >> b & 1)) c += w;
                    best = min(best, c);
                }
                CHECK(all[u][v] == best);
                CHECK(gh.cut(u, v) == best);
            }
    }
    return 0;
}
