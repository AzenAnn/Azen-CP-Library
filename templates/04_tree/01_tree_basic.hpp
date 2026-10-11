/**
 * 04_tree/01 树的基础：直径、重心、DFS 序
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：03_graph/01 存图与图的遍历
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 一次 DFS 求父亲、深度、子树大小
 *   2. 树的直径：两次 BFS / 树形 DP
 *   3. 树的重心
 *   4. DFS 序：子树对应连续区间
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/tree-basic/
 *   OI-wiki        https://oi-wiki.org/graph/tree-diameter/
 *   OI-wiki        https://oi-wiki.org/graph/tree-centroid/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/B4016  B4016 树的直径
 *   https://www.luogu.com.cn/problem/P1395  P1395 会议
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/1843/C  CF800  CF1843C Sum in Binary Tree  考点：位运算、组合数学、数学
 *   https://codeforces.com/problemset/problem/1057/A  CF900  CF1057A Bmail Computer Network  考点：搜索、树
 *   https://codeforces.com/problemset/problem/115/A  CF900  CF115A Party  考点：搜索、图论、树
 *   https://www.luogu.com.cn/problem/P11962  普及−  P11962 [GESP202503 六级] 树上漫步  考点：广度优先搜索 BFS、深度优先搜索 DFS、二分图
 *   https://www.luogu.com.cn/problem/P14076  普及−  P14076 [GESP202509 六级] 货物运输  考点：图论、贪心、广度优先搜索 BFS
 *   https://www.luogu.com.cn/problem/P17013  普及−  P17013 [GESP202606 六级] 满二叉树  考点：树的遍历
 *   https://www.luogu.com.cn/problem/P5908  普及−  P5908 猫猫和企鹅  考点：搜索、广度优先搜索 BFS、树的遍历
 *   https://www.luogu.com.cn/problem/P10722  普及  P10722 [GESP202406 六级] 二叉树  考点：树形数据结构、图遍历、树的遍历
 *   https://www.luogu.com.cn/problem/P2814  普及  P2814 家谱  考点：字符串、搜索、图论
 *   https://codeforces.com/problemset/problem/1675/D  CF1300  CF1675D Vertical Paths  考点：图论、实现、树
 *   https://codeforces.com/problemset/problem/1857/D  CF1300  CF1857D Strong Vertices  考点：数学、排序、树
 *   https://www.luogu.com.cn/problem/P3174  普及+/提高−  P3174 [HAOI2009] 毛毛虫  考点：动态规划 DP、树形 DP、树的直径
 *   https://www.luogu.com.cn/problem/P3304  普及+/提高−  P3304 [SDOI2013] 直径  考点：深度优先搜索 DFS、树的直径
 *   https://codeforces.com/problemset/problem/580/C  CF1500  CF580C Kefa and Park  考点：搜索、图论、树
 *   https://codeforces.com/problemset/problem/34/D  CF1600  CF34D Road Map  考点：搜索、图论
 *
 */

// 树用邻接表 g 存，点编号 0..n-1。下面都用 BFS 序代替递归，深度很大的链也不会爆栈。

// 1. 父亲、深度、子树大小。order 为 BFS 序：父亲一定在儿子之前，倒序遍历就是"先儿子后父亲"
struct TreeInfo {
    vector<int> parent, depth, sz, order;
    TreeInfo(const vector<vector<int>> &g, int root = 0) {
        int n = g.size();
        parent.assign(n, -1), depth.assign(n, 0), sz.assign(n, 1);
        order = {root};
        for (size_t i = 0; i < order.size(); i++) {
            int u = order[i];
            for (int v : g[u])
                if (v != parent[u]) parent[v] = u, depth[v] = depth[u] + 1, order.push_back(v);
        }
        for (int i = n - 1; i > 0; i--) sz[parent[order[i]]] += sz[order[i]];
    }
};

// 2. 树的直径（边数）：从任意点出发找最远点 a，再从 a 出发找最远点 b，a-b 就是一条直径
//    返回 {长度, a, b}。带权且有负权时要用树形 DP
tuple<int, int, int> tree_diameter(const vector<vector<int>> &g) {
    auto farthest = [&](int s) {
        vector<int> dist(g.size(), -1), q{s};
        dist[s] = 0;
        for (size_t i = 0; i < q.size(); i++)
            for (int v : g[q[i]])
                if (dist[v] == -1) dist[v] = dist[q[i]] + 1, q.push_back(v);
        int best = s;
        for (int u : q)
            if (dist[u] > dist[best]) best = u;
        return pair<int, int>{best, dist[best]};
    };
    int a = farthest(0).first;
    auto [b, len] = farthest(a);
    return {len, a, b};
}

// 3. 树的重心：删去后剩下的最大连通块最小的点（最多两个，这里返回编号较小的那个）
//    性质：删去重心后每个连通块大小都 <= n / 2
int tree_centroid(const vector<vector<int>> &g) {
    int n = g.size(), best = -1, best_val = INT_MAX;
    TreeInfo t(g, 0);
    for (int u = 0; u < n; u++) {
        int mx = n - t.sz[u];   // 父亲方向的连通块
        for (int v : g[u])
            if (v != t.parent[u]) mx = max(mx, t.sz[v]);
        if (mx < best_val) best_val = mx, best = u;
    }
    return best;
}

// 4. DFS 序：u 的子树恰好对应 ord 中的区间 [tin[u], tout[u])
//    于是"子树加 / 子树求和"就变成序列上的区间操作（配合树状数组或线段树）
struct EulerTour {
    vector<int> tin, tout, ord;
    EulerTour(const vector<vector<int>> &g, int root = 0) {
        int n = g.size();
        tin.assign(n, 0), tout.assign(n, 0);
        vector<int> parent(n, -1), it(n, 0), st{root};
        tin[root] = 0, ord.push_back(root);
        while (!st.empty()) {
            int u = st.back();
            if (it[u] < (int)g[u].size()) {
                int v = g[u][it[u]++];
                if (v == parent[u]) continue;
                parent[v] = u, tin[v] = ord.size(), ord.push_back(v), st.push_back(v);
            } else {
                tout[u] = ord.size(), st.pop_back();
            }
        }
    }
};
