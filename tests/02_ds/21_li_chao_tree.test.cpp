#include "../common.hpp"
#include "../../templates/02_ds/21_li_chao_tree.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        ll lo = rnd(-1000000000, 0), hi = lo + rnd(0, 2000000000);
        if (it % 3 == 0) lo = rnd(-20, 0), hi = lo + rnd(0, 40);   // 小范围，频繁命中边界
        LiChaoMin lc(lo, hi);
        vector<array<ll, 4>> segs;   // k, b, xl, xr
        for (int q = 0; q < 200; q++) {
            if (rnd(0, 2)) {
                ll k = rnd(-1000, 1000), b = rnd(-1000000000, 1000000000);
                if (rnd(0, 1)) lc.insert_line(k, b), segs.push_back({k, b, lo, hi});
                else {
                    ll xl = rnd(lo, hi), xr = rnd(lo, hi);
                    if (xl > xr) swap(xl, xr);
                    lc.insert_segment(k, b, xl, xr), segs.push_back({k, b, xl, xr});
                }
            } else {
                ll x = rnd(0, 3) ? rnd(lo, hi) : (rnd(0, 1) ? lo : hi);
                ll best = LLONG_MAX;
                for (auto [k, b, xl, xr] : segs)
                    if (xl <= x && x <= xr) best = min(best, k * x + b);
                CHECK(lc.query(x) == best);
            }
        }
    }
    return 0;
}
