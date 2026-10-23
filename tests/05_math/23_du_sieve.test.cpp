#include "../common.hpp"
#include "../../templates/05_math/23_du_sieve.hpp"

int main() {
    // 与线性筛的前缀和对比（让 lim 很小，强制走递归部分）
    const int N = 2000000;
    vector<int> phi(N + 1), mu(N + 1), pr;
    vector<char> comp(N + 1);
    phi[1] = mu[1] = 1;
    for (ll i = 2; i <= N; i++) {
        if (!comp[i]) pr.push_back(i), phi[i] = i - 1, mu[i] = -1;
        for (int p : pr) {
            if (i * p > N) break;
            comp[i * p] = 1;
            if (i % p == 0) { phi[i * p] = phi[i] * p, mu[i * p] = 0; break; }
            phi[i * p] = phi[i] * (p - 1), mu[i * p] = -mu[i];
        }
    }
    vector<ll> sp(N + 1), sm(N + 1);
    for (int i = 1; i <= N; i++) sp[i] = sp[i - 1] + phi[i], sm[i] = sm[i - 1] + mu[i];
    DuSieve ds(1000);   // lim ≈ 100，大部分询问都走记忆化递归
    for (int it = 0; it < 300; it++) {
        ll n = it < 100 ? rnd(1, 300) : rnd(1, N);
        CHECK(ds.sum_phi(n) == sp[n]);
        CHECK(ds.sum_mu(n) == sm[n]);
    }
    // 大 n：两种 lim 下结果一致，且 Σμ 的已知值
    DuSieve big(2147483647LL);
    CHECK(big.sum_mu(1000000000) == -222);   // Mertens 函数 M(10^9) = -222
    for (ll n : {1000000000LL, 2147483647LL, 123456789LL}) CHECK(big.sum_phi(n) == DuSieve(n / 10).sum_phi(n));
    return 0;
}
