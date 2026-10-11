#include "../common.hpp"
#include "../../templates/03_graph/05_scc.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(1, 12), m = rnd(0, 25);
        SCC s(n);
        vector<vector<bool>> reach(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) reach[i][i] = true;
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            s.add_edge(u, v), reach[u][v] = true;
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (reach[i][k] && reach[k][j]) reach[i][j] = true;
        int cnt = s.run();
        set<int> ids(s.comp.begin(), s.comp.end());
        CHECK((int)ids.size() == cnt);
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++) CHECK((s.comp[u] == s.comp[v]) == (reach[u][v] && reach[v][u]));
        // 编号为逆拓扑序：DAG 中的边总是从大编号指向小编号
        auto h = s.dag();
        for (int a = 0; a < cnt; a++)
            for (int b : h[a]) CHECK(a > b);
    }
    return 0;
}
