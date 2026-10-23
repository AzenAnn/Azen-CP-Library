/**
 * 03_graph/16 最小割树（Gomory-Hu Tree）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：03_graph/14 网络流：最大流与最小割
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 问题：无向图中任意两点之间的最小割（= 最大流），一共 n^2 对，但只有至多 n−1 种不同的值
 *   2. 最小割树：一棵 n 个点的树，u、v 的最小割 = 树上 u→v 路径的最小边权
 *   3. 构造（Gusfield 做法，不用缩点）：par 初始全为 0；依次对 i = 1..n−1 求 i 与 par[i] 的最小割 f，
 *      树边为 (i, par[i], f)；对 j > i 且 par[j] = par[i]、并且 j 落在 i 这一侧的点，令 par[j] = i
 *   4. 一共 n−1 次最大流（Dinic），每次都要在原图上重新跑（容量要复原）
 *   5. 应用：不同最小割的个数（P4123）、所有点对最小割之和、"割值 ≤ x 的点对数"
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/flow/min-cut/
 *   题解           https://www.luogu.com.cn/problem/solution/P4897
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4897  P4897 【模板】最小割树（Gomory-Hu Tree）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3329  省选/NOI−  P3329 [ZJOI2011] 最小割  考点：最小割树 + 统计割值 ≤ x 的点对
 *   https://www.luogu.com.cn/problem/P4123  省选/NOI−  P4123 [CQOI2016] 不同的最小割  考点：最小割树上 n−1 条边权去重
 *   https://www.luogu.com.cn/problem/P4214  省选/NOI−  P4214 [CERC2015] Juice Junctions  考点：度数 ≤ 3 时最大流 ≤ 3，最小割树或枚举
 *   https://www.luogu.com.cn/problem/UVA11594  省选/NOI−  UVA11594 All Pairs Maximum Flow  考点：最小割树求所有点对最大流
 *   https://codeforces.com/problemset/problem/343/E  CF2900  CF343E Pumping Stations  考点：最小割树上贪心取最大边的分治顺序
 *
 */

// 最小割树（Gusfield 构造）。无向图，点 0..n-1，边 {u, v, c}。构造 O(n · Dinic)，
// 之后 cut(u, v) O(n) 查询，all_pairs() O(n^2) 求出全部点对的最小割。
struct GomoryHu {
    struct Flow {   // 内置一个 Dinic，免得和 03_graph/14 的模板重名
        struct E { int to; ll cap; };
        int n;
        vector<E> e;
        vector<vector<int>> g;
        vector<int> lv, it;
        Flow(int n) : n(n), g(n), lv(n), it(n) {}
        void add(int u, int v, ll c) {   // 无向边：两个方向容量都是 c
            g[u].push_back(e.size()), e.push_back({v, c});
            g[v].push_back(e.size()), e.push_back({u, c});
        }
        bool bfs(int s, int t) {
            fill(lv.begin(), lv.end(), -1);
            lv[s] = 0;
            queue<int> q;
            q.push(s);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int id : g[u])
                    if (e[id].cap > 0 && lv[e[id].to] < 0) lv[e[id].to] = lv[u] + 1, q.push(e[id].to);
            }
            return lv[t] >= 0;
        }
        ll dfs(int u, int t, ll f) {
            if (u == t) return f;
            for (int &i = it[u]; i < (int)g[u].size(); i++) {
                int id = g[u][i], v = e[id].to;
                if (e[id].cap > 0 && lv[v] == lv[u] + 1) {
                    ll d = dfs(v, t, min(f, e[id].cap));
                    if (d > 0) {
                        e[id].cap -= d, e[id ^ 1].cap += d;
                        return d;
                    }
                }
            }
            return 0;
        }
        ll maxflow(int s, int t) {
            ll f = 0;
            while (bfs(s, t)) {
                fill(it.begin(), it.end(), 0);
                while (ll d = dfs(s, t, LLONG_MAX)) f += d;
            }
            return f;
        }
    };
    int n;
    vector<int> par;   // 树边 (i, par[i])，权值 w[i]；0 号点是根
    vector<ll> w;
    vector<vector<pair<int, ll>>> tree;
    GomoryHu(int n, const vector<array<ll, 3>> &edges) : n(n), par(n, 0), w(n, 0), tree(n) {
        for (int i = 1; i < n; i++) {
            Flow f(n);
            for (auto [u, v, c] : edges)
                if (u != v) f.add(u, v, c);
            w[i] = f.maxflow(i, par[i]);
            // 最后一次 bfs 中 lv >= 0 的点就是 i 这一侧（残量网络中 i 能到达的点）
            for (int j = i + 1; j < n; j++)
                if (par[j] == par[i] && f.lv[j] >= 0) par[j] = i;
            tree[i].push_back({par[i], w[i]}), tree[par[i]].push_back({i, w[i]});
        }
    }
    vector<ll> from(int s) const {   // s 到所有点的最小割（树上路径最小边权），s 到自己为 LLONG_MAX
        vector<ll> d(n, -1);
        d[s] = LLONG_MAX;
        vector<int> q = {s};
        for (size_t h = 0; h < q.size(); h++)
            for (auto [v, c] : tree[q[h]])
                if (d[v] < 0) d[v] = min(d[q[h]], c), q.push_back(v);
        return d;
    }
    ll cut(int u, int v) const { return from(u)[v]; }
    vector<vector<ll>> all_pairs() const {
        vector<vector<ll>> res(n);
        for (int s = 0; s < n; s++) res[s] = from(s);
        return res;
    }
};
