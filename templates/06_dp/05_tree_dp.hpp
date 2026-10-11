/**
 * 06_dp/05 树形 DP 与换根 DP
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：04_tree/01 树的基础：直径、重心、DFS 序
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 子树 DP（没有上司的舞会）
 *   2. 树上背包
 *   3. 换根 DP
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/tree/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/dp.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1352  P1352 没有上司的舞会
 *   https://www.luogu.com.cn/problem/P3478  P3478 [POI 2008] STA-Station
 *   https://www.luogu.com.cn/problem/P2014  P2014 [CTSC1997] 选课
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1122  普及  P1122 最大子树和  考点：动态规划 DP、树形 DP
 *   https://www.luogu.com.cn/problem/P14919  普及  P14919 [GESP202512 六级] 路径覆盖  考点：搜索、贪心、深度优先搜索 DFS
 *   https://www.luogu.com.cn/problem/P15801  普及  P15801 [GESP202603 六级] 完全二叉树  考点：树形数据结构、树形 DP、树的遍历
 *   https://www.luogu.com.cn/problem/P2016  普及  P2016 [SEERC 2000] 战略游戏  考点：动态规划 DP、图论、贪心
 *   https://www.luogu.com.cn/problem/P1273  普及+/提高−  P1273 [CHCI 2002 Final Exam #2] 有线电视网  考点：动态规划 DP、树形数据结构、递归
 *   https://www.luogu.com.cn/problem/P2015  普及+/提高−  P2015 二叉苹果树  考点：动态规划 DP、树形数据结构、背包 DP
 *   https://codeforces.com/problemset/problem/959/C  CF1500  CF959C Mahmoud and Ehab and the wrong algorithm  考点：构造、树
 *   https://codeforces.com/problemset/problem/763/A  CF1600  CF763A Timofey and a tree  考点：搜索、DP、并查集
 *   https://codeforces.com/problemset/problem/219/D  CF1700  CF219D Choosing Capital for Treeland  考点：搜索、DP、图论
 *   https://www.luogu.com.cn/problem/P1272  提高  P1272 [USACO02FEB] 重建道路  考点：动态规划 DP、背包 DP、树形 DP
 *   https://www.luogu.com.cn/problem/P2279  提高  P2279 [HNOI2003] 消防局的设立  考点：贪心、深度优先搜索 DFS、树形 DP
 *   https://codeforces.com/problemset/problem/1324/F  CF1800  CF1324F Maximum White Subtree  考点：搜索、DP、图论
 *   https://codeforces.com/problemset/problem/1988/D  CF2000  CF1988D The Omnipotent Monster Killer  考点：暴力、搜索、DP
 *   https://codeforces.com/problemset/problem/337/D  CF2000  CF337D Book of Evil  考点：搜索、分治、DP
 *   https://codeforces.com/problemset/problem/1187/E  CF2100  CF1187E Tree Painting  考点：搜索、DP、树
 *
 */

// 树形 DP：f[u] 由儿子的 f 合并得到。用 BFS 序倒序遍历（先儿子后父亲），避免递归爆栈。点编号 0..n-1

// 1. 没有上司的舞会（洛谷 P1352）：选一些点使任意两点不是父子关系，点权和最大（树上最大权独立集）
//    f[u][0]：u 不选；f[u][1]：u 选。f[u][0] += max(f[v][0], f[v][1])，f[u][1] += f[v][0]
ll max_independent_set(const vector<vector<int>> &g, const vector<ll> &w, int root = 0) {
    int n = g.size();
    vector<int> fa(n, -1), order{root};
    for (size_t i = 0; i < order.size(); i++)
        for (int v : g[order[i]])
            if (v != fa[order[i]]) fa[v] = order[i], order.push_back(v);
    vector<array<ll, 2>> f(n);
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        f[u][0] = 0, f[u][1] = w[u];
        for (int v : g[u])
            if (v != fa[u]) f[u][0] += max(f[v][0], f[v][1]), f[u][1] += f[v][0];
    }
    return max(f[root][0], f[root][1]);
}

// 2. 树上背包（洛谷 P2014 选课）：par[i] 为 i 的先修课（-1 表示没有），选一门课必须先选它的先修课，
//    最多选 m 门，学分和最大。加一个虚拟根 n 把森林连成树，相当于在树上选包含根的 m + 1 个点。
//    f[u][j]：u 的子树中选 j 个点（必须包含 u）的最大值。合并儿子时 j 只枚举到子树大小，总复杂度 O(n · m)
ll tree_knapsack(const vector<int> &par, const vector<ll> &w, int m) {
    int n = par.size();
    vector<vector<int>> ch(n + 1);
    for (int i = 0; i < n; i++) ch[par[i] == -1 ? n : par[i]].push_back(i);
    vector<int> order{n};
    for (size_t i = 0; i < order.size(); i++)
        for (int v : ch[order[i]]) order.push_back(v);
    const ll NEG = LLONG_MIN / 4;
    vector<vector<ll>> f(n + 1);
    for (int i = n; i >= 0; i--) {
        int u = order[i];
        f[u] = {NEG, u == n ? 0 : w[u]};   // f[u][1]：只选 u 自己
        for (int v : ch[u]) {
            int cap = min((int)(f[u].size() + f[v].size()) - 2, m + 1);
            vector<ll> g(cap + 1, NEG);
            for (size_t j = 1; j < f[u].size(); j++)
                for (size_t k = 0; k < f[v].size() && j + k <= (size_t)cap; k++) {
                    ll add = k == 0 ? 0 : f[v][k];
                    if (f[u][j] > NEG && add > NEG) g[j + k] = max(g[j + k], f[u][j] + add);
                }
            f[u] = g;
        }
    }
    ll best = 0;
    for (size_t j = 1; j < f[n].size() && j <= (size_t)m + 1; j++) best = max(best, f[n][j]);
    return best;
}

// 3. 换根 DP（洛谷 P3478）：求每个点作为根时，所有点到它的距离之和。
//    先以 0 为根求出 S(0) 和子树大小 sz；从父亲 u 换到儿子 v 时，v 的子树中的 sz[v] 个点距离各减 1，
//    其余 n - sz[v] 个点距离各加 1：S(v) = S(u) - sz[v] + (n - sz[v])
vector<ll> sum_dist_all_roots(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> fa(n, -1), dep(n, 0), order{0};
    for (size_t i = 0; i < order.size(); i++)
        for (int v : g[order[i]])
            if (v != fa[order[i]]) fa[v] = order[i], dep[v] = dep[order[i]] + 1, order.push_back(v);
    vector<ll> sz(n, 1), S(n, 0);
    for (int i = n - 1; i > 0; i--) sz[fa[order[i]]] += sz[order[i]];
    for (int u = 0; u < n; u++) S[0] += dep[u];
    for (int i = 1; i < n; i++) {
        int v = order[i];
        S[v] = S[fa[v]] - sz[v] + (n - sz[v]);
    }
    return S;
}
