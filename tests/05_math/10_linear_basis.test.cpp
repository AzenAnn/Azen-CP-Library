#include "../common.hpp"
#include "../../templates/05_math/10_linear_basis.hpp"

int main() {
    for (int it = 0; it < 2000; it++) {
        int n = rnd(1, 10);
        auto a = rnd_vec(n, 0, 63);
        if (it % 3 == 0)
            for (auto &x : a) x = rnd(0, (1LL << 59) - 1) & ~0xffffffffffLL ^ rnd(0, 15);
        LinearBasis lb;
        for (ll x : a) lb.insert(x);
        set<ll> vals;   // 所有非空子集的异或值
        for (int mask = 1; mask < (1 << n); mask++) {
            ll x = 0;
            for (int i = 0; i < n; i++)
                if (mask >> i & 1) x ^= a[i];
            vals.insert(x);
        }
        CHECK(lb.max_xor() == *vals.rbegin());
        CHECK(lb.min_xor() == *vals.begin());
        ll init = rnd(0, 63), best = init;
        for (ll v : vals) best = max(best, init ^ v);
        CHECK(lb.max_xor(init) == best);
        vector<ll> sorted(vals.begin(), vals.end());
        for (int k = 1; k <= (int)sorted.size() + 1; k++) CHECK(lb.kth(k) == (k <= (int)sorted.size() ? sorted[k - 1] : -1));
        for (int q = 0; q < 20; q++) {
            ll x = rnd(0, 63);
            CHECK(lb.contains(x) == (x == 0 || vals.count(x)));
        }
    }
    return 0;
}
