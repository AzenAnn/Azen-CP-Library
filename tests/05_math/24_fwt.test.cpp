#include "../common.hpp"
#include "../../templates/05_math/24_fwt.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int k = rnd(0, 7), n = 1 << k;
        ll p = rnd(0, 1) ? 998244353 : (rnd(1, 500) * 2 + 1);
        vector<ll> a(n), b(n);
        for (auto &x : a) x = rnd(0, p - 1);
        for (auto &x : b) x = rnd(0, p - 1);
        for (char op : {'|', '&', '^'}) {
            vector<ll> c(n, 0);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    int t = op == '|' ? (i | j) : op == '&' ? (i & j) : (i ^ j);
                    c[t] = (c[t] + a[i] * b[j]) % p;
                }
            CHECK(fwt_convolve(a, b, op, p) == c);
        }
    }
    return 0;
}
