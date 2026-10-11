/**
 * 04_tree/07 点分治
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：04_tree/01 树的基础：直径、重心、DFS 序、01_basic/10 分治
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 找重心并递归
 *   2. 统计经过重心的路径
 *   3. 点分树
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/tree-divide/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3806  P3806 【模板】点分治
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/1174/F  CF2400  CF1174F Ehab and the Big Finale  考点：构造、分治、图论
 *   https://codeforces.com/problemset/problem/914/E  CF2400  CF914E Palindromes in a Tree  考点：位运算、数据结构、分治
 *   https://www.luogu.com.cn/problem/P2056  省选/NOI−  P2056 [ZJOI2007] 捉迷藏  考点：线段树、点分治、树的直径
 *   https://www.luogu.com.cn/problem/P2664  省选/NOI−  P2664 树上游戏  考点：点分治
 *   https://www.luogu.com.cn/problem/P3241  省选/NOI−  P3241 [HNOI2015] 开店  考点：点分治、最近公共祖先 LCA、树链剖分
 *   https://www.luogu.com.cn/problem/P3345  省选/NOI−  P3345 [ZJOI2015] 幻想乡战略游戏  考点：线段树、点分治、树链剖分
 *   https://www.luogu.com.cn/problem/P6329  省选/NOI−  P6329 【模板】点分树 / 震波  考点：点分治、树状数组、动态树分治
 *   https://codeforces.com/problemset/problem/293/E  CF2700  CF293E Close Vertices  考点：数据结构、分治、树
 *   https://codeforces.com/problemset/problem/776/F  CF2800  CF776F Sherlock's bet to Moriarty  考点：构造、数据结构、分治
 *   https://www.luogu.com.cn/problem/P3920  NOI/NOI+/CTS  P3920 [WC2014] 紫荆花之恋  考点：点分治、平衡树、分治
 *   https://www.luogu.com.cn/problem/P4220  NOI/NOI+/CTS  P4220 [WC2018] 通道  考点：并查集、点分治、分治
 *   https://www.luogu.com.cn/problem/P4565  NOI/NOI+/CTS  P4565 [CTSC2018] 暴力写挂  考点：线段树、分治、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P5311  NOI/NOI+/CTS  P5311 [Ynoi2011] 成都七中  考点：点分治、树状数组
 *   https://www.luogu.com.cn/problem/P5912  NOI/NOI+/CTS  P5912 [POI 2004] JAS  考点：贪心、树的重心
 *   https://www.luogu.com.cn/problem/P9058  NOI/NOI+/CTS  P9058 [Ynoi2004] rpmtdq  考点：线段树、点分治、树状数组
 *
 */

// 点分治：每次找当前连通块的重心 c，统计"经过 c 的路径"，然后删掉 c，对剩下的各个连通块递归。
// 重心保证每个连通块大小至少减半，递归 O(log n) 层，每层总共 O(n)，再乘上统计的代价。点编号 0..n-1

// 找到包含 s 的连通块（不经过已删除的点）的重心
int find_centroid(const vector<vector<pair<int, ll>>> &g, const vector<bool> &removed, int s) {
    vector<int> order{s}, fa{-1};
    vector<int> sz;
    unordered_map<int, int> idx{{s, 0}};
    for (size_t i = 0; i < order.size(); i++)
        for (auto [v, w] : g[order[i]])
            if (!removed[v] && v != fa[i]) idx[v] = order.size(), order.push_back(v), fa.push_back(order[i]);
    int tot = order.size(), best = s, best_val = INT_MAX;
    sz.assign(tot, 1);
    vector<int> mx(tot, 0);
    for (int i = tot - 1; i > 0; i--) {
        int p = idx[fa[i]];
        sz[p] += sz[i], mx[p] = max(mx[p], sz[i]);
    }
    for (int i = 0; i < tot; i++) {
        int m = max(mx[i], tot - sz[i]);
        if (m < best_val) best_val = m, best = order[i];
    }
    return best;
}

// 1. 例题（洛谷 P3806）：对每个询问 k，判断树上是否存在距离恰好为 k 的点对。边权非负
vector<bool> path_length_exists(const vector<vector<pair<int, ll>>> &g, const vector<ll> &ks) {
    int n = g.size(), q = ks.size();
    vector<bool> removed(n, false), ans(q, false);
    ll maxk = q ? *max_element(ks.begin(), ks.end()) : 0;
    vector<int> st{0};   // 待处理的连通块（用其中任意一个点表示）
    while (!st.empty()) {
        int c = find_centroid(g, removed, st.back());
        st.pop_back();
        set<ll> seen{0};   // 之前处理过的子树中，到 c 的距离
        for (auto [v, w] : g[c]) {
            if (removed[v]) continue;
            vector<ll> ds;   // 这棵子树中各点到 c 的距离
            vector<tuple<int, int, ll>> bfs{{v, c, w}};
            for (size_t i = 0; i < bfs.size(); i++) {
                auto [u, p, d] = bfs[i];
                if (d > maxk) continue;   // 超过最大询问的距离不用再走
                ds.push_back(d);
                for (auto [x, wx] : g[u])
                    if (x != p && !removed[x]) bfs.push_back({x, u, d + wx});
            }
            for (int i = 0; i < q; i++)
                if (!ans[i])
                    for (ll d : ds)
                        if (seen.count(ks[i] - d)) { ans[i] = true; break; }
            seen.insert(ds.begin(), ds.end());   // 先查询再合并，保证两端来自不同子树
        }
        removed[c] = true;
        for (auto [v, w] : g[c])
            if (!removed[v]) st.push_back(v);
    }
    return ans;
}

// 2. 点分树：把每层的重心连成一棵树（重心 → 下一层子连通块的重心），树高 O(log n)。
//    原树上 u、v 之间的路径一定经过它们在点分树上的 LCA，常用于"带修改的点分治"。
//    返回点分树中每个点的父亲（根为 -1）
vector<int> centroid_tree(const vector<vector<int>> &g0) {
    int n = g0.size();
    vector<vector<pair<int, ll>>> g(n);
    for (int u = 0; u < n; u++)
        for (int v : g0[u]) g[u].push_back({v, 1});
    vector<bool> removed(n, false);
    vector<int> par(n, -1);
    vector<pair<int, int>> st{{0, -1}};   // (连通块中的一个点, 上一层的重心)
    while (!st.empty()) {
        auto [s, p] = st.back();
        st.pop_back();
        int c = find_centroid(g, removed, s);
        par[c] = p, removed[c] = true;
        for (auto [v, w] : g[c])
            if (!removed[v]) st.push_back({v, c});
    }
    return par;
}
