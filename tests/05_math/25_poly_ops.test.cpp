#include "../common.hpp"
#include "../../templates/05_math/25_poly_ops.hpp"

const ll P = poly::MOD;
vector<ll> naive_mul(const vector<ll> &a, const vector<ll> &b, int n) {   // mod x^n
    vector<ll> c(n, 0);
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < b.size() && i + j < (size_t)n; j++) c[i + j] = (c[i + j] + a[i] * b[j]) % P;
    return c;
}
vector<ll> rnd_poly(int n, bool c0_one = false, bool c0_zero = false) {
    vector<ll> a(n);
    for (auto &x : a) x = rnd(0, P - 1);
    if (n && c0_one) a[0] = 1;
    if (n && c0_zero) a[0] = 0;
    return a;
}

int main() {
    for (int it = 0; it < 60; it++) {
        int n = it < 40 ? rnd(1, 40) : rnd(100, 300);
        // 乘法
        auto a = rnd_poly(n), b = rnd_poly(rnd(1, n));
        CHECK(poly::mul(a, b) == naive_mul(a, b, a.size() + b.size() - 1));
        // 求逆
        a[0] = rnd(1, P - 1);
        auto ia = poly::inv(a, n);
        auto one = naive_mul(a, ia, n);
        CHECK(one[0] == 1 && count(one.begin() + 1, one.end(), 0) == n - 1);
        // ln 与 exp 互逆
        auto c = rnd_poly(n, true);
        CHECK(poly::exp(poly::ln(c, n), n) == c);
        auto d = rnd_poly(n, false, true);
        CHECK(poly::ln(poly::exp(d, n), n) == d);
        // 开根
        auto s = poly::sqrt(c, n);
        CHECK(naive_mul(s, s, n) == c);
        // 快速幂：与连乘对比
        ll k = rnd(0, 5);
        vector<ll> pw(n, 0);
        pw[0] = 1;
        for (int t = 0; t < k; t++) pw = naive_mul(pw, c, n);
        CHECK(poly::pow(c, k, n) == pw);
        // 带余除法
        auto A = rnd_poly(rnd(1, n)), B = rnd_poly(rnd(1, n));
        B.back() = rnd(1, P - 1);
        auto [q, r] = poly::divmod(A, B);
        auto qb = naive_mul(q, B, A.size());
        for (size_t i = 0; i < A.size(); i++) CHECK((qb[i] + (i < r.size() ? r[i] : 0)) % P == A[i]);
        CHECK(r.size() <= max<size_t>(1, B.size() - 1));
        if (A.size() >= B.size()) CHECK(q.size() == A.size() - B.size() + 1);
    }
    return 0;
}
