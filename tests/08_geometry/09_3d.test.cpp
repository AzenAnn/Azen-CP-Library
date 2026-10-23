#include "../common.hpp"
#include "../../templates/08_geometry/09_3d.hpp"

double rd(double l, double r) { return l + (r - l) * uniform_real_distribution<double>(0, 1)(test_rng); }

int main() {
    // 1. 凸包的面与暴力（所有其他点都在同一侧的三角形）完全一致
    for (int it = 0; it < 300; it++) {
        int n = rnd(4, 9);
        vector<P3> pts(n);
        for (auto &q : pts) q = P3(rd(-10, 10), rd(-10, 10), rd(-10, 10));
        Hull3D h(pts, 0);
        set<array<int, 3>> got, want;
        for (auto f : h.faces) sort(f.begin(), f.end()), got.insert(f);
        for (int a = 0; a < n; a++)
            for (int b = a + 1; b < n; b++)
                for (int c = b + 1; c < n; c++) {
                    int pos = 0, neg = 0;
                    for (int d = 0; d < n; d++)
                        if (d != a && d != b && d != c) (mixed(pts[a], pts[b], pts[c], pts[d]) > 0 ? pos : neg)++;
                    if (!pos || !neg) want.insert({a, b, c});
                }
        CHECK(got == want);
        for (auto [a, b, c] : h.faces)   // 朝外：其他点都在面的内侧
            for (int d = 0; d < n; d++) CHECK(mixed(h.p[a], h.p[b], h.p[c], h.p[d]) <= 1e-9);
        // 体积：凸包是凸的，以任一内部点（重心）剖分成四面体，体积应一致
        P3 g;
        for (auto &q : pts) g = g + q * (1.0 / n);
        double v = 0;
        for (auto [a, b, c] : h.faces) v += mixed(g, pts[a], pts[b], pts[c]) / 6;
        CHECK(fabs(v - h.volume()) < 1e-6);
    }
    // 2. 立方体（含大量共面的点和内部点）：体积 = s³，表面积 = 6s²
    for (int it = 0; it < 20; it++) {
        double s = rd(1, 10);
        vector<P3> pts;
        for (int m = 0; m < 8; m++) pts.push_back(P3(m & 1 ? s : 0, m & 2 ? s : 0, m & 4 ? s : 0));
        for (int i = 0; i < 200; i++) {
            P3 q(rd(0, s), rd(0, s), rd(0, s));
            int f = rnd(0, 5);   // 一部分点放在表面上
            if (f < 3) (f == 0 ? q.x : f == 1 ? q.y : q.z) = rnd(0, 1) ? s : 0;
            pts.push_back(q);
        }
        Hull3D h(pts);
        CHECK(fabs(h.volume() - s * s * s) < 1e-5 * s * s * s);
        CHECK(fabs(h.area() - 6 * s * s) < 1e-5 * s * s);
    }
    // 3. 平面与直线
    for (int it = 0; it < 200; it++) {
        P3 a(rd(-5, 5), rd(-5, 5), rd(-5, 5)), b(rd(-5, 5), rd(-5, 5), rd(-5, 5)), c(rd(-5, 5), rd(-5, 5), rd(-5, 5));
        P3 p(rd(-5, 5), rd(-5, 5), rd(-5, 5)), q(rd(-5, 5), rd(-5, 5), rd(-5, 5));
        P3 nrm = (b - a).cross(c - a);
        if (nrm.len() < 1e-3 || fabs(nrm.dot(q - p)) < 1e-3) continue;
        P3 x = line_plane_intersection(p, q, a, b, c);
        CHECK(fabs(dist_point_plane(x, a, b, c)) < 1e-7);
        CHECK((x - p).cross(q - p).len() < 1e-6 * max(1.0, (x - p).len()));   // 交点在直线上
        double d = dist_point_plane(p, a, b, c);   // 沿法向量走回平面
        P3 foot = p - nrm * (d / nrm.len());
        CHECK(fabs(dist_point_plane(foot, a, b, c)) < 1e-7);
    }
    return 0;
}
