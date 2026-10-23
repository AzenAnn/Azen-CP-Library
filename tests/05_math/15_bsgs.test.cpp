#include "../common.hpp"
#include "../../templates/05_math/15_bsgs.hpp"

int main() {
    for (ll p = 1; p <= 80; p++)
        for (ll a = 0; a < p; a++)
            for (ll b = 0; b < p; b++) {
                ll first = -1, cur = 1 % p;
                for (ll x = 0; x <= 2 * p + 5; x++) {
                    if (cur == b) { first = x; break; }
                    cur = cur * a % p;
                }
                CHECK(exbsgs(a, b, p) == first);
                if (__gcd(a, p) == 1) CHECK(bsgs(a, b, p) == first);
            }
    // 大模数
    ll p = 1000000007, a = 5, x = 123456789, b = 1;
    for (ll e = x, base = a; e; e >>= 1, base = base * base % p)
        if (e & 1) b = b * base % p;
    ll got = bsgs(a, b, p), chk = 1;
    for (ll e = got, base = a; e; e >>= 1, base = base * base % p)
        if (e & 1) chk = chk * base % p;
    CHECK(got != -1 && got <= x && chk == b);
    return 0;
}
