#include "../common.hpp"
#include "../../templates/06_dp/16_wqs_slope_trick.hpp"

int main() {
    for (int it = 0; it < 1000; it++) {
        int n = rnd(1, 30);
        auto a = rnd_vec(n, -20, 20);
        // 暴力 DP：dp[i][j][last]
        const ll NEG = LLONG_MIN / 4;
        int K = (n + 1) / 2;
        vector<vector<array<ll, 2>>> dp(n + 1, vector<array<ll, 2>>(K + 1, {NEG, NEG}));
        dp[0][0][0] = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= K; j++)
                for (int l = 0; l < 2; l++) {
                    if (dp[i][j][l] == NEG) continue;
                    dp[i + 1][j][0] = max(dp[i + 1][j][0], dp[i][j][l]);
                    if (!l && j + 1 <= K) dp[i + 1][j + 1][1] = max(dp[i + 1][j + 1][1], dp[i][j][l] + a[i]);
                }
        int k = rnd(0, K);
        CHECK(max_k_nonadjacent(a, k) == max(dp[n][k][0], dp[n][k][1]));
        // Slope trick：暴力 DP，b_i 只需取 a 中出现过的值
        vector<ll> vals = a;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        vector<ll> f(vals.size(), 0);
        for (ll x : a) {
            ll best = LLONG_MAX;
            for (size_t v = 0; v < vals.size(); v++) best = min(best, f[v]), f[v] = best + llabs(x - vals[v]);
        }
        CHECK(min_cost_nondecreasing(a) == *min_element(f.begin(), f.end()));
    }
    return 0;
}
