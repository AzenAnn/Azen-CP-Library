#include "../common.hpp"
#include "../../templates/08_geometry/01_geo_basic.hpp"
#include "../../templates/08_geometry/02_convex_hull.hpp"

int main() {
    for (int it = 0; it < 3000; it++) {
        int n = rnd(1, 12);
        vector<Pt> pts(n);
        for (auto &p : pts) p = Pt(rnd(0, 6), rnd(0, 6));
        auto h = convex_hull(pts);
        // 暴力：p 是凸包顶点 ⇔ p 不在其他点构成的任何三角形（含边）内，也不在任何两点之间的线段上
        set<Pt> uniq(pts.begin(), pts.end());
        vector<Pt> u(uniq.begin(), uniq.end());
        set<Pt> expect;
        for (auto &p : u) {
            bool inside = false;
            for (auto &a : u)
                for (auto &b : u) {
                    if (a == p || b == p || a == b) continue;
                    if (on_segment(p, a, b)) inside = true;
                    for (auto &c : u) {
                        if (c == p || c == a || c == b || orient(a, b, c) == 0) continue;
                        ll s1 = orient(a, b, p), s2 = orient(b, c, p), s3 = orient(c, a, p);
                        if ((s1 >= 0 && s2 >= 0 && s3 >= 0) || (s1 <= 0 && s2 <= 0 && s3 <= 0)) inside = true;
                    }
                }
            if (!inside) expect.insert(p);
        }
        CHECK(set<Pt>(h.begin(), h.end()) == expect && h.size() == expect.size());
        for (size_t i = 0; i < h.size() && h.size() >= 3; i++) CHECK(orient(h[i], h[(i + 1) % h.size()], h[(i + 2) % h.size()]) > 0);
        if (h.size() >= 3) {
            for (auto &p : pts) {   // 所有点都在凸包内（含边界）
                bool ok = true;
                for (size_t i = 0; i < h.size(); i++) ok &= orient(h[i], h[(i + 1) % h.size()], p) >= 0;
                CHECK(ok);
            }
            double per = 0;
            for (size_t i = 0; i < h.size(); i++) per += hypot(h[(i + 1) % h.size()].x - h[i].x, h[(i + 1) % h.size()].y - h[i].y);
            CHECK(fabs(hull_perimeter(h) - per) < 1e-9);
        }
    }
    return 0;
}
