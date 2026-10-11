#include "../common.hpp"
#include "../../templates/08_geometry/01_geo_basic.hpp"

// 暴力：用克莱姆法则（整数，精确）判断线段相交
bool brute_intersect(Pt a, Pt b, Pt c, Pt d) {
    Pt r = b - a, s = d - c;
    ll den = r.cross(s), tn = (c - a).cross(s), un = (c - a).cross(r);
    if (den != 0) {
        if (den < 0) den = -den, tn = -tn, un = -un;
        return 0 <= tn && tn <= den && 0 <= un && un <= den;
    }
    if ((c - a).cross(r) != 0) return false;   // 平行不共线
    // 共线：投影到坐标轴上看区间是否重叠（a == b 时 r 为零向量，也走这里）
    auto overlap = [](ll p1, ll p2, ll q1, ll q2) { return max(min(p1, p2), min(q1, q2)) <= min(max(p1, p2), max(q1, q2)); };
    if (a == b && c == d) return a == c;
    return overlap(a.x, b.x, c.x, d.x) && overlap(a.y, b.y, c.y, d.y);
}

int main() {
    for (int it = 0; it < 200000; it++) {
        auto rp = [] { return Pt(rnd(0, 4), rnd(0, 4)); };
        Pt a = rp(), b = rp(), c = rp(), d = rp();
        if (a == b && c == d) continue;
        if (a == b || c == d) {   // 退化为点：与 on_segment 对比
            CHECK(segments_intersect(a, b, c, d) == (a == b ? on_segment(a, c, d) : on_segment(c, a, b)));
            continue;
        }
        CHECK(segments_intersect(a, b, c, d) == brute_intersect(a, b, c, d));
    }
    // 直线交点、点到线段距离
    for (int it = 0; it < 10000; it++) {
        Pd a(rnd(-10, 10), rnd(-10, 10)), b(rnd(-10, 10), rnd(-10, 10)), c(rnd(-10, 10), rnd(-10, 10)), d(rnd(-10, 10), rnd(-10, 10));
        if (fabs((b - a).cross(d - c)) < 1e-9) continue;
        Pd p = line_intersection(a, b, c, d);
        CHECK(fabs((b - a).cross(p - a)) < 1e-6 && fabs((d - c).cross(p - c)) < 1e-6);
        double best = 1e18;   // 在线段上密集取点，距离的最小值
        for (int k = 0; k <= 2000; k++) best = min(best, (a + (b - a) * (k / 2000.0) - c).len());
        CHECK(dist_point_segment(c, a, b) <= best + 1e-9 && best - dist_point_segment(c, a, b) < 0.03);
    }
    // 多边形：随机星形多边形（按极角排序，保证是简单多边形），与"转角和"判断内外对比
    for (int it = 0; it < 2000; it++) {
        int n = rnd(3, 8);
        vector<Pt> poly;
        for (int i = 0; i < n; i++) {
            double ang = 2 * acos(-1.0) * i / n + 0.3;
            ll r = rnd(2, 6);
            poly.push_back(Pt(llround(r * cos(ang) * 2), llround(r * sin(ang) * 2)));
        }
        if (area2(poly) <= 0) continue;
        bool simple = true;   // 检查相邻顶点不重复、不相邻的边不相交
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                if (poly[i] == poly[j]) simple = false;
                if ((j == i + 1) || (i == 0 && j == n - 1)) continue;
                if (segments_intersect(poly[i], poly[(i + 1) % n], poly[j], poly[(j + 1) % n])) simple = false;
            }
        if (!simple) continue;
        ll s2 = 0;   // 鞋带公式（另一种写法）
        for (int i = 0; i < n; i++) s2 += (poly[i].x * poly[(i + 1) % n].y) - (poly[(i + 1) % n].x * poly[i].y);
        CHECK(area2(poly) == s2);
        for (ll x = -13; x <= 13; x++)
            for (ll y = -13; y <= 13; y++) {
                Pt p(x, y);
                bool on = false;
                for (int i = 0; i < n; i++) {
                    Pt a = poly[i], b = poly[(i + 1) % n];
                    if ((b - a).cross(p - a) == 0 && min(a.x, b.x) <= x && x <= max(a.x, b.x) && min(a.y, b.y) <= y && y <= max(a.y, b.y)) on = true;
                }
                int expect;
                if (on) expect = 0;
                else {
                    double w = 0;
                    for (int i = 0; i < n; i++) {
                        Pd a(poly[i].x - x, poly[i].y - y), b(poly[(i + 1) % n].x - x, poly[(i + 1) % n].y - y);
                        w += atan2(a.cross(b), a.dot(b));
                    }
                    expect = fabs(w) > 1 ? 1 : -1;
                }
                CHECK(point_in_polygon(p, poly) == expect);
            }
    }
    return 0;
}
