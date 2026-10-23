#include "../common.hpp"
#include "../../templates/03_graph/20_general_match.hpp"

int main() {
    for (int it = 0; it < 2000; it++) {
        int n = rnd(1, 12), m = rnd(0, 25);
        Blossom bm(n);
        vector<vector<bool>> adj(n, vector<bool>(n));
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            bm.add_edge(u, v);
            if (u != v) adj[u][v] = adj[v][u] = true;
        }
        // 暴力：状压 DP，f[S] = 点集 S 内的最大匹配
        vector<int> f(1 << n, 0);
        for (int S = 1; S < (1 << n); S++) {
            int i = __builtin_ctz(S), R = S ^ (1 << i);
            f[S] = f[R];
            for (int j = 0; j < n; j++)
                if ((R >> j & 1) && adj[i][j]) f[S] = max(f[S], f[R ^ (1 << j)] + 1);
        }
        int got = bm.solve();
        CHECK(got == f[(1 << n) - 1]);
        int c = 0;
        for (int v = 0; v < n; v++)
            if (bm.match[v] != -1) {
                CHECK(bm.match[bm.match[v]] == v && adj[v][bm.match[v]]);
                c++;
            }
        CHECK(c == 2 * got);
    }
    return 0;
}
