/**
 * 03_graph/05 强连通分量与缩点
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：03_graph/02 拓扑排序
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Tarjan 求 SCC（dfn / low）
 *   2. 缩点成 DAG 后再 DP
 *   3. Kosaraju
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/scc/
 *   cp-algorithms  https://cp-algorithms.com/graph/strongly-connected-components.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3387  P3387 【模板】缩点 / 强连通分量
 *   https://www.luogu.com.cn/problem/B3609  B3609 [图论与代数结构 701] 强连通分量
 *   https://judge.yosupo.jp/problem/scc  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1455  普及  P1455 搭配购买  考点：并查集、背包 DP、强连通分量
 *   https://www.luogu.com.cn/problem/P2194  普及  P2194 HXY烧情侣  考点：图论、强连通分量
 *   https://www.luogu.com.cn/problem/P3916  普及  P3916 图的遍历  考点：搜索、图论、广度优先搜索 BFS
 *   https://www.luogu.com.cn/problem/P4306  普及  P4306 [JSOI2010] 连通数  考点：枚举、图论建模、连通块
 *   https://www.luogu.com.cn/problem/P1726  普及+/提高−  P1726 上白泽慧音  考点：图论、强连通分量、Tarjan
 *   https://www.luogu.com.cn/problem/P2341  普及+/提高−  P2341 [USACO03FALL / HAOI2006] 受欢迎的牛 G  考点：图论、图论建模、强连通分量
 *   https://www.luogu.com.cn/problem/P2746  普及+/提高−  P2746 [IOI 1996 / USACO5.3] 校园网 Network of Schools  考点：图论、强连通分量、Tarjan
 *   https://www.luogu.com.cn/problem/P2863  普及+/提高−  P2863 [USACO06JAN] The Cow Prom S  考点：强连通分量、Tarjan
 *   https://codeforces.com/problemset/problem/427/C  CF1700  CF427C Checkposts  考点：搜索、图论、双指针
 *   https://www.luogu.com.cn/problem/P1407  提高  P1407 [国家集训队] 稳定婚姻  考点：网络流、图论建模、强连通分量
 *   https://www.luogu.com.cn/problem/P2515  提高  P2515 [HAOI2010] 软件安装  考点：动态规划 DP、背包 DP、树形 DP
 *   https://www.luogu.com.cn/problem/P2812  提高  P2812 校园网络 / [IOI 1996 / USACO5.3] 校园网 Network of Schools 加强版  考点：图论、强连通分量、Tarjan
 *   https://codeforces.com/problemset/problem/999/E  CF2000  CF999E Reachability from the Capital  考点：搜索、图论、贪心
 *   https://codeforces.com/problemset/problem/1547/G  CF2100  CF1547G How Many Paths?  考点：搜索、DP、图论
 *   https://codeforces.com/problemset/problem/894/E  CF2100  CF894E Ralph and Mushrooms  考点：DP、图论
 *
 */

// Tarjan 求强连通分量：dfn[u] 为 DFS 时间戳，low[u] 为 u 能回溯到的栈中最小时间戳。
// low[u] == dfn[u] 时，栈中 u 及其上方的点构成一个 SCC。O(n + m)
// 点编号 0..n-1。注意：Tarjan 得到的 SCC 编号是"逆拓扑序"，编号大的 SCC 在拓扑序中靠前。
// 递归深度可达 n；Codeforces 等平台栈空间足够，本地测试大数据时可能需要 ulimit -s unlimited
struct SCC {
    int n, cnt = 0, timer = 0;
    vector<vector<int>> g;
    vector<int> dfn, low, comp, stk;
    vector<bool> in_stk;
    SCC(int n) : n(n), g(n) {}
    void add_edge(int u, int v) { g[u].push_back(v); }
    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        stk.push_back(u), in_stk[u] = true;
        for (int v : g[u]) {
            if (!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
            else if (in_stk[v]) low[u] = min(low[u], dfn[v]);
        }
        if (low[u] == dfn[u]) {
            while (true) {
                int v = stk.back();
                stk.pop_back(), in_stk[v] = false;
                comp[v] = cnt;
                if (v == u) break;
            }
            cnt++;
        }
    }
    int run() {   // 返回 SCC 个数，comp[u] 为 u 所在 SCC 的编号
        dfn.assign(n, 0), low.assign(n, 0), comp.assign(n, -1), in_stk.assign(n, false);
        for (int u = 0; u < n; u++)
            if (!dfn[u]) dfs(u);
        return cnt;
    }
    // 缩点后的 DAG（已去掉自环，可能有重边）；需要先调用 run()
    vector<vector<int>> dag() const {
        vector<vector<int>> h(cnt);
        for (int u = 0; u < n; u++)
            for (int v : g[u])
                if (comp[u] != comp[v]) h[comp[u]].push_back(comp[v]);
        return h;
    }
};
