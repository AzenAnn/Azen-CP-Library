#include "../common.hpp"
#include "../../templates/02_ds/18_segment_tree_divide.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 8), T = rnd(1, 20), m = rnd(0, 15);
        SegTreeDivide sd(n, T);
        vector<array<int, 4>> es;
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1), l = rnd(0, T - 1), r = rnd(0, T - 1);
            if (l > r) swap(l, r);
            sd.add_edge(u, v, l, r);
            es.push_back({u, v, l, r});
        }
        sd.solve();
        for (int t = 0; t < T; t++) {
            vector<vector<int>> g(n);
            for (auto [u, v, l, r] : es)
                if (l <= t && t <= r) g[u].push_back(v), g[v].push_back(u);
            vector<int> col(n, -1);
            int comps = 0;
            bool bip = true;
            for (int s = 0; s < n; s++) {
                if (col[s] != -1) continue;
                comps++;
                col[s] = 0;
                vector<int> q = {s};
                for (size_t h = 0; h < q.size(); h++)
                    for (int v : g[q[h]]) {
                        if (col[v] == -1) col[v] = col[q[h]] ^ 1, q.push_back(v);
                        else if (col[v] == col[q[h]]) bip = false;
                    }
            }
            CHECK(sd.comps[t] == comps);
            CHECK((bool)sd.bip[t] == bip);
        }
    }
    return 0;
}
