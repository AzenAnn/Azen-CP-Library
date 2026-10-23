#include "../common.hpp"
#include "../../templates/08_geometry/01_geo_basic.hpp"
#include "../../templates/08_geometry/07_circle.hpp"

double rd(double l, double r) { return l + (r - l) * uniform_real_distribution<double>(0, 1)(test_rng); }

// 数值积分：竖直扫描线上"属于区域"的长度，中点法
template <class F>
double integrate_x(double l, double r, F len, int N = 20000) {
    double h = (r - l) / N, s = 0;
    for (int i = 0; i < N; i++) s += len(l + (i + 0.5) * h);
    return s * h;
}
pair<double, double> circle_y(const Circle &C, double x) {   // 圆在竖线 x 上的区间，没有时 l > r
    double t = C.r * C.r - (x - C.c.x) * (x - C.c.x);
    if (t < 0) return {1, 0};
    return {C.c.y - sqrt(t), C.c.y + sqrt(t)};
}

int main() {
    for (int it = 0; it < 300; it++) {
        Circle A{Pd(rd(-5, 5), rd(-5, 5)), rd(0.5, 4)}, B{Pd(rd(-5, 5), rd(-5, 5)), rd(0.5, 4)};
        if (it % 10 == 0) B.c = A.c + Pd(rd(-0.5, 0.5), rd(-0.5, 0.5));   // 制造内含
        // 1. 圆与直线
        Pd a(rd(-8, 8), rd(-8, 8)), b(rd(-8, 8), rd(-8, 8));
        auto pts = circle_line_inter(A, a, b);
        double h = fabs((b - a).cross(A.c - a)) / (b - a).len();
        CHECK(pts.size() == (h < A.r ? 2u : 0u));
        for (auto p : pts) CHECK(fabs((p - A.c).len() - A.r) < 1e-7 && fabs((b - a).cross(p - a)) < 1e-7);
        // 2. 两圆交点
        auto q = circle_circle_inter(A, B);
        double d = (A.c - B.c).len();
        CHECK(q.size() == ((d < A.r + B.r && d > fabs(A.r - B.r)) ? 2u : 0u));
        for (auto p : q) CHECK(fabs((p - A.c).len() - A.r) < 1e-6 && fabs((p - B.c).len() - B.r) < 1e-6);
        // 3. 相交面积：数值积分
        double num = integrate_x(-10, 10, [&](double x) {
            auto [l1, r1] = circle_y(A, x);
            auto [l2, r2] = circle_y(B, x);
            return max(0.0, min(r1, r2) - max(l1, l2));
        });
        CHECK(fabs(circle_circle_area(A, B) - num) < 1e-3);
        // 4. 切线
        Pd p(rd(-10, 10), rd(-10, 10));
        auto ts = tangent_points(A, p);
        CHECK(ts.size() == ((p - A.c).len() > A.r ? 2u : 0u));
        for (auto t : ts) CHECK(fabs((t - A.c).len() - A.r) < 1e-7 && fabs((t - A.c).dot(t - p)) < 1e-6);
        // 5. 外接圆
        Pd x(rd(-5, 5), rd(-5, 5)), y(rd(-5, 5), rd(-5, 5)), z(rd(-5, 5), rd(-5, 5));
        if (fabs((y - x).cross(z - x)) > 1) {
            auto C = circumcircle(x, y, z);
            CHECK(fabs((x - C.c).len() - C.r) < 1e-6 && fabs((y - C.c).len() - C.r) < 1e-6 && fabs((z - C.c).len() - C.r) < 1e-6);
        }
        // 6. 圆与多边形：围绕 o 的星形多边形，相邻角度差 < π 保证 o 在内部、多边形简单且逆时针
        int n = rnd(3, 8);
        Pd o(rd(-2, 2), rd(-2, 2));
        vector<double> ang(n);
        for (int i = 0; i < n; i++) ang[i] = (i + rd(0, 0.4)) * 2 * acos(-1.0) / n;
        vector<Pd> poly;
        for (double t : ang) {
            double rr = rd(0.5, 6);
            poly.push_back(o + Pd(cos(t), sin(t)) * rr);
        }
        double area = integrate_x(-10, 10, [&](double xx) {
            vector<double> ys;
            for (int i = 0; i < n; i++) {
                Pd u = poly[i], v = poly[(i + 1) % n];
                if ((u.x > xx) != (v.x > xx)) ys.push_back(u.y + (v.y - u.y) * (xx - u.x) / (v.x - u.x));
            }
            sort(ys.begin(), ys.end());
            auto [cl, cr] = circle_y(A, xx);
            double s = 0;
            for (size_t i = 0; i + 1 < ys.size(); i += 2) s += max(0.0, min(cr, ys[i + 1]) - max(cl, ys[i]));
            return s;
        });
        CHECK(fabs(circle_polygon_area(A, poly) - area) < 2e-3);
        reverse(poly.begin(), poly.end());
        CHECK(fabs(circle_polygon_area(A, poly) + area) < 2e-3);
    }
    return 0;
}
