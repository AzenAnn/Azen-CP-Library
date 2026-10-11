/**
 * 03_graph/12 最小费用最大流
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：03_graph/11 网络流：最大流与最小割
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. SSP（SPFA 找最短增广路）
 *   2. 原始对偶（Dijkstra + 势能）
 *   3. 费用流建模
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/flow/min-cost/
 *   cp-algorithms  https://cp-algorithms.com/graph/min_cost_flow.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph_flow.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3381  P3381 【模板】最小费用最大流
 *   https://judge.yosupo.jp/problem/min_cost_b_flow  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2045  省选/NOI−  P2045 方格取数加强版  考点：网络流、费用流
 *   https://www.luogu.com.cn/problem/P2050  省选/NOI−  P2050 [NOI2012] 美食节  考点：网络流、费用流
 *   https://www.luogu.com.cn/problem/P2053  省选/NOI−  P2053 [SCOI2007] 修车  考点：网络流、费用流
 *   https://www.luogu.com.cn/problem/P2469  省选/NOI−  P2469 [SDOI2010] 星际竞速  考点：网络流、费用流
 *   https://www.luogu.com.cn/problem/P2604  省选/NOI−  P2604 [ZJOI2010] 网络扩容  考点：网络流、图论建模、费用流
 *   https://www.luogu.com.cn/problem/P2770  省选/NOI−  P2770 航空路线问题  考点：网络流、费用流
 *   https://www.luogu.com.cn/problem/P3705  省选/NOI−  P3705 [SDOI2017] 新生舞会  考点：二分、分数规划、费用流
 *   https://www.luogu.com.cn/problem/P4012  省选/NOI−  P4012 深海机器人问题  考点：图论建模、费用流
 *   https://www.luogu.com.cn/problem/P4043  省选/NOI−  P4043 [AHOI2014/JSOI2014] 支线剧情  考点：网络流、上下界网络流、费用流
 *   https://codeforces.com/problemset/problem/1107/F  CF2600  CF1107F Vasya and Endless Credits  考点：DP、网络流、图匹配
 *   https://www.luogu.com.cn/problem/P15246  NOI/NOI+/CTS  P15246 [WC2026] 猫和老鼠  考点：cdq 分治、费用流
 *   https://www.luogu.com.cn/problem/P4003  NOI/NOI+/CTS  P4003 [清华集训 2017] 无限之环  考点：网络流、费用流
 *   https://www.luogu.com.cn/problem/P4249  NOI/NOI+/CTS  P4249 [WC2007] 剪刀石头布  考点：图论、图论建模、费用流
 *   https://www.luogu.com.cn/problem/P4542  NOI/NOI+/CTS  P4542 [ZJOI2011] 营救皮卡丘  考点：图论建模、最短路、费用流
 *   https://www.luogu.com.cn/problem/P5331  NOI/NOI+/CTS  P5331 [SNOI2019] 通信  考点：网络流、cdq 分治、图论建模
 *
 */

// 最小费用最大流：在流量最大的前提下费用最小（洛谷 P3381）。
// SSP（逐次最短路）：每次沿费用最短的增广路增广。要求初始图中没有负费用的环。点编号 0..n-1

// 1. SPFA 版：允许负费用边，写法最简单，比赛中最常用
struct MCMF {
    struct Edge {
        int to;
        ll cap, cost;
    };
    int n;
    vector<Edge> e;
    vector<vector<int>> g;
    MCMF(int n) : n(n), g(n) {}
    int add_edge(int u, int v, ll cap, ll cost) {
        g[u].push_back(e.size()), e.push_back({v, cap, cost});
        g[v].push_back(e.size()), e.push_back({u, 0, -cost});   // 反向边费用为负
        return e.size() - 2;
    }
    // 返回 {最大流, 最小费用}；limit 为流量上限
    pair<ll, ll> run(int s, int t, ll limit = LLONG_MAX) {
        ll flow = 0, cost = 0;
        const ll INF = LLONG_MAX / 4;
        while (flow < limit) {
            vector<ll> dist(n, INF);
            vector<int> pre(n, -1);   // 到达该点的边
            vector<bool> inq(n, false);
            queue<int> q;
            dist[s] = 0, q.push(s), inq[s] = true;
            while (!q.empty()) {
                int u = q.front();
                q.pop(), inq[u] = false;
                for (int id : g[u]) {
                    int v = e[id].to;
                    if (e[id].cap > 0 && dist[u] + e[id].cost < dist[v]) {
                        dist[v] = dist[u] + e[id].cost, pre[v] = id;
                        if (!inq[v]) inq[v] = true, q.push(v);
                    }
                }
            }
            if (dist[t] == INF) break;
            ll f = limit - flow;
            for (int v = t; v != s; v = e[pre[v] ^ 1].to) f = min(f, e[pre[v]].cap);
            for (int v = t; v != s; v = e[pre[v] ^ 1].to) e[pre[v]].cap -= f, e[pre[v] ^ 1].cap += f;
            flow += f, cost += f * dist[t];
        }
        return {flow, cost};
    }
};

// 2. 原始对偶（Primal-Dual）：给每个点一个势能 h，边的"约化费用" cost + h[u] - h[v] 恒非负，
//    于是每轮可以用 Dijkstra 代替 SPFA，最坏复杂度有保证。有负费用边时先用一次 SPFA 求初始势能
struct MCMFDijkstra {
    struct Edge {
        int to;
        ll cap, cost;
    };
    int n;
    vector<Edge> e;
    vector<vector<int>> g;
    MCMFDijkstra(int n) : n(n), g(n) {}
    int add_edge(int u, int v, ll cap, ll cost) {
        g[u].push_back(e.size()), e.push_back({v, cap, cost});
        g[v].push_back(e.size()), e.push_back({u, 0, -cost});
        return e.size() - 2;
    }
    pair<ll, ll> run(int s, int t, ll limit = LLONG_MAX) {
        const ll INF = LLONG_MAX / 4;
        vector<ll> h(n, 0), dist(n);
        vector<int> pre(n);
        {   // 初始势能：SPFA 求 s 到各点的最短路（只走有容量的边）
            vector<bool> inq(n, false);
            fill(h.begin(), h.end(), INF);
            queue<int> q;
            h[s] = 0, q.push(s);
            while (!q.empty()) {
                int u = q.front();
                q.pop(), inq[u] = false;
                for (int id : g[u])
                    if (e[id].cap > 0 && h[u] + e[id].cost < h[e[id].to]) {
                        h[e[id].to] = h[u] + e[id].cost;
                        if (!inq[e[id].to]) inq[e[id].to] = true, q.push(e[id].to);
                    }
            }
            for (auto &x : h)
                if (x == INF) x = 0;
        }
        ll flow = 0, cost = 0;
        while (flow < limit) {
            fill(dist.begin(), dist.end(), INF);
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
            dist[s] = 0, pq.push({0, s});
            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                if (d > dist[u]) continue;
                for (int id : g[u]) {
                    int v = e[id].to;
                    ll nd = d + e[id].cost + h[u] - h[v];   // 约化费用 >= 0
                    if (e[id].cap > 0 && nd < dist[v]) dist[v] = nd, pre[v] = id, pq.push({nd, v});
                }
            }
            if (dist[t] == INF) break;
            for (int v = 0; v < n; v++)
                if (dist[v] < INF) h[v] += dist[v];
            ll f = limit - flow;
            for (int v = t; v != s; v = e[pre[v] ^ 1].to) f = min(f, e[pre[v]].cap);
            for (int v = t; v != s; v = e[pre[v] ^ 1].to) e[pre[v]].cap -= f, e[pre[v] ^ 1].cap += f;
            flow += f, cost += f * (h[t] - h[s]);
        }
        return {flow, cost};
    }
};
