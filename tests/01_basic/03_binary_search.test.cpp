#include "../common.hpp"
#include "../../templates/01_basic/03_binary_search.hpp"

int main() {
    for (int it = 0; it < 2000; it++) {
        ll lo = rnd(-1000, 1000), hi = lo + rnd(1, 2000), t = rnd(lo + 1, hi);
        CHECK(first_true(lo, hi, [&](ll x) { return x >= t; }) == t);
        ll t2 = rnd(lo, hi - 1);
        CHECK(last_true(lo, hi, [&](ll x) { return x <= t2; }) == t2);
        // 整数三分：峰在 p
        ll L = rnd(-100, 100), R = L + rnd(0, 200), p = rnd(L, R);
        auto f = [&](ll x) { return -(x - p) * (x - p); };
        CHECK(ternary_max_int(L, R, f) == p);
    }
    double r = first_true_real(0, 10, [](double x) { return x * x >= 2; });
    CHECK(fabs(r - sqrt(2.0)) < 1e-9);
    double m = ternary_max(-10, 10, [](double x) { return -(x - 1.5) * (x - 1.5); });
    CHECK(fabs(m - 1.5) < 1e-6);
    // 二分答案示例：把数组分成至多 k 段，最小化最大段和
    vector<ll> a = {7, 2, 5, 10, 8};
    auto ok = [&](ll lim) {
        int seg = 1;
        ll s = 0;
        for (ll x : a) {
            if (x > lim) return false;
            if (s + x > lim) seg++, s = 0;
            s += x;
        }
        return seg <= 2;
    };
    CHECK(first_true(0, 32, ok) == 18);
    return 0;
}
