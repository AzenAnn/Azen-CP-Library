#include "../common.hpp"
#include "../../templates/02_ds/16_odt.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 30);
        auto a = rnd_vec(n, 0, 9);
        ODT odt(a);
        for (int op = 0; op < 100; op++) {
            int l = rnd(0, n - 1), r = rnd(l + 1, n), t = rnd(0, 3);
            if (t == 0) {
                ll v = rnd(0, 9);
                odt.assign(l, r, v);
                for (int i = l; i < r; i++) a[i] = v;
            } else if (t == 1) {
                ll x = rnd(0, 5);
                odt.add(l, r, x);
                for (int i = l; i < r; i++) a[i] += x;
            } else if (t == 2) {
                int k = rnd(1, r - l);
                vector<ll> v(a.begin() + l, a.begin() + r);
                sort(v.begin(), v.end());
                CHECK(odt.kth(l, r, k) == v[k - 1]);
            } else {
                ll e = rnd(0, 5), mod = rnd(1, 1000), s = 0;
                for (int i = l; i < r; i++) {
                    ll p = 1 % mod;
                    for (int j = 0; j < e; j++) p = p * (a[i] % mod) % mod;
                    s = (s + p) % mod;
                }
                CHECK(odt.pow_sum(l, r, e, mod) == s);
            }
        }
    }
    return 0;
}
