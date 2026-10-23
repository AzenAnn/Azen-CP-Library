/**
 * 03_graph/20 一般图匹配（带花树 Blossom）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：03_graph/09 二分图
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 一般图最大匹配与二分图的区别：奇环（花）的处理
 *   2. 带花树算法：BFS 找增广路，遇到偶环缩花
 *   3. 复杂度 O(n³)，实现细节：并查集维护花、lca 找花
 *   4. 应用：一般图最大匹配、最大权匹配（带权带花树）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/graph-matching/general-match/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P6113  P6113 【模板】一般图最大匹配
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4258  省选/NOI−  P4258 [WC2016] 挑战NPC  考点：每个筐拆成 3 个点，一般图最大匹配
 *   https://www.luogu.com.cn/problem/P6699  NOI/NOI+/CTS  P6699 【模板】一般图最大权匹配  考点：一般图最大权匹配（带权带花树）
 *
 */

// 一般图最大匹配（带花树，Edmonds 算法）：从每个未匹配点 BFS 找增广路，遇到奇环（花）就把它缩成一个点。O(n^3)。
// 点 0..n-1。match[v] 为 v 的匹配点（-1 表示未匹配），solve() 返回匹配数。
struct Blossom {
    int n;
    vector<vector<int>> g;
    vector<int> match, pre, base;
    vector<char> used, in_blossom;
    Blossom(int n) : n(n), g(n), match(n, -1), pre(n), base(n), used(n), in_blossom(n) {}
    void add_edge(int u, int v) {
        if (u == v) return;
        g[u].push_back(v), g[v].push_back(u);
    }
    int lca(int a, int b) {   // 交错树上两点所在花基的最近公共祖先
        vector<char> vis(n, 0);
        while (true) {
            a = base[a], vis[a] = 1;
            if (match[a] == -1) break;
            a = pre[match[a]];
        }
        while (true) {
            b = base[b];
            if (vis[b]) return b;
            b = pre[match[b]];
        }
    }
    void mark_path(int v, int b, int child) {   // 把 v 到花基 b 的路径标进花里，同时反向记录 pre
        while (base[v] != b) {
            in_blossom[base[v]] = in_blossom[base[match[v]]] = 1;
            pre[v] = child, child = match[v], v = pre[match[v]];
        }
    }
    int find_path(int root) {   // 返回增广路的终点，没有返回 -1
        fill(used.begin(), used.end(), 0), fill(pre.begin(), pre.end(), -1);
        iota(base.begin(), base.end(), 0);
        used[root] = 1;
        vector<int> q = {root};
        for (size_t h = 0; h < q.size(); h++) {
            int v = q[h];
            for (int to : g[v]) {
                if (base[v] == base[to] || match[v] == to) continue;
                if (to == root || (match[to] != -1 && pre[match[to]] != -1)) {   // 偶点碰到偶点：奇环，缩花
                    int cur = lca(v, to);
                    fill(in_blossom.begin(), in_blossom.end(), 0);
                    mark_path(v, cur, to), mark_path(to, cur, v);
                    for (int i = 0; i < n; i++)
                        if (in_blossom[base[i]]) {
                            base[i] = cur;
                            if (!used[i]) used[i] = 1, q.push_back(i);
                        }
                } else if (pre[to] == -1) {
                    pre[to] = v;
                    if (match[to] == -1) return to;
                    used[match[to]] = 1, q.push_back(match[to]);
                }
            }
        }
        return -1;
    }
    int solve() {
        int res = 0;
        for (int v = 0; v < n; v++)
            if (match[v] == -1) {
                int x = find_path(v);
                if (x == -1) continue;
                res++;
                while (x != -1) {   // 沿 pre / match 交替翻转
                    int pv = pre[x], ppv = match[pv];
                    match[x] = pv, match[pv] = x, x = ppv;
                }
            }
        return res;
    }
};
