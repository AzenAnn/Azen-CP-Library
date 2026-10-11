/**
 * 04_tree/03 树上差分与树上前缀和
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：04_tree/02 最近公共祖先（LCA）、01_basic/02 前缀和与差分
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 点差分：路径上的点加 x
 *   2. 边差分：路径上的边加 x
 *   3. 树上前缀和：路径和
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/basic/prefix-sum/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3128  P3128 [USACO15DEC] Max Flow P
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10931  普及+/提高−  P10931 闇の連鎖  考点：最近公共祖先 LCA、树链剖分、差分
 *   https://www.luogu.com.cn/problem/P11967  普及+/提高−  P11967 [GESP202503 八级] 割裂  考点：倍增、最近公共祖先 LCA、差分
 *   https://www.luogu.com.cn/problem/P17424  普及+/提高−  P17424 [ICPC 2018 Xuzhou R] Rikka with Intersections of Paths  考点：线段树、最近公共祖先 LCA、树链剖分
 *   https://www.luogu.com.cn/problem/P3258  普及+/提高−  P3258 [JLOI2014] 松鼠的新家  考点：线段树、最近公共祖先 LCA、树链剖分
 *   https://www.luogu.com.cn/problem/P4427  普及+/提高−  P4427 [BJOI2018] 求和  考点：倍增、深度优先搜索 DFS、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P6869  普及+/提高−  P6869 [COCI 2019/2020 #5] Putovanje  考点：最近公共祖先 LCA、差分
 *   https://www.luogu.com.cn/problem/P9246  普及+/提高−  P9246 [蓝桥杯 2023 省 B] 砍树  考点：最近公共祖先 LCA、差分
 *   https://www.luogu.com.cn/problem/P2680  提高  P2680 [NOIP 2015 提高组] 运输计划  考点：图论、二分、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P6594  提高  P6594 [YsOI2020] 换寝室  考点：二分、深度优先搜索 DFS、树形 DP
 *   https://www.luogu.com.cn/problem/P7924  提高  P7924 「EVOI-RD2」旅行家  考点：双连通分量、最近公共祖先 LCA、差分
 *   https://www.luogu.com.cn/problem/P8201  提高  P8201 [传智杯 #4 决赛] [yLOI2021] 生活在树上（hard version）  考点：树形数据结构、树状数组、最近公共祖先 LCA
 *   https://codeforces.com/problemset/problem/191/C  CF1900  CF191C Fools and Roads  考点：数据结构、搜索、树
 *   https://www.luogu.com.cn/problem/P5384  提高+/省选−  P5384 [Cnoi2019] 雪松果树  考点：深度优先搜索 DFS、最近公共祖先 LCA、树链剖分
 *
 */

// 树上差分：把"路径加"变成"几个点上的单点修改"，最后做一次子树求和还原，O(n log n + q log n)
// 内置一个精简的倍增 LCA，可以直接粘贴使用。点编号 0..n-1
struct TreeDiff {
    int n, LOG;
    vector<vector<int>> up;
    vector<int> dep, order;   // order 为 BFS 序（父亲在前）
    vector<ll> d;
    TreeDiff(const vector<vector<int>> &g, int root = 0) : n(g.size()), LOG(__lg(max(n, 1)) + 1), dep(n, 0), d(n, 0) {
        up.assign(LOG, vector<int>(n, root));
        vector<bool> vis(n, false);
        order = {root}, vis[root] = true;
        for (size_t i = 0; i < order.size(); i++)
            for (int v : g[order[i]])
                if (!vis[v]) vis[v] = true, dep[v] = dep[order[i]] + 1, up[0][v] = order[i], order.push_back(v);
        for (int k = 1; k < LOG; k++)
            for (int u = 0; u < n; u++) up[k][u] = up[k - 1][up[k - 1][u]];
    }
    int parent(int u) const { return u == order[0] ? -1 : up[0][u]; }
    int lca(int a, int b) const {
        if (dep[a] < dep[b]) swap(a, b);
        for (int k = LOG - 1; k >= 0; k--)
            if (dep[a] - (1 << k) >= dep[b]) a = up[k][a];
        if (a == b) return a;
        for (int k = LOG - 1; k >= 0; k--)
            if (up[k][a] != up[k][b]) a = up[k][a], b = up[k][b];
        return up[0][a];
    }
    // 1. 点差分：u-v 路径上的每个点加 x。d[u] += x, d[v] += x, d[lca] -= x, d[parent(lca)] -= x
    void add_path_vertices(int u, int v, ll x) {
        int w = lca(u, v);
        d[u] += x, d[v] += x, d[w] -= x;
        if (parent(w) != -1) d[parent(w)] -= x;
    }
    // 2. 边差分：u-v 路径上的每条边加 x。每条边用它深度较大的端点表示：d[u] += x, d[v] += x, d[lca] -= 2x
    void add_path_edges(int u, int v, ll x) {
        int w = lca(u, v);
        d[u] += x, d[v] += x, d[w] -= 2 * x;
    }
    // 还原：每个点的值 = 子树内 d 的和。点差分时 res[v] 是点 v 的值；边差分时 res[v] 是边 (v, 父亲) 的值
    vector<ll> build() const {
        vector<ll> s(d);
        for (int i = n - 1; i > 0; i--) s[up[0][order[i]]] += s[order[i]];
        return s;
    }
    // 3. 树上前缀和：pre[v] = 根到 v 路径上的点权和；u-v 路径点权和 = pre[u] + pre[v] - pre[lca] - pre[parent(lca)]
    vector<ll> prefix(const vector<ll> &w) const {
        vector<ll> pre(n);
        for (int u : order) pre[u] = w[u] + (parent(u) == -1 ? 0 : pre[parent(u)]);
        return pre;
    }
    ll path_sum(const vector<ll> &pre, int u, int v) const {
        int w = lca(u, v);
        return pre[u] + pre[v] - pre[w] - (parent(w) == -1 ? 0 : pre[parent(w)]);
    }
};
