/**
 * 04_tree/13 树上随机游走
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：04_tree/01 树的基础：直径、重心、DFS 序、06_dp/09 概率与期望 DP
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 随机游走期望方程：f[u] = 1 + Σ f[v] / deg[u]
 *   2. 叶子消元：利用叶子只连父亲，把叶子期望用父亲表示，逐层消元
 *   3. 从根出发/任意点对间期望步数
 *   4. 结合高斯消元：方程组直接求解（n 较小时）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/tree-random-walk/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3412  P3412 仓鼠找sugar II
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P6835  提高+/省选−  P6835 [Cnoi2020] 线形生物  考点：链上随机游走：期望步数的前缀和递推
 *   https://www.luogu.com.cn/problem/P2081  省选/NOI−  P2081 [NOI2012] 迷失游乐园  考点：期望、动态规划 DP、图论
 *   https://www.luogu.com.cn/problem/P8657  省选/NOI−  P8657 [蓝桥杯 2017 国 B] 观光铁路  考点：随机游走 Markov Chain、高斯消元
 *   https://www.luogu.com.cn/problem/P4321  NOI/NOI+/CTS  P4321 随机漫游  考点：状压 + 随机游走的期望方程（高斯消元）
 *   https://www.luogu.com.cn/problem/P5643  NOI/NOI+/CTS  P5643 [PKUWC2018] 随机游走  考点：Min-Max 容斥 + 树上随机游走（叶子消元）
 *
 */

// 树上随机游走：每一步等概率走向一个相邻点，经过边 (u, v) 花费 w(u, v)（不带权时 w = 1，就是步数）。
// up[u]：从 u 出发第一次到达父亲的期望花费 = Σ_{u 的所有邻边} w + Σ_{u 的儿子 c} up[c]（不带权时就是 2·size(u) − 1）；
// down[u]：从父亲 p 出发第一次到达 u 的期望花费 = Σ_{p 的所有邻边} w + Σ_{p 的其他儿子 s} up[s] + down[p]。
// 两点之间：E(u → v) = u 往上到 LCA 的 up 之和 + LCA 往下到 v 的 down 之和。边权为整数时结果是整数。
struct TreeRandomWalk {
    int n, LOG;
    vector<vector<pair<int, ll>>> g;
    vector<int> dep;
    vector<vector<int>> anc;
    vector<ll> up, down, su, sd;   // su[v]：根到 v 路径上的 up 之和；sd 同理
    TreeRandomWalk(const vector<vector<pair<int, ll>>> &g, int root = 0)
        : n(g.size()), LOG(__lg(max(n, 1)) + 1), g(g), dep(n, 0), anc(LOG, vector<int>(n, root)), up(n, 0), down(n, 0), su(n, 0), sd(n, 0) {
        vector<int> order = {root}, fa(n, -1);
        vector<ll> wsum(n, 0);   // 每个点所有邻边的权值和
        for (size_t h = 0; h < order.size(); h++) {
            int u = order[h];
            for (auto [v, w] : g[u]) {
                wsum[u] += w;
                if (v != fa[u]) fa[v] = u, dep[v] = dep[u] + 1, anc[0][v] = u, order.push_back(v);
            }
        }
        for (int i = n - 1; i > 0; i--) {   // 儿子先算
            int u = order[i];
            up[u] += wsum[u];
            up[fa[u]] += up[u];   // 先把儿子的 up 累加到父亲上（父亲稍后再加自己的 wsum）
        }
        // 此时 up[p] 暂存 Σ 儿子 up，down[c] = wsum[p] + (Σ 儿子 up − up[c]) + down[p]
        vector<ll> child_up(n);
        for (int i = 0; i < n; i++) child_up[order[i]] = up[order[i]] - (order[i] == root ? 0 : wsum[order[i]]);
        for (int i = 1; i < n; i++) {
            int c = order[i], p = fa[c];
            down[c] = wsum[p] + (child_up[p] - up[c]) + (p == root ? 0 : down[p]);
        }
        up[root] = 0;
        for (int i = 1; i < n; i++) {
            int v = order[i];
            su[v] = su[fa[v]] + up[v], sd[v] = sd[fa[v]] + down[v];
        }
        for (int j = 1; j < LOG; j++)
            for (int v = 0; v < n; v++) anc[j][v] = anc[j - 1][anc[j - 1][v]];
    }
    int lca(int a, int b) const {
        if (dep[a] < dep[b]) swap(a, b);
        for (int j = LOG - 1; j >= 0; j--)
            if (dep[a] - (1 << j) >= dep[b]) a = anc[j][a];
        if (a == b) return a;
        for (int j = LOG - 1; j >= 0; j--)
            if (anc[j][a] != anc[j][b]) a = anc[j][a], b = anc[j][b];
        return anc[0][a];
    }
    // 从 u 出发第一次到达 v 的期望花费
    ll expected(int u, int v) const {
        int l = lca(u, v);
        return (su[u] - su[l]) + (sd[v] - sd[l]);
    }
};
