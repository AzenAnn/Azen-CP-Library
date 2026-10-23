#include "../common.hpp"
#include "../../templates/03_graph/21_block_forest.hpp"

int main() {
    for (int it = 0; it < 800; it++) {
        int n = rnd(1, 9), m = rnd(0, 14);
        vector<pair<int, int>> es;
        for (int i = 0; i < m; i++) es.push_back({(int)rnd(0, n - 1), (int)rnd(0, n - 1)});
        BlockForest bf(n, es);
        int N = n + bf.cnt;
        // 1. 结果是森林：边数 = 点数 − 连通块数（只算有边的部分）
        int E = 0;
        for (int x = 0; x < N; x++) E += bf.tree[x].size();
        E /= 2;
        vector<int> comp(N, -1);
        int C = 0;
        for (int x = 0; x < N; x++) {
            if (comp[x] != -1) continue;
            vector<int> q = {x};
            comp[x] = C;
            for (size_t h = 0; h < q.size(); h++)
                for (int y : bf.tree[q[h]])
                    if (comp[y] == -1) comp[y] = C, q.push_back(y);
            C++;
        }
        CHECK(E == N - C);
        // 2. 必经点：u、v 连通时，删去 w 后 u、v 不连通 ⇔ w 是树上 u→v 路径的中间圆点
        auto connected = [&](int u, int v, int ban) {
            vector<vector<int>> g(n);
            for (auto [a, b] : es)
                if (a != ban && b != ban) g[a].push_back(b), g[b].push_back(a);
            vector<bool> vis(n);
            vector<int> q = {u};
            vis[u] = true;
            for (size_t h = 0; h < q.size(); h++)
                for (int y : g[q[h]])
                    if (!vis[y]) vis[y] = true, q.push_back(y);
            return (bool)vis[v];
        };
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++) {
                if (u == v) continue;
                bool con = connected(u, v, -1);
                CHECK(con == (comp[u] == comp[v]));
                if (!con) continue;
                vector<int> par(N, -1), q = {u};   // 树上路径
                vector<bool> vis(N);
                vis[u] = true;
                for (size_t h = 0; h < q.size(); h++)
                    for (int y : bf.tree[q[h]])
                        if (!vis[y]) vis[y] = true, par[y] = q[h], q.push_back(y);
                set<int> on_path;
                for (int x = par[v]; x != u; x = par[x])
                    if (x < n) on_path.insert(x);
                for (int w = 0; w < n; w++)
                    if (w != u && w != v) CHECK(!connected(u, v, w) == (bool)on_path.count(w));
            }
    }
    return 0;
}
