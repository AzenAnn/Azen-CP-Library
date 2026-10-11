/**
 * 04_tree/08 虚树
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：04_tree/02 最近公共祖先（LCA）
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 按 DFS 序排序关键点
 *   2. 单调栈建虚树
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/virtual-tree/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2495  P2495 【模板】虚树 / [SDOI2011] 消耗战
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10930  省选/NOI−  P10930 异象石  考点：深度优先搜索 DFS、最近公共祖先 LCA、虚树
 *   https://www.luogu.com.cn/problem/P3233  省选/NOI−  P3233 [HNOI2014] 世界树  考点：动态规划 DP、倍增、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P3320  省选/NOI−  P3320 [SDOI2015] 寻宝游戏  考点：深度优先搜索 DFS、最近公共祖先 LCA、虚树
 *   https://www.luogu.com.cn/problem/P4103  省选/NOI−  P4103 [HEOI2014] 大工程  考点：倍增、树上启发式合并、虚树
 *   https://www.luogu.com.cn/problem/P7409  省选/NOI−  P7409 SvT  考点：字符串、图论、后缀自动机 SAM
 *   https://www.luogu.com.cn/problem/P7737  省选/NOI−  P7737 [NOI2021] 庆典  考点：线段树、广度优先搜索 BFS、拓扑排序
 *   https://codeforces.com/problemset/problem/1111/E  CF2500  CF1111E Tree  考点：数据结构、搜索、DP
 *   https://codeforces.com/problemset/problem/1725/E  CF2500  CF1725E Electrical Efficiency  考点：组合数学、数据结构、DP
 *   https://codeforces.com/problemset/problem/613/D  CF2800  CF613D Kingdom and its Cities  考点：搜索、分治、DP
 *   https://www.luogu.com.cn/problem/P3783  NOI/NOI+/CTS  P3783 [SDOI2017] 天才黑客  考点：字符串、线段树、虚树
 *   https://www.luogu.com.cn/problem/P4426  NOI/NOI+/CTS  P4426 [HNOI/AHOI2018] 毒瘤  考点：并查集、枚举、虚树
 *   https://www.luogu.com.cn/problem/P5327  NOI/NOI+/CTS  P5327 [ZJOI2019] 语言  考点：线段树、深度优先搜索 DFS、树链剖分
 *   https://www.luogu.com.cn/problem/P5891  NOI/NOI+/CTS  P5891 Fracture Ray
 *   https://www.luogu.com.cn/problem/P9479  NOI/NOI+/CTS  P9479 [NOI2023] 桂花树  考点：动态规划 DP、虚树、状压 DP
 *   https://codeforces.com/problemset/problem/1320/E  CF3000  CF1320E Treeland and Viruses  考点：数据结构、搜索、DP
 *
 */

// 虚树：多次询问、每次只涉及 k 个关键点时，只保留关键点和它们两两的 LCA，建一棵 O(k) 大小的树，
// 在上面做树形 DP，单次询问 O(k log n)，总复杂度与 Σk 相关而不是与 n 相关。
// 建法：关键点按 DFS 序排序，加入相邻两点的 LCA，再排序去重得到点集 A；
//       对 A 中相邻的两点 a、b，lca(a, b) 就是 b 在虚树中的父亲。点编号 0..n-1，根为 0
struct VirtualTree {
    int n, LOG;
    vector<vector<int>> up;
    vector<int> dep, tin;
    vector<ll> mn;   // mn[v]：根到 v 路径上的最小边权（例题用）
    VirtualTree(const vector<vector<pair<int, ll>>> &g) : n(g.size()), LOG(__lg(max(n, 1)) + 1), dep(n, 0), tin(n, 0), mn(n, LLONG_MAX) {
        up.assign(LOG, vector<int>(n, 0));
        vector<int> st{0}, fa(n, -1);
        int timer = 0;
        while (!st.empty()) {   // 迭代先序遍历求 DFS 序
            int u = st.back();
            st.pop_back();
            tin[u] = timer++;
            for (auto [v, w] : g[u])
                if (v != fa[u]) fa[v] = u, up[0][v] = u, dep[v] = dep[u] + 1, mn[v] = min(mn[u], w), st.push_back(v);
        }
        for (int k = 1; k < LOG; k++)
            for (int u = 0; u < n; u++) up[k][u] = up[k - 1][up[k - 1][u]];
    }
    int lca(int a, int b) const {
        if (dep[a] < dep[b]) swap(a, b);
        for (int k = LOG - 1; k >= 0; k--)
            if (dep[a] - (1 << k) >= dep[b]) a = up[k][a];
        if (a == b) return a;
        for (int k = LOG - 1; k >= 0; k--)
            if (up[k][a] != up[k][b]) a = up[k][a], b = up[k][b];
        return up[0][a];
    }
    // 返回 {虚树的点（按 DFS 序）, 每个点在虚树中的父亲（第一个点为虚树的根，父亲为 -1）}
    pair<vector<int>, vector<int>> build(vector<int> keys) const {
        auto by_tin = [&](int a, int b) { return tin[a] < tin[b]; };
        sort(keys.begin(), keys.end(), by_tin);
        vector<int> A(keys);
        for (size_t i = 1; i < keys.size(); i++) A.push_back(lca(keys[i - 1], keys[i]));
        sort(A.begin(), A.end(), by_tin);
        A.erase(unique(A.begin(), A.end()), A.end());
        vector<int> par(A.size(), -1);
        for (size_t i = 1; i < A.size(); i++) par[i] = lca(A[i - 1], A[i]);
        return {A, par};
    }
    // 例题（洛谷 P2495 消耗战）：切断若干边，使根 0 与所有关键点都不连通，求最小代价。
    // 在虚树上 DP：f(v) = v 是关键点 ? mn[v] : min(mn[v], Σ f(儿子))，答案为 Σ f(根的儿子)
    ll min_cut_keys(const vector<int> &keys) const {
        vector<int> ks(keys);
        ks.push_back(0);   // 把根也放进虚树
        auto [A, par] = build(ks);
        int k = A.size();
        unordered_map<int, int> idx;
        for (int i = 0; i < k; i++) idx[A[i]] = i;
        vector<bool> is_key(k, false);
        for (int v : keys) is_key[idx[v]] = true;
        vector<ll> sum(k, 0);
        for (int i = k - 1; i > 0; i--) {   // DFS 序倒序：儿子先于父亲处理
            ll f = is_key[i] ? mn[A[i]] : min(mn[A[i]], sum[i]);
            sum[idx[par[i]]] += f;
        }
        return sum[0];
    }
};
