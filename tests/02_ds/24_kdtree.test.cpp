#include "../common.hpp"
#include "../../templates/02_ds/24_kdtree.hpp"

int main() {
    for (int it = 0; it < 400; it++) {
        int n = rnd(0, 60);
        ll C = rnd(0, 1) ? 10 : 1000000000;
        vector<KDTree::Pt> pts(n);
        for (int i = 0; i < n; i++) pts[i] = {rnd(-C, C), rnd(-C, C), rnd(-5, 5), i};
        KDTree kd(pts);
        for (int q = 0; q < 50; q++) {
            ll x = rnd(-C, C), y = rnd(-C, C);
            int skip = n ? rnd(-1, n - 1) : -1;
            ll best = LLONG_MAX;
            for (auto &p : pts)
                if (p.id != skip) best = min(best, (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
            CHECK(kd.nearest(x, y, skip) == best);
            ll x1 = rnd(-C, C), x2 = rnd(-C, C), y1 = rnd(-C, C), y2 = rnd(-C, C);
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            ll s = 0;
            for (auto &p : pts)
                if (x1 <= p.x && p.x <= x2 && y1 <= p.y && p.y <= y2) s += p.w;
            CHECK(kd.rect_sum(x1, x2, y1, y2) == s);
        }
    }
    return 0;
}
