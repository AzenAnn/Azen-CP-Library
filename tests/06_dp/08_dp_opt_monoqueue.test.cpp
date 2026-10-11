#include "../common.hpp"
#include "../../templates/06_dp/08_dp_opt_monoqueue.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(1, 30), L = rnd(1, 5), R = L + rnd(0, 5);
        auto a = rnd_vec(n, -10, 10);
        const ll NEG = LLONG_MIN / 4;
        vector<ll> f(n, NEG);
        f[0] = a[0];
        for (int i = 1; i < n; i++)
            for (int j = max(0, i - R); j <= i - L; j++)
                if (f[j] > NEG) f[i] = max(f[i], f[j] + a[i]);
        CHECK(window_dp(a, L, R) == f);

        int m = rnd(0, 6), W = rnd(0, 30);
        vector<int> w(m), c(m);
        vector<ll> v(m);
        for (int i = 0; i < m; i++) w[i] = rnd(1, 7), v[i] = rnd(0, 20), c[i] = rnd(0, 4);
        vector<ll> dp(W + 1, 0);   // 暴力：每件物品枚举选几个
        for (int i = 0; i < m; i++) {
            vector<ll> nd(dp);
            for (int j = 0; j <= W; j++)
                for (int k = 1; k <= c[i] && k * w[i] <= j; k++) nd[j] = max(nd[j], dp[j - k * w[i]] + k * v[i]);
            dp = nd;
        }
        CHECK(knapsack_bounded_mq(w, v, c, W) == dp[W]);
    }
    return 0;
}
