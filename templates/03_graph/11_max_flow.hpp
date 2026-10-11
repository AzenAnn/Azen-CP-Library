/**
 * 03_graph/11 网络流：最大流与最小割
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：03_graph/03 最短路
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Dinic
 *   2. 最大流 = 最小割
 *   3. 常见建模：拆点、超级源汇
 *   4. 用最大流做二分图匹配
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/flow/max-flow/
 *   OI-wiki        https://oi-wiki.org/graph/flow/min-cut/
 *   cp-algorithms  https://cp-algorithms.com/graph/dinic.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph_flow.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3376  P3376 【模板】网络最大流
 *   https://www.luogu.com.cn/problem/P2756  P2756 飞行员配对方案问题
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P6268  提高  P6268 [SHOI2002] 舞会  考点：网络流、图论建模、二分图
 *   https://www.luogu.com.cn/problem/P7368  提高  P7368 [USACO05NOV] Asteroids G  考点：网络流、二分图
 *   https://codeforces.com/problemset/problem/1437/C  CF1800  CF1437C Chef Monocarp  考点：DP、网络流、图匹配
 *   https://codeforces.com/problemset/problem/1525/D  CF1800  CF1525D Armchairs  考点：DP、网络流、图匹配
 *   https://codeforces.com/problemset/problem/1360/G  CF1900  CF1360G A/B Matrix  考点：构造、贪心、数学
 *   https://www.luogu.com.cn/problem/P1345  提高+/省选−  P1345 [USACO5.4] 奶牛的电信 Telecowmunication  考点：图论、网络流、最小割
 *   https://www.luogu.com.cn/problem/P2740  提高+/省选−  P2740 [USACO4.2] 草地排水 Drainage Ditches  考点：网络流
 *   https://www.luogu.com.cn/problem/P2766  提高+/省选−  P2766 最长不下降子序列问题  考点：动态规划 DP、贪心、网络流
 *   https://codeforces.com/problemset/problem/498/C  CF2100  CF498C Array and Operations  考点：网络流、图匹配、数论
 *   https://codeforces.com/problemset/problem/546/E  CF2100  CF546E Soldier and Traveling  考点：网络流、图论、数学
 *   https://codeforces.com/problemset/problem/1082/G  CF2400  CF1082G Petya and Graph  考点：网络流、图论
 *   https://www.luogu.com.cn/problem/P1251  省选/NOI−  P1251 餐巾计划问题  考点：贪心、网络流、费用流
 *   https://www.luogu.com.cn/problem/P2762  省选/NOI−  P2762 太空飞行计划问题  考点：网络流、最小割
 *   https://www.luogu.com.cn/problem/P3980  省选/NOI−  P3980 [NOI2008] 志愿者招募  考点：网络流、图论建模、上下界网络流
 *   https://codeforces.com/problemset/problem/2026/E  CF2500  CF2026E Best Subsequence  考点：位运算、搜索、网络流
 *
 */

// Dinic 最大流：每轮 BFS 按距离分层，只沿"层数 + 1"的边 DFS 增广，并用当前弧优化跳过已经满的边。
// 一般图 O(n^2 m)，单位容量图 O(m√m)，二分图匹配 O(m√n)；实际跑得比上界快很多。
// 加边返回正向边的编号 id，flow(id) 为这条边上的流量。点编号 0..n-1
// 常见建模：
//   最小割 = 最大流；割的方案：跑完后从 s 出发沿剩余容量 > 0 的边能到达的点为 S 集合（min_cut）
//   点有容量：把点 v 拆成 v_in -> v_out，容量为点容量
//   多源多汇：加超级源点 / 超级汇点
//   二分图最大匹配：s -> 左点（容量 1），左点 -> 右点（容量 1），右点 -> t（容量 1）
struct Dinic {
    struct Edge {
        int to;
        ll cap;
    };
    int n;
    vector<Edge> e;
    vector<vector<int>> g;
    vector<int> level, it;
    Dinic(int n) : n(n), g(n) {}
    int add_edge(int u, int v, ll cap) {   // 第 id 条边与其反向边编号为 id、id ^ 1
        g[u].push_back(e.size()), e.push_back({v, cap});
        g[v].push_back(e.size()), e.push_back({u, 0});
        return e.size() - 2;
    }
    bool bfs(int s, int t) {
        level.assign(n, -1);
        queue<int> q;
        q.push(s), level[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : g[u])
                if (e[id].cap > 0 && level[e[id].to] == -1) level[e[id].to] = level[u] + 1, q.push(e[id].to);
        }
        return level[t] != -1;
    }
    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        ll res = 0;
        for (int &i = it[u]; i < (int)g[u].size(); i++) {   // 当前弧：从上次停下的边继续
            int id = g[u][i], v = e[id].to;
            if (e[id].cap <= 0 || level[v] != level[u] + 1) continue;
            ll d = dfs(v, t, min(f - res, e[id].cap));
            e[id].cap -= d, e[id ^ 1].cap += d, res += d;
            if (res == f) return res;
        }
        level[u] = -1;   // 这个点已经推不出流了
        return res;
    }
    ll max_flow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            it.assign(n, 0);
            flow += dfs(s, t, LLONG_MAX);
        }
        return flow;
    }
    ll flow(int id) const { return e[id ^ 1].cap; }
    vector<bool> min_cut(int s) const {   // 跑完最大流后调用：返回 S 集合
        vector<bool> vis(n, false);
        vector<int> st{s};
        vis[s] = true;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int id : g[u])
                if (e[id].cap > 0 && !vis[e[id].to]) vis[e[id].to] = true, st.push_back(e[id].to);
        }
        return vis;
    }
};
