#include "../common.hpp"
#include "../../templates/05_math/02_gcd.hpp"

int main() {
    for (int it = 0; it < 5000; it++) {
        ll a = rnd(0, 1e9), b = rnd(0, 1e9), x, y;
        if (it % 3 == 0) a = rnd(0, 30), b = rnd(0, 30);
        ll g = exgcd(a, b, x, y);
        CHECK(g == __gcd(a, b));
        CHECK((__int128)a * x + (__int128)b * y == g);
    }
    for (int it = 0; it < 3000; it++) {
        ll m = rnd(1, 40), a = rnd(-50, 50), b = rnd(-50, 50);
        ll first = -1, cnt = 0;
        for (ll x = 0; x < m; x++)
            if (((a * x - b) % m + m) % m == 0) cnt++, first = first == -1 ? x : first;
        auto [x, period] = linear_congruence(a, b, m);
        CHECK(x == first);
        if (first != -1) CHECK(period * cnt == m);
    }
    return 0;
}
