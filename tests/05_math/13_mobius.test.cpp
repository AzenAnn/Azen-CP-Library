#include "../common.hpp"
#include "../../templates/05_math/13_mobius.hpp"

int main() {
    Mobius mo(2000);
    for (int n = 1; n <= 2000; n++) {   // 用定义检查 μ
        int x = n, k = 0, mu = 1;
        for (int p = 2; p * p <= x; p++)
            if (x % p == 0) {
                x /= p, k++;
                if (x % p == 0) mu = 0;
                while (x % p == 0) x /= p;
            }
        if (x > 1) k++;
        if (mu) mu = k % 2 ? -1 : 1;
        CHECK(mo.mu[n] == mu);
    }
    for (int it = 0; it < 500; it++) {
        ll a = rnd(1, 150), b = rnd(1, 150), k = rnd(1, 20), c = 0;
        for (ll x = 1; x <= a; x++)
            for (ll y = 1; y <= b; y++) c += __gcd(x, y) == k;
        CHECK(count_gcd_eq(mo, a, b, k) == c);
    }
    return 0;
}
