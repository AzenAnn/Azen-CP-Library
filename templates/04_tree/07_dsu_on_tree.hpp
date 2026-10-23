/**
 * 04_tree/07 树上启发式合并
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：04_tree/05 树链剖分
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 保留重儿子信息，暴力合并轻儿子
 *   2. 复杂度 O(n log n) 的原因
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/dsu-on-tree/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph_tree.go
 *
 * 【模板题 / 入门题】
 *   https://codeforces.com/problemset/problem/600/E  CF600E Lomsat gelral
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1456  提高  P1456 Monkey King  考点：可并堆、启发式合并
 *   https://www.luogu.com.cn/problem/P6279  提高  P6279 [USACO20OPEN] Favorite Colors G  考点：并查集、启发式合并
 *   https://www.luogu.com.cn/problem/P7118  提高  P7118 Galgame  考点：动态规划 DP、动态规划优化、组合数学
 *   https://www.luogu.com.cn/problem/P8907  提高  P8907 [USACO22DEC] Making Friends P  考点：启发式合并
 *   https://codeforces.com/problemset/problem/161/D  CF1800  CF161D Distance in Tree  考点：搜索、DP、树
 *   https://www.luogu.com.cn/problem/P3521  提高+/省选−  P3521 [POI 2011] ROT-Tree Rotations  考点：线段树、树上启发式合并、线段树合并
 *   https://www.luogu.com.cn/problem/P3899  提高+/省选−  P3899 [湖南集训] 更为厉害  考点：线段树、树状数组、树上启发式合并
 *   https://codeforces.com/problemset/problem/2127/E  CF2100  CF2127E Ancient Tree  考点：构造、数据结构、搜索
 *   https://codeforces.com/problemset/problem/570/D  CF2200  CF570D Tree Requests  考点：二分、位运算、构造
 *   https://codeforces.com/problemset/problem/1805/E  CF2300  CF1805E There Should Be a Lot of Maximums  考点：暴力、数据结构、搜索
 *   https://codeforces.com/problemset/problem/1709/E  CF2400  CF1709E XOR Tree  考点：位运算、数据结构、搜索
 *   https://codeforces.com/problemset/problem/246/E  CF2400  CF246E Blood Cousins Return  考点：二分、数据结构、搜索
 *   https://www.luogu.com.cn/problem/P5666  省选/NOI−  P5666 [CSP-S 2019] 树的重心  考点：倍增、树状数组、树上启发式合并
 *   https://www.luogu.com.cn/problem/P9886  省选/NOI−  P9886 [ICPC 2018 Qingdao R] Kawa Exam  考点：树上启发式合并
 *   https://codeforces.com/problemset/problem/715/C  CF2700  CF715C Digit Tree  考点：搜索、分治、并查集
 *
 */

// 树上启发式合并（DSU on tree）：离线统计"每棵子树"的信息，O(n log n)
// 做法：先递归处理轻儿子并清空它们的贡献；再处理重儿子并保留贡献；
//       然后把轻儿子子树中的点和 u 自己逐个加进来，得到 u 的答案。
// 每个点只会在"它到根的路径上的轻边"处被重新加入，轻边不超过 O(log n) 条，所以总复杂度 O(n log n)
// 例题 CF600E：对每个点，求它的子树中出现次数最多的颜色的编号之和。
// 递归深度可达 n（Codeforces 上没有问题）。color[v] 为非负整数，点编号 0..n-1
vector<ll> dsu_on_tree(const vector<vector<int>> &g, const vector<int> &color, int root = 0) {
    int n = g.size();
    vector<int> fa(n, -1), sz(n, 1), heavy(n, -1), tin(n), tout(n), ord, order{root};
    for (size_t i = 0; i < order.size(); i++)
        for (int v : g[order[i]])
            if (v != fa[order[i]]) fa[v] = order[i], order.push_back(v);
    for (int i = n - 1; i > 0; i--) {
        int v = order[i], p = fa[v];
        sz[p] += sz[v];
        if (heavy[p] == -1 || sz[v] > sz[heavy[p]]) heavy[p] = v;
    }
    {   // DFS 序：子树 u 对应 ord[tin[u] .. tout[u])
        vector<int> st{root};
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            tin[u] = ord.size(), ord.push_back(u), tout[u] = tin[u] + sz[u];
            for (int v : g[u])
                if (v != fa[u]) st.push_back(v);
        }
    }
    vector<int> cnt(*max_element(color.begin(), color.end()) + 1, 0);
    int mx = 0;
    ll best = 0;   // 当前出现次数的最大值、达到最大值的颜色编号之和
    vector<ll> ans(n);
    auto add = [&](int v) {
        int c = color[v];
        if (++cnt[c] > mx) mx = cnt[c], best = c;
        else if (cnt[c] == mx) best += c;
    };
    function<void(int, bool)> dfs = [&](int u, bool keep) {
        for (int v : g[u])
            if (v != fa[u] && v != heavy[u]) dfs(v, false);
        if (heavy[u] != -1) dfs(heavy[u], true);
        for (int v : g[u])
            if (v != fa[u] && v != heavy[u])
                for (int i = tin[v]; i < tout[v]; i++) add(ord[i]);
        add(u);
        ans[u] = best;
        if (!keep) {   // 清空整棵子树的贡献
            for (int i = tin[u]; i < tout[u]; i++) cnt[color[ord[i]]]--;
            mx = 0, best = 0;
        }
    };
    dfs(root, true);
    return ans;
}
