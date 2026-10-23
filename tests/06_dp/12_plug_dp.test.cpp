#include "../common.hpp"
#include "../../templates/06_dp/12_plug_dp.hpp"

int main() {
    for (int it = 0; it < 400; it++) {
        int n = rnd(1, 5), m = rnd(1, 5);
        if (n * m > 20) m = 20 / n;
        vector<string> g(n, string(m, '.'));
        for (auto &r : g)
            for (auto &ch : r)
                if (rnd(0, 5) == 0) ch = '*';
        // 暴力：从第一个空格出发 DFS 枚举哈密顿回路（每个回路正反各数一次，除以 2）
        vector<pair<int, int>> cells;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (g[i][j] == '.') cells.push_back({i, j});
        ll brute = 0;
        int K = cells.size();
        if (K >= 4) {
            vector<vector<bool>> vis(n, vector<bool>(m));
            auto [si, sj] = cells[0];
            function<void(int, int, int)> dfs = [&](int i, int j, int cnt) {
                int di[] = {1, -1, 0, 0}, dj[] = {0, 0, 1, -1};
                for (int d = 0; d < 4; d++) {
                    int a = i + di[d], b = j + dj[d];
                    if (a < 0 || a >= n || b < 0 || b >= m || g[a][b] != '.') continue;
                    if (a == si && b == sj && cnt == K) brute++;
                    if (!vis[a][b]) vis[a][b] = true, dfs(a, b, cnt + 1), vis[a][b] = false;
                }
            };
            vis[si][sj] = true;
            dfs(si, sj, 1);
            brute /= 2;
        }
        CHECK(count_hamiltonian_cycles(g) == brute);
    }
    CHECK(count_hamiltonian_cycles({"....", "....", "....", "...."}) == 6);   // 4×4 全空：6 个哈密顿回路
    return 0;
}
