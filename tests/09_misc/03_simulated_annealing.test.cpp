#include "../common.hpp"
#include "../../templates/09_misc/03_simulated_annealing.hpp"

int main() {
    for (int it = 0; it < 30; it++) {
        int n = rnd(1, 10);
        vector<array<double, 3>> pts(n);
        for (auto &p : pts) p = {(double)rnd(-100, 100), (double)rnd(-100, 100), (double)rnd(1, 10)};
        auto energy = [&](double x, double y) {
            double s = 0;
            for (auto &q : pts) s += q[2] * hypot(x - q[0], y - q[1]);
            return s;
        };
        // 对照：Weiszfeld 迭代（加权费马点的经典算法），从每个点和重心出发取最优
        double best = 1e18;
        for (int s = 0; s <= n; s++) {
            double x = s < n ? pts[s][0] + 1e-3 : 0, y = s < n ? pts[s][1] + 1e-3 : 0;
            for (int k = 0; k < 20000; k++) {
                double nx = 0, ny = 0, den = 0;
                for (auto &q : pts) {
                    double d = max(hypot(x - q[0], y - q[1]), 1e-12);
                    nx += q[2] * q[0] / d, ny += q[2] * q[1] / d, den += q[2] / d;
                }
                x = nx / den, y = ny / den;
            }
            best = min(best, energy(x, y));
            if (s < n) best = min(best, energy(pts[s][0], pts[s][1]));
        }
        auto [x, y] = weighted_fermat_point(pts);
        CHECK(energy(x, y) <= best + 1e-6 * max(1.0, best));
    }
    return 0;
}
