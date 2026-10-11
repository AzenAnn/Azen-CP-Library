#include "../common.hpp"
#include "../../templates/04_tree/05_dsu_on_tree.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 40);
        vector<vector<int>> g(n);
        vector<int> par(n, -1), col(n);
        for (int &c : col) c = rnd(1, 6);
        for (int v = 1; v < n; v++) {
            int u = rnd(max(0, v - 4), v - 1);
            g[u].push_back(v), g[v].push_back(u), par[v] = u;
        }
        auto ans = dsu_on_tree(g, col, 0);
        for (int u = 0; u < n; u++) {
            map<int, int> cnt;
            for (int v = 0; v < n; v++) {
                int x = v;
                while (x != -1 && x != u) x = par[x];
                if (x == u) cnt[col[v]]++;
            }
            int mx = 0;
            ll s = 0;
            for (auto [c, k] : cnt) mx = max(mx, k);
            for (auto [c, k] : cnt)
                if (k == mx) s += c;
            CHECK(ans[u] == s);
        }
    }
    return 0;
}
