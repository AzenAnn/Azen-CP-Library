#include "../common.hpp"
#include "../../templates/03_graph/10_km.hpp"

int main() {
    for (int it = 0; it < 1000; it++) {
        int n = rnd(0, 6), m = rnd(n, 7);
        vector<vector<ll>> w(n, vector<ll>(m));
        ll V = rnd(0, 1) ? 5 : 1000000000;
        for (auto &r : w)
            for (auto &x : r) x = rnd(-V, V);
        // 暴力：枚举右边选哪 n 个点、怎么排列
        vector<int> id(m);
        iota(id.begin(), id.end(), 0);
        ll best = LLONG_MIN;
        do {
            ll s = 0;
            for (int i = 0; i < n; i++) s += w[i][id[i]];
            best = max(best, s);
        } while (next_permutation(id.begin(), id.end()));
        if (n == 0) best = 0;
        vector<int> ml;
        ll got = km_max_weight(w, &ml);
        CHECK(got == best);
        set<int> st;
        ll s = 0;
        for (int i = 0; i < n; i++) {
            CHECK(ml[i] >= 0 && ml[i] < m);
            st.insert(ml[i]), s += w[i][ml[i]];
        }
        CHECK((int)st.size() == n && s == got);
    }
    return 0;
}
