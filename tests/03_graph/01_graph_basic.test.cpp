#include "../common.hpp"
#include "../../templates/03_graph/01_graph_basic.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 15), m = rnd(0, 25);
        vector<vector<int>> g(n);
        vector<vector<int>> d(n, vector<int>(n, 1e9));
        for (int i = 0; i < n; i++) d[i][i] = 0;
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            g[u].push_back(v), g[v].push_back(u);
            if (u != v) d[u][v] = d[v][u] = 1;
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        int s1 = rnd(0, n - 1), s2 = rnd(0, n - 1);
        auto dist = bfs(g, {s1, s2});
        for (int v = 0; v < n; v++) {
            int e = min(d[s1][v], d[s2][v]);
            CHECK(dist[v] == (e >= 1e9 ? -1 : e));
        }
        auto [comp, cnt] = components(g);
        set<int> ids(comp.begin(), comp.end());
        CHECK((int)ids.size() == cnt);
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++) CHECK((comp[u] == comp[v]) == (d[u][v] < 1e9));
    }
    vector<string> grid = {"..#.", ".#..", "...#", "#..."};
    auto gd = grid_bfs(grid, 0, 0);
    CHECK(gd[0][1] == 1 && gd[2][2] == 4 && gd[3][3] == 6 && gd[0][2] == -1 && gd[0][3] == 7);
    return 0;
}
