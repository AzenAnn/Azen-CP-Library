#include "../common.hpp"
#include "../../templates/09_misc/04_meet_in_middle.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(0, 16);
        auto a = rnd_vec(n, rnd(0, 1) ? 0 : -50, 100);
        ll S = rnd(-100, 800);
        ll cnt = 0, best = LLONG_MIN;
        for (int m = 0; m < (1 << n); m++) {
            ll s = 0;
            for (int i = 0; i < n; i++)
                if (m >> i & 1) s += a[i];
            if (s <= S) cnt++, best = max(best, s);
        }
        CHECK(count_subsets_leq(a, S) == cnt);
        CHECK(max_subset_leq(a, S) == best);
    }
    // n = 40 也能很快算完
    vector<ll> big(40);
    for (auto &x : big) x = rnd(1, 1000000000000LL);
    CHECK(count_subsets_leq(big, 0) == 1 && count_subsets_leq(big, LLONG_MAX / 2) == (1LL << 40));
    return 0;
}
