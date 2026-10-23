#include "../common.hpp"
#include "../../templates/03_graph/04_min_cycle.hpp"

const ll INF = MIN_CYCLE_INF;

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(1, 7);
        // 无向图最小环：暴力枚举所有简单环（从最小编号点出发 DFS）
        vector<vector<ll>> w(n, vector<ll>(n, INF));
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (rnd(0, 1)) w[i][j] = w[j][i] = rnd(1, 20);
        ll best = INF;
        vector<int> path;
        vector<bool> used(n);
        function<void(int, int, ll)> dfs = [&](int s, int u, ll len) {
            for (int v = s; v < n; v++) {
                if (w[u][v] >= INF) continue;
                if (v == s && path.size() >= 3) best = min(best, len + w[u][v]);
                if (!used[v] && v > s) used[v] = true, path.push_back(v), dfs(s, v, len + w[u][v]), path.pop_back(), used[v] = false;
            }
        };
        for (int s = 0; s < n; s++) used[s] = true, path = {s}, dfs(s, s, 0), used[s] = false;
        vector<int> cyc;
        ll got = floyd_min_cycle(w, &cyc);
        CHECK(got == best);
        if (got < INF) {   // 输出的环合法：点互不相同，相邻点有边，长度等于答案
            CHECK(cyc.size() >= 3);
            set<int> st(cyc.begin(), cyc.end());
            CHECK(st.size() == cyc.size());
            ll len = 0;
            for (size_t i = 0; i < cyc.size(); i++) {
                ll e = w[cyc[i]][cyc[(i + 1) % cyc.size()]];
                CHECK(e < INF);
                len += e;
            }
            CHECK(len == got);
        }

        // 有向图最小环 + 严格次短路：暴力按"长度"做可达性 DP
        vector<vector<ll>> dw(n, vector<ll>(n, INF));
        vector<vector<pair<int, ll>>> g(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (rnd(0, 2) == 0) {
                    ll c = rnd(1, 6);
                    dw[i][j] = min(dw[i][j], c);
                    g[i].push_back({j, c});
                }
        const int D = 80;
        // reach[d][v]：从 0 出发存在长度恰为 d 的路径到达 v
        vector<vector<bool>> reach(D + 1, vector<bool>(n));
        reach[0][0] = true;
        for (int d = 0; d <= D; d++)
            for (int u = 0; u < n; u++)
                if (reach[d][u])
                    for (auto [v, c] : g[u])
                        if (d + c <= D) reach[d + c][v] = true;
        auto [d1, d2] = second_shortest(g, 0);
        for (int v = 0; v < n; v++) {
            ll a = INF, b = INF;
            for (int d = 0; d <= D; d++)
                if (reach[d][v]) {
                    if (a == INF) a = d;
                    else if (b == INF) b = d;
                }
            CHECK(d1[v] == a);
            if (d2[v] <= 40 || b <= 40) CHECK(d2[v] == b);   // 次短路不超过 40 时 D=80 的暴力一定能找到
        }
        ll cyc_best = INF;   // 有向最小环 = min over v (从 v 出发回到 v 的最短正长度路径)
        for (int s = 0; s < n; s++) {
            vector<vector<bool>> r(D + 1, vector<bool>(n));
            for (auto [v, c] : g[s]) r[c][v] = true;
            for (int d = 0; d <= D; d++)
                for (int u = 0; u < n; u++)
                    if (r[d][u]) {
                        if (u == s) cyc_best = min(cyc_best, (ll)d);
                        for (auto [v, c] : g[u])
                            if (d + c <= D) r[d + c][v] = true;
                    }
        }
        CHECK(floyd_min_cycle_directed(dw) == cyc_best);
    }
    return 0;
}
