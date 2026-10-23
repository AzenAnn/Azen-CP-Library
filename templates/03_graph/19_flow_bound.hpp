/**
 * 03_graph/19 上下界网络流
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：03_graph/14 网络流：最大流与最小割
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 无源汇上下界可行流：建超级源汇，下界由附加边满足
 *   2. 有源汇上下界可行流：连 t→s 容量 inf 化为无源汇
 *   3. 有源汇上下界最大流：先求可行流，再在残量网络上 s→t 增广
 *   4. 有源汇上下界最小流：先求可行流，再 t→s 退流
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/flow/bound/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P14578  P14578 【模板】无源汇上下界可行流
 *   https://www.luogu.com.cn/problem/P14579  P14579 【模板】有源汇上下界最大流
 *   https://www.luogu.com.cn/problem/P14580  P14580 【模板】有源汇上下界最小流
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P5258  提高  P5258 [JSOI2013] 旅行时的困惑  考点：上下界网络流、贪心
 *   https://www.luogu.com.cn/problem/P2764  省选/NOI−  P2764 最小路径覆盖问题  考点：上下界网络流、网络流、二分图
 *   https://www.luogu.com.cn/problem/P4043  省选/NOI−  P4043 [AHOI2014/JSOI2014] 支线剧情  考点：上下界费用流
 *   https://www.luogu.com.cn/problem/P4553  省选/NOI−  P4553 80 人环游世界  考点：上下界费用流
 *   https://www.luogu.com.cn/problem/P4843  省选/NOI−  P4843 清理雪道  考点：有源汇上下界最小流
 *   https://www.luogu.com.cn/problem/P5192  省选/NOI−  P5192 Shoot the Bullet | 东方文花帖  考点：有源汇上下界最大流
 *
 */

// 上下界网络流。每条边 {u, v, lo, hi} 的流量必须在 [lo, hi] 内。
// 做法：先让每条边流 lo，记录每个点的盈余 d（流入下界 − 流出下界）；新建超级源 S'、汇 T'，
// d > 0 时 S'→x 容量 d，d < 0 时 x→T' 容量 −d，原边容量改成 hi − lo。S'→T' 满流 ⇔ 存在可行流。
// 1. circulation()：无源汇可行流；2. max_flow(s, t) / min_flow(s, t)：有源汇的最大 / 最小流（无解返回 LLONG_MIN）。
//    有源汇时要求没有流入 s、流出 t 的边（题目里的常见设定）；否则把 s、t 拆点或改用无源汇模型。
// 求出可行解后 flow_of(i) 给出第 i 条边的流量。
struct BoundedFlow {
    struct Flow {   // 内置 Dinic，避免与 03_graph/14 重名
        struct E { int to; ll cap; };
        vector<E> e;
        vector<vector<int>> g;
        vector<int> lv, it;
        Flow(int n) : g(n), lv(n), it(n) {}
        int add(int u, int v, ll c) {
            g[u].push_back(e.size()), e.push_back({v, c});
            g[v].push_back(e.size()), e.push_back({u, 0});
            return e.size() - 2;
        }
        bool bfs(int s, int t) {
            fill(lv.begin(), lv.end(), -1);
            queue<int> q;
            lv[s] = 0, q.push(s);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int id : g[u])
                    if (e[id].cap > 0 && lv[e[id].to] < 0) lv[e[id].to] = lv[u] + 1, q.push(e[id].to);
            }
            return lv[t] >= 0;
        }
        ll dfs(int u, int t, ll f) {
            if (u == t) return f;
            for (int &i = it[u]; i < (int)g[u].size(); i++) {
                int id = g[u][i], v = e[id].to;
                if (e[id].cap > 0 && lv[v] == lv[u] + 1)
                    if (ll d = dfs(v, t, min(f, e[id].cap))) {
                        e[id].cap -= d, e[id ^ 1].cap += d;
                        return d;
                    }
            }
            return 0;
        }
        ll maxflow(int s, int t) {
            ll f = 0;
            while (bfs(s, t)) {
                fill(it.begin(), it.end(), 0);
                while (ll d = dfs(s, t, LLONG_MAX / 4)) f += d;
            }
            return f;
        }
    };
    int n;
    vector<array<ll, 4>> edges;
    vector<int> eid;   // 原边在 Flow 里的编号
    Flow *F = nullptr;
    BoundedFlow(int n) : n(n) {}
    ~BoundedFlow() { delete F; }
    void add_edge(int u, int v, ll lo, ll hi) { edges.push_back({u, v, lo, hi}); }
    // 建图并检查可行性（额外加 t→s 容量无穷的边时 s、t 有效）。返回 t→s 边编号（没有为 -1），不可行时 ok = false
    int build(int s, int t, bool &ok) {
        delete F;
        F = new Flow(n + 2);
        int S = n, T = n + 1;
        vector<ll> d(n, 0);
        eid.clear();
        for (auto [u, v, lo, hi] : edges) eid.push_back(F->add(u, v, hi - lo)), d[v] += lo, d[u] -= lo;
        int back = s >= 0 ? F->add(t, s, LLONG_MAX / 4) : -1;
        ll need = 0;
        for (int x = 0; x < n; x++) {
            if (d[x] > 0) F->add(S, x, d[x]), need += d[x];
            if (d[x] < 0) F->add(x, T, -d[x]);
        }
        ok = F->maxflow(S, T) == need;
        return back;
    }
    bool circulation() {
        bool ok;
        build(-1, -1, ok);
        return ok;
    }
    ll max_flow(int s, int t) {
        bool ok;
        int back = build(s, t, ok);
        if (!ok) return LLONG_MIN;
        ll f = F->e[back ^ 1].cap;   // t→s 边上的流量就是当前可行流的流量
        F->e[back].cap = F->e[back ^ 1].cap = 0;
        return f + F->maxflow(s, t);
    }
    ll min_flow(int s, int t) {
        bool ok;
        int back = build(s, t, ok);
        if (!ok) return LLONG_MIN;
        ll f = F->e[back ^ 1].cap;
        F->e[back].cap = F->e[back ^ 1].cap = 0;
        return f - F->maxflow(t, s);   // 尽量把流量退回去
    }
    ll flow_of(int i) const { return edges[i][2] + F->e[eid[i] ^ 1].cap; }
};
