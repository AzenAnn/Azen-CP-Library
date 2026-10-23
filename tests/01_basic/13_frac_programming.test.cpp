#include "../common.hpp"
#include "../../templates/01_basic/13_frac_programming.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(1, 10), k = rnd(1, n);
        vector<double> a(n), b(n);
        for (int i = 0; i < n; i++) a[i] = rnd(-20, 50), b[i] = rnd(1, 30);
        double best = -1e18;
        for (int s = 0; s < (1 << n); s++) {
            if (__builtin_popcount(s) != k) continue;
            double sa = 0, sb = 0;
            for (int i = 0; i < n; i++)
                if (s >> i & 1) sa += a[i], sb += b[i];
            best = max(best, sa / sb);
        }
        CHECK(fabs(frac_choose_k(a, b, k) - best) < 1e-6);
        CHECK(fabs(frac_choose_k_dinkelbach(a, b, k) - best) < 1e-9);
    }
    return 0;
}
