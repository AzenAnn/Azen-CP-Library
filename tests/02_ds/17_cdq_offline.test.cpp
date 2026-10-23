#include "../common.hpp"
#include "../../templates/02_ds/17_cdq_offline.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(0, 40);
        vector<array<int, 3>> p(n);
        for (auto &x : p) x = {(int)rnd(1, 5), (int)rnd(1, 5), (int)rnd(-3, 3)};
        auto res = partial_order_3d(p);
        for (int i = 0; i < n; i++) {
            int c = 0;
            for (int j = 0; j < n; j++)
                if (j != i && p[j][0] <= p[i][0] && p[j][1] <= p[i][1] && p[j][2] <= p[i][2]) c++;
            CHECK(res[i] == c);
        }
        if (!n) continue;
        auto a = rnd_vec(n, -10, 10);
        vector<array<int, 3>> qs;
        for (int q = 0; q < 30; q++) {
            int l = rnd(0, n - 1), r = rnd(l + 1, n);
            qs.push_back({l, r, (int)rnd(1, r - l)});
        }
        auto ans = parallel_kth(a, qs);
        for (int q = 0; q < 30; q++) {
            vector<ll> s(a.begin() + qs[q][0], a.begin() + qs[q][1]);
            sort(s.begin(), s.end());
            CHECK(ans[q] == s[qs[q][2] - 1]);
        }
    }
    return 0;
}
