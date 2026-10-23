#include "../common.hpp"
#include "../../templates/05_math/21_binomial_inversion.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 40);
        ll m = rnd(0, 1) ? 998244353 : rnd(2, 1000);
        auto f = rnd_vec(n, 0, m - 1);
        // 正向变换后再反演，应还原
        auto g1 = binom_transform_lower(f, m, +1);
        CHECK(binom_transform_lower(g1, m) == f);
        auto g2 = binom_transform_upper(f, m, +1);
        CHECK(binom_transform_upper(g2, m) == f);
        // 正向变换与定义直接对比
        vector<vector<ll>> C(n, vector<ll>(n, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= i; j++) C[i][j] = (j == 0 || j == i) ? 1 % m : (C[i - 1][j - 1] + C[i - 1][j]) % m;
        for (int x = 0; x < n; x++) {
            ll a = 0, b = 0;
            for (int i = 0; i <= x; i++) a = (a + C[x][i] * f[i]) % m;
            for (int i = x; i < n; i++) b = (b + C[i][x] * f[i]) % m;
            CHECK(g1[x] == a && g2[x] == b);
        }
    }
    // 恰好 k 个不动点：暴力枚举排列
    for (int n = 0; n <= 7; n++) {
        vector<ll> cnt(n + 1, 0);
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        do {
            int c = 0;
            for (int i = 0; i < n; i++) c += p[i] == i;
            cnt[c]++;
        } while (next_permutation(p.begin(), p.end()));
        CHECK(fixed_point_counts(n, 1000000007) == cnt);
    }
    return 0;
}
