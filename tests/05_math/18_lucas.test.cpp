#include "../common.hpp"
#include "../../templates/05_math/18_lucas.hpp"

int main() {
    // 杨辉三角（模任意 M）作为暴力
    for (int it = 0; it < 300; it++) {
        ll M = rnd(0, 2) ? rnd(1, 2000) : (ll)vector<int>{8, 9, 27, 32, 72, 100, 1000, 1024, 999}[rnd(0, 8)];
        int N = rnd(0, 60);
        vector<vector<ll>> C(N + 1, vector<ll>(N + 1, 0));
        for (int i = 0; i <= N; i++)
            for (int j = 0; j <= i; j++) C[i][j] = (j == 0 || j == i) ? 1 % M : (C[i - 1][j - 1] + C[i - 1][j]) % M;
        for (int q = 0; q < 20; q++) {
            int n = rnd(0, N), m = rnd(-1, N + 1);
            ll want = (m < 0 || m > n) ? 0 : C[n][m];
            CHECK(ExLucas::exlucas(n, m, M) == want);
        }
    }
    // Lucas：p 为质数，n 很大时与扩展 Lucas 互相对比
    vector<ll> primes = {2, 3, 5, 7, 11, 13, 101, 997, 10007};
    for (int it = 0; it < 300; it++) {
        ll p = primes[rnd(0, primes.size() - 1)];
        ll n = rnd(0, 1000000000000LL), m = rnd(0, n);
        CHECK(ExLucas::lucas(n, m, p) == ExLucas::exlucas(n, m, p));
        if (n <= 60) {
            ll c = 1;   // n 较小时直接算
            for (ll i = 0; i < m; i++) c = c * (n - i) / (i + 1);
            CHECK(ExLucas::lucas(n, m, p) == c % p);
        }
    }
    // 大 n、合数模数：与"分别对质因子用 Lucas 再合并"不好比，改为与 C(n, m) 的小 n 精确值比较
    for (int it = 0; it < 200; it++) {
        ll n = rnd(0, 60), m = rnd(0, n), M = rnd(1, 1000000);
        unsigned __int128 c = 1;
        for (ll i = 0; i < m; i++) c = c * (n - i) / (i + 1);
        CHECK(ExLucas::exlucas(n, m, M) == (ll)(c % M));
    }
    return 0;
}
