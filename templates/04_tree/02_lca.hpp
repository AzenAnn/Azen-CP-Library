/**
 * 04_tree/02 最近公共祖先（LCA）
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：04_tree/01 树的基础：直径、重心、DFS 序、01_basic/09 倍增
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 倍增 LCA
 *   2. 欧拉序 + ST 表
 *   3. 树上两点距离
 *   4. 倍增维护路径最值
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/lca/
 *   cp-algorithms  https://cp-algorithms.com/graph/lca_binary_lifting.html
 *   cp-algorithms  https://cp-algorithms.com/graph/lca.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3379  P3379 【模板】最近公共祖先（LCA）
 *   https://judge.yosupo.jp/problem/lca  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10113  普及  P10113 [GESP202312 八级] 大量的工作沟通  考点：最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P13016  普及  P13016 [GESP202506 六级] 最大因数  考点：图论、数论、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P3884  普及  P3884 [JLOI2009] 二叉树问题  考点：深度优先搜索 DFS、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P5836  普及  P5836 [USACO19DEC] Milk Visits S  考点：搜索、树形数据结构、并查集
 *   https://www.luogu.com.cn/problem/P3258  普及+/提高−  P3258 [JLOI2014] 松鼠的新家  考点：线段树、最近公共祖先 LCA、树链剖分
 *   https://www.luogu.com.cn/problem/P3398  普及+/提高−  P3398 仓鼠找 sugar  考点：倍增、最近公共祖先 LCA、树链剖分
 *   https://www.luogu.com.cn/problem/P4427  普及+/提高−  P4427 [BJOI2018] 求和  考点：倍增、深度优先搜索 DFS、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P8805  普及+/提高−  P8805 [蓝桥杯 2022 国 B] 机房  考点：最近公共祖先 LCA、前缀和
 *   https://www.luogu.com.cn/problem/P2245  提高  P2245 星际导航  考点：图论、Kruskal 重构树、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P2783  提高  P2783 有机化学之神偶尔会做作弊  考点：图论、Tarjan、双连通分量
 *   https://www.luogu.com.cn/problem/P5021  提高  P5021 [NOIP 2018 提高组] 赛道修建  考点：贪心、二分、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P5829  提高  P5829 【模板】失配树  考点：字符串、树形数据结构、最近公共祖先 LCA
 *   https://codeforces.com/problemset/problem/1304/E  CF2000  CF1304E 1-Trees and Queries  考点：数据结构、搜索、最短路
 *   https://codeforces.com/problemset/problem/519/E  CF2100  CF519E A and B and Lecture Rooms  考点：二分、数据结构、搜索
 *   https://codeforces.com/problemset/problem/609/E  CF2100  CF609E Minimum spanning tree for each edge  考点：数据结构、搜索、并查集
 *
 */

// 倍增 LCA：up[k][u] 为 u 的第 2^k 个祖先（根的祖先设为根自己）。预处理 O(n log n)，查询 O(log n)
// 点编号 0..n-1。另一种做法"欧拉序 + ST 表"可以 O(1) 查询，留作练习
struct LCA {
    int n, LOG;
    vector<vector<int>> up;
    vector<int> dep;
    LCA(const vector<vector<int>> &g, int root = 0)
        : n(g.size()), LOG(__lg(max(n, 1)) + 1), up(LOG, vector<int>(n, root)), dep(n, 0) {
        vector<int> q{root};
        vector<bool> vis(n, false);
        vis[root] = true;
        for (size_t i = 0; i < q.size(); i++) {   // BFS，避免递归爆栈
            int u = q[i];
            for (int v : g[u])
                if (!vis[v]) vis[v] = true, dep[v] = dep[u] + 1, up[0][v] = u, q.push_back(v);
        }
        for (int k = 1; k < LOG; k++)
            for (int u = 0; u < n; u++) up[k][u] = up[k - 1][up[k - 1][u]];
    }
    int kth_ancestor(int u, int k) const {   // 向上跳 k 步，要求 k <= dep[u]
        for (int j = 0; k; j++, k >>= 1)
            if (k & 1) u = up[j][u];
        return u;
    }
    int lca(int a, int b) const {
        if (dep[a] < dep[b]) swap(a, b);
        a = kth_ancestor(a, dep[a] - dep[b]);   // 先跳到同一深度
        if (a == b) return a;
        for (int k = LOG - 1; k >= 0; k--)       // 再一起往上跳，停在 LCA 的下面一层
            if (up[k][a] != up[k][b]) a = up[k][a], b = up[k][b];
        return up[0][a];
    }
    int dist(int a, int b) const { return dep[a] + dep[b] - 2 * dep[lca(a, b)]; }
};
