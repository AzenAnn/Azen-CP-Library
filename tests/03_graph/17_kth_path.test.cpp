#include "../common.hpp"
#include "../../templates/03_graph/17_kth_path.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(1, 6), m = rnd(0, 12), k = rnd(1, 30);
        int s = rnd(0, n - 1), t = rnd(0, n - 1);
        vector<array<ll, 3>> es;
        for (int i = 0; i < m; i++) es.push_back({rnd(0, n - 1), rnd(0, n - 1), rnd(1, 5)});
        // 暴力：cnt[d][v] = 从 s 出发长度恰为 d、终点为 v 的路径条数（计重数）
        const int D = 60;
        vector<vector<ll>> cnt(D + 1, vector<ll>(n, 0));
        cnt[0][s] = 1;
        for (int d = 0; d <= D; d++)
            for (auto [u, v, w] : es)
                if (d + w <= D && cnt[d][u]) cnt[d + w][v] = min<ll>(1000, cnt[d + w][v] + cnt[d][u]);
        vector<ll> brute;
        for (int d = 0; d <= D && (int)brute.size() < k; d++)
            for (ll c = 0; c < cnt[d][t] && (int)brute.size() < k; c++) brute.push_back(d);
        auto got = k_shortest_paths(n, es, s, t, k);
        // 长度 ≤ D 的部分必须完全一致
        vector<ll> a, b;
        for (ll x : got)
            if (x <= D) a.push_back(x);
        for (ll x : brute) b.push_back(x);
        if ((int)b.size() == k) CHECK(got == b);
        else CHECK(a == b && (int)got.size() <= k);
    }
    return 0;
}
