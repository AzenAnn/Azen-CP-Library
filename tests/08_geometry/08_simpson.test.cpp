#include "../common.hpp"
#include "../../templates/08_geometry/01_geo_basic.hpp"
#include "../../templates/08_geometry/07_circle.hpp"
#include "../../templates/08_geometry/08_simpson.hpp"

double rd(double l, double r) { return l + (r - l) * uniform_real_distribution<double>(0, 1)(test_rng); }

int main() {
    const double PI = acos(-1.0);
    // 1. 已知积分
    CHECK(fabs(simpson_integrate([](double x) { return sin(x); }, 0, PI) - 2) < 1e-8);
    CHECK(fabs(simpson_integrate([](double x) { return exp(x); }, 0, 2) - (exp(2) - 1)) < 1e-8);
    CHECK(fabs(simpson_integrate([](double x) { return 1 / x; }, 1, 100) - log(100)) < 1e-7);
    CHECK(fabs(simpson_integrate([](double x) { return sqrt(max(0.0, 1 - x * x)); }, -1, 1) - PI / 2) < 1e-7);
    for (int it = 0; it < 100; it++) {   // 三次多项式
        double a = rd(-3, 3), b = rd(-3, 3), c = rd(-3, 3), d = rd(-3, 3), l = rd(-5, 0), r = rd(0, 5);
        auto F = [&](double x) { return a * x * x * x * x / 4 + b * x * x * x / 3 + c * x * x / 2 + d * x; };
        double got = simpson_integrate([&](double x) { return a * x * x * x + b * x * x + c * x + d; }, l, r);
        CHECK(fabs(got - (F(r) - F(l))) < 1e-7);
    }
    // 2. 圆的面积并：与细分的中点法数值积分对比
    for (int it = 0; it < 60; it++) {
        int n = rnd(1, 5);
        vector<Circle> cs;
        for (int i = 0; i < n; i++) cs.push_back({Pd(rd(-4, 4), rd(-4, 4)), rd(0.3, 3)});
        if (n >= 2 && it % 5 == 0) cs[1] = cs[0];   // 完全相同的圆
        int N = 200000;
        double l = -8, r = 8, h = (r - l) / N, num = 0;
        for (int i = 0; i < N; i++) {
            double x = l + (i + 0.5) * h;
            vector<pair<double, double>> seg;
            for (auto &c : cs) {
                double t = c.r * c.r - (x - c.c.x) * (x - c.c.x);
                if (t > 0) seg.push_back({c.c.y - sqrt(t), c.c.y + sqrt(t)});
            }
            sort(seg.begin(), seg.end());
            double lo = -1e18, hi = -1e18;
            for (auto [a, b] : seg) {
                if (a > hi) num += (hi - lo) * h, lo = a, hi = b;
                else hi = max(hi, b);
            }
            num += (hi - lo) * h;
        }
        CHECK(fabs(circle_union_area(cs) - num) < 1e-4);
    }
    return 0;
}
