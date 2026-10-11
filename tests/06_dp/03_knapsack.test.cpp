#include "../common.hpp"
#include "../../templates/06_dp/03_knapsack.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(0, 8), W = rnd(0, 25);
        vector<int> w(n), c(n);
        vector<ll> v(n);
        for (int i = 0; i < n; i++) w[i] = rnd(1, 8), v[i] = rnd(0, 20), c[i] = rnd(0, 3);
        // 暴力：枚举每件物品选几个
        ll b01 = 0, bc = 0, bb = 0;
        vector<ll> ways(W + 1, 0);
        for (int mask = 0; mask < (1 << n); mask++) {
            ll sw = 0, sv = 0;
            for (int i = 0; i < n; i++)
                if (mask >> i & 1) sw += w[i], sv += v[i];
            if (sw <= W) b01 = max(b01, sv), ways[sw]++;
        }
        function<void(int, ll, ll, bool)> rec = [&](int i, ll sw, ll sv, bool bounded) {
            if (sw > W) return;
            if (i == n) {
                (bounded ? bb : bc) = max(bounded ? bb : bc, sv);
                return;
            }
            int lim = bounded ? c[i] : W / w[i];
            for (int k = 0; k <= lim; k++) rec(i + 1, sw + (ll)k * w[i], sv + k * v[i], bounded);
        };
        rec(0, 0, 0, false), rec(0, 0, 0, true);
        CHECK(knapsack01(w, v, W) == b01);
        CHECK(knapsack_complete(w, v, W) == bc);
        CHECK(knapsack_bounded(w, v, c, W) == bb);
        auto cw = count_ways01(w, W, 1000000007);
        for (int j = 0; j <= W; j++) CHECK(cw[j] == ways[j]);
        // 分组背包：每组最多选一件
        int G = rnd(0, 4);
        vector<vector<pair<int, ll>>> groups(G);
        for (auto &g : groups)
            for (int k = rnd(1, 3); k--;) g.push_back({(int)rnd(1, 8), rnd(0, 20)});
        ll bg = 0;
        function<void(int, ll, ll)> rg = [&](int i, ll sw, ll sv) {
            if (sw > W) return;
            if (i == G) { bg = max(bg, sv); return; }
            rg(i + 1, sw, sv);
            for (auto [wi, vi] : groups[i]) rg(i + 1, sw + wi, sv + vi);
        };
        rg(0, 0, 0);
        CHECK(knapsack_group(groups, W) == bg);
    }
    return 0;
}
