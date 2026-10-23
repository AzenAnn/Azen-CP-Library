#include "../common.hpp"
#include "../../templates/03_graph/12_two_sat.hpp"

int main() {
    for (int it = 0; it < 2000; it++) {
        int n = rnd(1, 8), m = rnd(0, 15);
        TwoSat ts(n);
        vector<array<int, 4>> cl;
        for (int k = 0; k < m; k++) {
            int i = rnd(0, n - 1), j = rnd(0, n - 1), f = rnd(0, 1), g = rnd(0, 1);
            cl.push_back({i, f, j, g}), ts.add_clause(i, f, j, g);
        }
        auto ok = [&](int mask) {
            for (auto [i, f, j, g] : cl)
                if ((mask >> i & 1) != f && (mask >> j & 1) != g) return false;
            return true;
        };
        bool exist = false;
        for (int mask = 0; mask < (1 << n); mask++) exist |= ok(mask);
        CHECK(ts.satisfiable() == exist);
        if (exist) {
            int mask = 0;
            for (int i = 0; i < n; i++) mask |= ts.ans[i] << i;
            CHECK(ok(mask));
        }
    }
    return 0;
}
