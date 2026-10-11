#include "../common.hpp"
#include "../../templates/08_geometry/01_geo_basic.hpp"
#include "../../templates/08_geometry/05_closest_pair.hpp"

int main() {
    for (int it = 0; it < 3000; it++) {
        int n = rnd(2, 60);
        ll R = it % 3 == 0 ? 3 : it % 3 == 1 ? 100 : 1000000000;
        vector<Pt> pts(n);
        for (auto &p : pts) p = Pt(rnd(-R, R), rnd(-R, R));
        ll best = LLONG_MAX;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) best = min(best, (pts[i] - pts[j]).norm2());
        CHECK(closest_pair2(pts) == best);
        CHECK(closest_pair2_sweep(pts) == best);
    }
    return 0;
}
