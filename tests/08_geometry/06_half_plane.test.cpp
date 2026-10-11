#include "../common.hpp"
#include "../../templates/08_geometry/01_geo_basic.hpp"
#include "../../templates/08_geometry/06_half_plane.hpp"

// 暴力：Sutherland-Hodgman 多边形裁剪，从一个大矩形开始，依次用每个半平面裁剪
vector<Pd> clip(const vector<Pd> &poly, const HalfPlane &h) {
    vector<Pd> res;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        Pd a = poly[i], b = poly[(i + 1) % n];
        double sa = h.v.cross(a - h.p), sb = h.v.cross(b - h.p);
        if (sa >= 0) res.push_back(a);
        if ((sa > 0 && sb < 0) || (sa < 0 && sb > 0)) res.push_back(a + (b - a) * (sa / (sa - sb)));
    }
    return res;
}
double area(const vector<Pd> &p) {
    double s = 0;
    for (size_t i = 0; i < p.size(); i++) s += p[i].cross(p[(i + 1) % p.size()]);
    return s / 2;
}

int main() {
    const double B = 100;
    for (int it = 0; it < 30000; it++) {
        vector<HalfPlane> hs;
        hs.push_back(HalfPlane(Pd(-B, -B), Pd(1, 0)));   // 边界框
        hs.push_back(HalfPlane(Pd(B, -B), Pd(0, 1)));
        hs.push_back(HalfPlane(Pd(B, B), Pd(-1, 0)));
        hs.push_back(HalfPlane(Pd(-B, B), Pd(0, -1)));
        int k = rnd(1, 8);
        for (int i = 0; i < k; i++) {
            Pd p(rnd(-50, 50), rnd(-50, 50)), v(rnd(-10, 10), rnd(-10, 10));
            if (fabs(v.x) + fabs(v.y) < 1e-9) continue;
            hs.push_back(HalfPlane(p, v));
        }
        vector<Pd> poly = {Pd(-B, -B), Pd(B, -B), Pd(B, B), Pd(-B, B)};
        for (size_t i = 4; i < hs.size(); i++) poly = clip(poly, hs[i]);
        double expect = poly.size() >= 3 ? area(poly) : 0;
        auto res = half_plane_intersection(hs);
        double got = res.size() >= 3 ? area(res) : 0;
        CHECK(fabs(got - expect) < 1e-6 * max(1.0, expect));
        for (auto &p : res)   // 交出的每个顶点都满足所有半平面
            for (auto &h : hs) CHECK(h.v.cross(p - h.p) > -1e-6);
    }
    return 0;
}
