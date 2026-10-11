#include "../common.hpp"
#include "../../templates/06_dp/09_dp_expectation.hpp"

int n, t;
vector<vector<pair<int, ll>>> g;
// 暴力：枚举所有路径，按概率加权
double brute(int u, double prob, ll len) {
    if (u == t || g[u].empty()) return prob * len;
    double s = 0;
    for (auto [v, w] : g[u]) s += brute(v, prob / g[u].size(), len + w);
    return s;
}

int main() {
    for (int it = 0; it < 500; it++) {
        n = rnd(2, 7), t = n - 1;
        vector<array<ll, 3>> E;
        g.assign(n, {});
        for (int u = 0; u < n - 1; u++) {   // 保证每个非终点都有出边，且只连向编号更大的点
            int k = rnd(1, 3);
            for (int i = 0; i < k; i++) {
                int v = rnd(u + 1, n - 1);
                ll w = rnd(1, 10);
                E.push_back({u, v, w}), g[u].push_back({v, w});
            }
        }
        CHECK(fabs(dag_expected_length(n, E, 0, t) - brute(0, 1, 0)) < 1e-9);
    }
    // 收集卡片：n = 2 时为 1 + 2 = 3
    CHECK(fabs(coupon_collector(1) - 1) < 1e-12 && fabs(coupon_collector(2) - 3) < 1e-12);
    // 模拟检验 expected_steps_with_stay：期望为 n / (1 - p)
    CHECK(fabs(expected_steps_with_stay(10, 0.25) - 10 / 0.75) < 1e-9);
    mt19937 rng(1);
    double sum = 0;
    int T = 200000;
    for (int i = 0; i < T; i++) {
        int pos = 0, steps = 0;
        while (pos < 5) steps++, pos += (rng() % 4 != 0);   // p = 1/4 停留
        sum += steps;
    }
    CHECK(fabs(sum / T - expected_steps_with_stay(5, 0.25)) < 0.05);
    return 0;
}
