#include "../common.hpp"
#include "../../templates/05_math/12_number_block.hpp"

int main() {
    for (ll n = 1; n <= 2000; n++) {
        ll s = 0;
        for (ll i = 1; i <= n; i++) s += n / i;
        CHECK(sum_floor(n) == s);
        ll cnt = 0, prev_r = 0;
        for_each_block(n, [&](ll l, ll r, ll q) {
            CHECK(l == prev_r + 1);
            for (ll i = l; i <= r; i++) CHECK(n / i == q);
            prev_r = r, cnt++;
        });
        CHECK(prev_r == n && cnt <= 2 * sqrt(n) + 1);
    }
    for (int it = 0; it < 2000; it++) {
        ll n = rnd(1, 300), k = rnd(1, 300), s = 0;
        for (ll i = 1; i <= n; i++) s += k % i;
        CHECK(sum_mod(n, k) == s);
        ll m = rnd(1, 300), s2 = 0, t2 = 0;
        for (ll i = 1; i <= min(n, m); i++) s2 += (n / i) * (m / i);
        for_each_block2(n, m, [&](ll l, ll r, ll qa, ll qb) {
            for (ll i = l; i <= r; i++) CHECK(n / i == qa && m / i == qb);
            t2 += (r - l + 1) * qa * qb;
        });
        CHECK(s2 == t2);
    }
    CHECK(sum_mod(1000000000, 1000000000) > 0);
    return 0;
}
