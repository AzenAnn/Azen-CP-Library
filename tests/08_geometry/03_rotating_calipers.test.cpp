#include "../common.hpp"
#include "../../templates/08_geometry/01_geo_basic.hpp"
#include "../../templates/08_geometry/02_convex_hull.hpp"
#include "../../templates/08_geometry/03_rotating_calipers.hpp"

int main() {
    for (int it = 0; it < 3000; it++) {
        int n = rnd(1, 30);
        vector<Pt> pts(n);
        ll R = it % 2 ? 5 : 1000000;
        for (auto &p : pts) p = Pt(rnd(-R, R), rnd(-R, R));
        ll best = 0;
        for (auto &a : pts)
            for (auto &b : pts) best = max(best, (a - b).norm2());
        CHECK(hull_diameter2(pts) == best);
    }
    return 0;
}
