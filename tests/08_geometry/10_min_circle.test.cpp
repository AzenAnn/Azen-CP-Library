#include "../common.hpp"
#include "../../templates/08_geometry/01_geo_basic.hpp"
#include "../../templates/08_geometry/10_min_circle.hpp"

double rd(double l, double r) { return l + (r - l) * uniform_real_distribution<double>(0, 1)(test_rng); }

int main() {
    for (int it = 0; it < 1000; it++) {
        int n = rnd(1, 12);
        vector<Pd> pts(n);
        for (auto &q : pts) q = rnd(0, 3) ? Pd(rd(-10, 10), rd(-10, 10)) : Pd(rnd(-3, 3), rnd(-3, 3));   // 混入整点，制造重点、共线
        auto [o, r] = min_enclosing_circle(pts);
        for (auto &q : pts) CHECK((q - o).len() <= r + 1e-7);
        // 暴力：所有两点直径圆、三点外接圆中，能覆盖全部点的最小者
        double best = 1e18;
        auto test = [&](Pd c) {
            double rr = 0;
            for (auto &q : pts) rr = max(rr, (q - c).len());
            best = min(best, rr);
        };
        test(pts[0]);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                test((pts[i] + pts[j]) / 2);
                for (int k = j + 1; k < n; k++) {
                    Pd B = pts[j] - pts[i], C = pts[k] - pts[i];
                    double D = 2 * B.cross(C);
                    if (fabs(D) < 1e-9) continue;
                    test(pts[i] + Pd((C.y * B.norm2() - B.y * C.norm2()) / D, (B.x * C.norm2() - C.x * B.norm2()) / D));
                }
            }
        CHECK(fabs(r - best) < 1e-6);
    }
    return 0;
}
