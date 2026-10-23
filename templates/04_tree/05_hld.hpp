/**
 * 04_tree/05 树链剖分
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：04_tree/02 最近公共祖先（LCA）、02_ds/07 线段树（含懒标记）
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 重链剖分
 *   2. 路径修改 / 查询（配合线段树）
 *   3. 子树修改 / 查询
 *   4. 用树剖求 LCA
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/hld/
 *   cp-algorithms  https://cp-algorithms.com/graph/hld.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3384  P3384 【模板】重链剖分 / 树链剖分
 *   https://judge.yosupo.jp/problem/vertex_add_path_sum  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10641  提高  P10641 BZOJ3252 攻略  考点：贪心、线段树、可并堆
 *   https://www.luogu.com.cn/problem/P3459  提高  P3459 [POI 2007] MEG-Megalopolis  考点：线段树、树状数组、深度优先搜索 DFS
 *   https://www.luogu.com.cn/problem/P4374  提高  P4374 [USACO18OPEN] Disruption P  考点：线段树、并查集、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P9235  提高  P9235 [蓝桥杯 2023 省 A] 网络稳定性  考点：图论、贪心、倍增
 *   https://codeforces.com/problemset/problem/161/D  CF1800  CF161D Distance in Tree  考点：搜索、DP、树
 *   https://www.luogu.com.cn/problem/P3178  提高+/省选−  P3178 [HAOI2015] 树上操作  考点：线段树、树状数组、深度优先搜索 DFS
 *   https://codeforces.com/problemset/problem/208/E  CF2100  CF208E Blood Cousins  考点：二分、数据结构、搜索
 *   https://codeforces.com/problemset/problem/343/D  CF2100  CF343D Water Tree  考点：数据结构、搜索、图论
 *   https://codeforces.com/problemset/problem/587/C  CF2200  CF587C Duff in the Army  考点：数据结构、树
 *   https://codeforces.com/problemset/problem/1009/F  CF2300  CF1009F Dominant Indices  考点：数据结构、并查集、树
 *   https://codeforces.com/problemset/problem/1174/F  CF2400  CF1174F Ehab and the Big Finale  考点：构造、分治、图论
 *   https://codeforces.com/problemset/problem/1615/E  CF2400  CF1615E Purple Crayon  考点：数据结构、搜索、博弈
 *   https://www.luogu.com.cn/problem/P1084  省选/NOI−  P1084 [NOIP 2012 提高组] 疫情控制  考点：贪心、树形数据结构、线段树
 *   https://www.luogu.com.cn/problem/P4211  省选/NOI−  P4211 [LNOI2014] LCA  考点：线段树、最近公共祖先 LCA、树链剖分
 *   https://www.luogu.com.cn/problem/P5127  省选/NOI−  P5127 子异和
 *
 */

// 树链剖分（重链剖分）：每个点选子树最大的儿子为"重儿子"，重边连成重链。
// 按"先走重儿子"的顺序编 DFS 序，则：每条重链是 DFS 序上的一段连续区间，每棵子树也是一段连续区间；
// 任意路径最多经过 O(log n) 条重链。配合线段树，路径 / 子树的修改和查询都是 O(log^2 n) / O(log n)。
// 本模板：路径加、路径求和、子树加、子树求和、LCA（洛谷 P3384，需要取模时在线段树中取模）。点编号 0..n-1
struct HLD {
    int n;
    vector<int> fa, dep, sz, heavy, top, dfn;
    vector<ll> sum, tag;   // 线段树（区间加、区间和），下标为 DFS 序
    HLD(const vector<vector<int>> &g, const vector<ll> &w, int root = 0) : n(g.size()) {
        fa.assign(n, -1), dep.assign(n, 0), sz.assign(n, 1), heavy.assign(n, -1), top.assign(n, root), dfn.assign(n, 0);
        vector<int> order{root};   // BFS 序求父亲、深度、子树大小、重儿子（避免递归）
        for (size_t i = 0; i < order.size(); i++)
            for (int v : g[order[i]])
                if (v != fa[order[i]]) fa[v] = order[i], dep[v] = dep[order[i]] + 1, order.push_back(v);
        for (int i = n - 1; i > 0; i--) {
            int v = order[i], p = fa[v];
            sz[p] += sz[v];
            if (heavy[p] == -1 || sz[v] > sz[heavy[p]]) heavy[p] = v;
        }
        int timer = 0;
        vector<int> st{root};   // 用栈做先序遍历：重儿子最后入栈、最先出栈
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            dfn[u] = timer++;
            for (int v : g[u])
                if (v != fa[u] && v != heavy[u]) top[v] = v, st.push_back(v);
            if (heavy[u] != -1) top[heavy[u]] = top[u], st.push_back(heavy[u]);
        }
        sum.assign(4 * n, 0), tag.assign(4 * n, 0);
        vector<ll> a(n);
        for (int u = 0; u < n; u++) a[dfn[u]] = w[u];
        build(1, 0, n, a);
    }
    // ---- 线段树部分：[l, r) 左闭右开 ----
    void build(int p, int l, int r, const vector<ll> &a) {
        if (r - l == 1) { sum[p] = a[l]; return; }
        int m = (l + r) / 2;
        build(2 * p, l, m, a), build(2 * p + 1, m, r, a);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
    void apply(int p, int len, ll x) { sum[p] += x * len, tag[p] += x; }
    void push(int p, int l, int m, int r) {
        if (tag[p]) apply(2 * p, m - l, tag[p]), apply(2 * p + 1, r - m, tag[p]), tag[p] = 0;
    }
    void seg_add(int p, int l, int r, int x, int y, ll v) {
        if (y <= l || r <= x) return;
        if (x <= l && r <= y) { apply(p, r - l, v); return; }
        int m = (l + r) / 2;
        push(p, l, m, r);
        seg_add(2 * p, l, m, x, y, v), seg_add(2 * p + 1, m, r, x, y, v);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
    ll seg_sum(int p, int l, int r, int x, int y) {
        if (y <= l || r <= x) return 0;
        if (x <= l && r <= y) return sum[p];
        int m = (l + r) / 2;
        push(p, l, m, r);
        return seg_sum(2 * p, l, m, x, y) + seg_sum(2 * p + 1, m, r, x, y);
    }
    // ---- 树上操作 ----
    // 把 u-v 路径拆成若干段 DFS 序区间：每次让链顶更深的点跳到链顶的父亲
    template <class F>
    void for_path(int u, int v, F f) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            f(dfn[top[u]], dfn[u] + 1);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        f(dfn[u], dfn[v] + 1);
    }
    int lca(int u, int v) const {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    void path_add(int u, int v, ll x) { for_path(u, v, [&](int l, int r) { seg_add(1, 0, n, l, r, x); }); }
    ll path_sum(int u, int v) {
        ll s = 0;
        for_path(u, v, [&](int l, int r) { s += seg_sum(1, 0, n, l, r); });
        return s;
    }
    void subtree_add(int u, ll x) { seg_add(1, 0, n, dfn[u], dfn[u] + sz[u], x); }
    ll subtree_sum(int u) { return seg_sum(1, 0, n, dfn[u], dfn[u] + sz[u]); }
};
