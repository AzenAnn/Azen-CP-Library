#include "../common.hpp"
#include "../../templates/05_math/27_lagrange_interp.hpp"

int main() {
    const ll P = 998244353;
    for (int it = 0; it < 500; it++) {
        int n = rnd(1, 15);
        auto coef = rnd_vec(n, 0, P - 1);   // 随机多项式
        auto f = [&](ll x) {
            ll r = 0;
            x = (x % P + P) % P;
            for (int i = n - 1; i >= 0; i--) r = (r * x + coef[i]) % P;
            return r;
        };
        set<ll> used;
        vector<ll> xs, ys;
        while ((int)xs.size() < n) {
            ll x = rnd(-1000, 1000);
            if (used.insert(x).second) xs.push_back(x), ys.push_back(f(x));
        }
        vector<ll> cy(n);
        for (int i = 0; i < n; i++) cy[i] = f(i);
        for (int q = 0; q < 10; q++) {
            ll x = rnd(0, 1) ? rnd(-100, 100) : rnd(0, 1000000000000000000LL);
            CHECK(lagrange_eval(xs, ys, x, P) == f(x));
            if (x >= 0) CHECK(lagrange_consecutive(cy, x, P) == f(x));
        }
    }
    for (int k = 0; k <= 6; k++)
        for (ll n = 0; n <= 60; n++) {
            ll s = 0;
            for (ll i = 1; i <= n; i++) s = (s + lag_pow(i, k, P)) % P;
            CHECK(power_sum(n, k, P) == s);
        }
    CHECK(power_sum(1000000000, 1, P) == 1000000000LL % P * 1000000001 % P * ((P + 1) / 2) % P);
    return 0;
}
