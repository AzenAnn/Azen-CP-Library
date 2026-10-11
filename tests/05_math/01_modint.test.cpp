#include "../common.hpp"
#include "../../templates/05_math/01_modint.hpp"

int main() {
    for (int it = 0; it < 2000; it++) {
        ll m = rnd(1, 50), a = rnd(-100, 100), e = rnd(0, 12), r = 1 % m;
        for (int i = 0; i < e; i++) r = r * (((a % m) + m) % m) % m;
        CHECK(qpow(a, e, m) == r);
    }
    ll bigm = (ll)1e18 + 9;   // 大模数：检查 __int128 乘法
    CHECK(qpow(2, 0, bigm) == 1 && qpow(bigm - 1, 2, bigm) == 1);
    const int P = 998244353;
    for (int it = 0; it < 2000; it++) {
        ll x = rnd(-1e12, 1e12), y = rnd(-1e12, 1e12);
        ll xm = (x % P + P) % P, ym = (y % P + P) % P;
        mint a = x, b = y;
        CHECK((a + b).v == (xm + ym) % P);
        CHECK((a - b).v == (xm - ym + P) % P);
        CHECK((a * b).v == xm * ym % P);
        CHECK((-a).v == (P - xm) % P);
        if (ym) CHECK((a / b) * b == a && b * b.inv() == mint(1));
        CHECK(a.pow(3) == a * a * a);
    }
    stringstream ss("-1");
    mint z;
    ss >> z;
    CHECK(z.v == P - 1);
    return 0;
}
