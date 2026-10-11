#include "../common.hpp"
#include "../../templates/05_math/06_euler_phi.hpp"

int main() {
    auto ph = phi_sieve(3000);
    for (int n = 1; n <= 3000; n++) {
        int c = 0;
        for (int i = 1; i <= n; i++) c += __gcd(i, n) == 1;
        CHECK(ph[n] == c && phi(n) == c);
    }
    CHECK(phi(1000000007LL * 3) == 2LL * 1000000006);
    for (int it = 0; it < 3000; it++) {
        ll a = rnd(0, 100), m = rnd(1, 100), b = rnd(0, 1e18);
        if (it % 2) b = rnd(0, 20);
        ll r = 1 % m, base = a % m;   // 直接快速幂
        for (ll e = b; e; e >>= 1, base = (__int128)base * base % m)
            if (e & 1) r = (__int128)r * base % m;
        CHECK(pow_big_exponent(a, to_string(b), m) == r);
    }
    return 0;
}
