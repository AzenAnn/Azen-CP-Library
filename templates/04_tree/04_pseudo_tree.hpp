/**
 * 04_tree/04 基环树
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：04_tree/01 树的基础：直径、重心、DFS 序、06_dp/05 树形 DP 与换根 DP、02_ds/02 单调队列
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 定义：n 个点 n 条边的连通图 = 一棵树加一条边，恰好有一个环；每个点出度为 1 的有向图（内向基环树森林）也很常见
 *   2. 找环：拓扑排序不断删去度数为 1 的点，剩下的就是环；或者 DFS 找返祖边。注意重边构成的二元环
 *   3. 思路一"断环为链"：环上每个点挂着一棵树，先在树上 DP，再在环上做（环复制一倍 + 单调队列），如 Island 求直径
 *   4. 思路二"断一条环边"：删掉环上一条边 (u, v) 变成树，分别强制 u、v 不选做两次树形 DP，如骑士（最大独立集）
 *   5. 内向基环树（函数图）：每个点沿 nxt 走最终进入一个环，信息传递求最小环、倍增跳 k 步
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/tree-basic/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2661  P2661 [NOIP 2015 提高组] 信息传递
 *   https://www.luogu.com.cn/problem/P2607  P2607 [ZJOI2008] 骑士
 *   https://www.luogu.com.cn/problem/P4381  P4381 [IOI 2008] Island
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P8655  普及  P8655 [蓝桥杯 2017 国 B] 发现环  考点：基环树
 *   https://www.luogu.com.cn/problem/P2921  普及+/提高−  P2921 [USACO08DEC] Trick or Treat on the Farm G  考点：基环树、动态规划 DP、搜索
 *   https://www.luogu.com.cn/problem/P9869  普及+/提高−  P9869 [NOIP2023] 三值逻辑  考点：基环树、并查集、广度优先搜索 BFS
 *   https://www.luogu.com.cn/problem/P10933  提高  P10933 创世纪  考点：基环树、树形 DP
 *   https://www.luogu.com.cn/problem/P1453  提高  P1453 城市环路  考点：基环树、动态规划 DP、图论
 *   https://www.luogu.com.cn/problem/P3533  提高  P3533 [POI 2012] RAN-Rendezvous  考点：基环树、倍增、并查集
 *   https://www.luogu.com.cn/problem/P4949  提高  P4949 最短距离  考点：基环树、最近公共祖先 LCA、树链剖分
 *   https://www.luogu.com.cn/problem/P5022  提高  P5022 [NOIP 2018 提高组] 旅行  考点：基环树、搜索、贪心
 *   https://codeforces.com/problemset/problem/711/D  CF1900  CF711D Directed Roads  考点：内向基环树森林：环外的边随意，环上不能全同向
 *   https://www.luogu.com.cn/problem/P1399  提高+/省选−  P1399 [NOI2013] 快餐店  考点：基环树、递推、线段树
 *   https://www.luogu.com.cn/problem/P5049  省选/NOI−  P5049 [NOIP 2018 提高组] 旅行 加强版  考点：基环树、贪心、深度优先搜索 DFS
 *
 */

// 基环树森林（无向）：每个连通块恰好 n_i 个点 n_i 条边。允许重边（二元环）和自环（一元环）。点 0..n-1，边 {u, v, w}。
// 构造后：on[v] 表示 v 在环上；cycles[c] 是第 c 个环上的点（按环的顺序），cyc_w[c][i] 是 cycles[c][i] → cycles[c][i+1] 的边权，
// cyc_e[c][i] 是那条边的编号；top[v] 是 v 所在的那棵"挂在环上的树"的根（环上的点），comp[v] 是所在连通块（= 环）的编号。
struct PseudoForest {
    int n;
    vector<array<ll, 3>> edges;
    vector<vector<array<int, 2>>> g;   // {邻点, 边编号}
    vector<char> on;
    vector<int> top, comp, order, pe;  // order：从环向外的 BFS 序；pe[v]：v 连向父亲的边（环上的点为 -1）
    vector<vector<int>> cycles, cyc_e;
    vector<vector<ll>> cyc_w;
    PseudoForest(int n, const vector<array<ll, 3>> &es) : n(n), edges(es), g(n), on(n, 1), top(n, -1), comp(n, -1), pe(n, -1) {
        vector<int> deg(n, 0);
        for (int i = 0; i < (int)es.size(); i++) {
            int u = es[i][0], v = es[i][1];
            g[u].push_back({v, i}), g[v].push_back({u, i}), deg[u]++, deg[v]++;
        }
        // 1. 拓扑排序剥叶子，剩下的就是环
        vector<int> q;
        for (int v = 0; v < n; v++)
            if (deg[v] == 1) q.push_back(v);
        for (size_t h = 0; h < q.size(); h++) {
            int u = q[h];
            on[u] = 0;
            for (auto [v, id] : g[u])
                if (--deg[v] == 1) q.push_back(v);
        }
        // 2. 沿着环走一圈，记录顺序（用边编号避免在二元环上走回头路）
        for (int s = 0; s < n; s++) {
            if (!on[s] || comp[s] != -1) continue;
            int c = cycles.size();
            cycles.push_back({}), cyc_e.push_back({}), cyc_w.push_back({});
            int cur = s, last = -1;
            while (true) {
                comp[cur] = c, cycles[c].push_back(cur);
                int nxt = -1, eid = -1;
                for (auto [v, id] : g[cur])
                    if (on[v] && id != last && (v == s || comp[v] == -1)) {
                        nxt = v, eid = id;
                        if (v != s) break;   // 优先走没访问过的点，最后才回到起点
                    }
                cyc_e[c].push_back(eid), cyc_w[c].push_back(es[eid][2]);
                if (nxt == s) break;
                cur = nxt, last = eid;
            }
        }
        // 3. 从环上的点向外 BFS，确定每棵树的根
        for (int v = 0; v < n; v++)
            if (on[v]) top[v] = v, order.push_back(v);
        for (size_t h = 0; h < order.size(); h++) {
            int u = order[h];
            for (auto [v, id] : g[u])
                if (!on[v] && top[v] == -1) top[v] = top[u], comp[v] = comp[u], pe[v] = id, order.push_back(v);
        }
    }
    int parent(int v) const { return pe[v] == -1 ? -1 : (int)(edges[pe[v]][0] ^ edges[pe[v]][1] ^ v); }

    // 例 1：每个连通块的直径（最长简单路径，边权非负）。断环为链：树内直径 + 环上两点 d_i + d_j + 环上较长的一段
    vector<ll> diameters() const {
        vector<ll> dep(n, 0), best(cycles.size(), 0);   // dep[v]：v 向下（远离环）的最长链
        for (int i = n - 1; i >= 0; i--) {
            int v = order[i], p = parent(v);
            if (p == -1) continue;
            ll len = dep[v] + edges[pe[v]][2];
            best[comp[v]] = max(best[comp[v]], dep[p] + len);   // 树内经过 p 的两条链
            dep[p] = max(dep[p], len);
        }
        for (size_t c = 0; c < cycles.size(); c++) {
            int k = cycles[c].size();
            if (k == 1) continue;
            // 复制一倍：x_i = d_i − pre_i，在长度 < k 的窗口里求 max x_i，答案 = d_j + pre_j + max x_i
            vector<ll> pre(2 * k, 0), d(2 * k);
            for (int i = 0; i < 2 * k; i++) {
                d[i] = dep[cycles[c][i % k]];
                if (i) pre[i] = pre[i - 1] + cyc_w[c][(i - 1) % k];
            }
            deque<int> dq;
            for (int j = 0; j < 2 * k; j++) {
                while (!dq.empty() && dq.front() <= j - k) dq.pop_front();
                if (!dq.empty()) best[c] = max(best[c], d[j] + pre[j] + d[dq.front()] - pre[dq.front()]);
                while (!dq.empty() && d[dq.back()] - pre[dq.back()] <= d[j] - pre[j]) dq.pop_back();
                dq.push_back(j);
            }
        }
        return best;
    }

    // 例 2：最大权独立集（相邻的点不能同时选）。断开环上的一条边 (u, v)，分别强制 u 不选、v 不选，各做一次树形 DP
    ll max_independent_set(const vector<ll> &val) const {
        ll total = 0;
        vector<ll> f0(n), f1(n);
        for (size_t c = 0; c < cycles.size(); c++) {
            int cut = cyc_e[c][0];
            int u = edges[cut][0], v = edges[cut][1];
            ll res = LLONG_MIN;
            for (int r : {u, v}) {
                vector<int> ord = {r};   // 以 r 为根、忽略边 cut 的 BFS 序
                vector<int> fe(n, -2);
                fe[r] = -1;
                for (size_t h = 0; h < ord.size(); h++)
                    for (auto [x, id] : g[ord[h]])
                        if (id != cut && id != fe[ord[h]] && fe[x] == -2) fe[x] = id, ord.push_back(x);
                for (int i = ord.size() - 1; i >= 0; i--) {
                    int x = ord[i];
                    f0[x] = 0, f1[x] = val[x];
                    for (auto [y, id] : g[x])
                        if (id != cut && fe[y] == id) f0[x] += max(f0[y], f1[y]), f1[x] += f0[y];
                }
                res = max(res, f0[r]);   // r 强制不选
            }
            total += res;
        }
        return total;
    }
};

// 内向基环树（函数图）：每个点 v 有唯一后继 nxt[v]。返回 {cyc_len, dist}：
// v 最终进入的环长 cyc_len[v]，v 到环的距离 dist[v]（环上的点为 0）。O(n)
pair<vector<int>, vector<int>> functional_graph(const vector<int> &nxt) {
    int n = nxt.size();
    vector<int> indeg(n, 0), cyc_len(n, 0), dist(n, 0), q;
    for (int v = 0; v < n; v++) indeg[nxt[v]]++;
    for (int v = 0; v < n; v++)
        if (!indeg[v]) q.push_back(v);
    for (size_t h = 0; h < q.size(); h++)   // 剥掉不在环上的点
        if (--indeg[nxt[q[h]]] == 0) q.push_back(nxt[q[h]]);
    for (int v = 0; v < n; v++) {
        if (!indeg[v] || cyc_len[v]) continue;
        int len = 0, u = v;
        do len++, u = nxt[u];
        while (u != v);
        do cyc_len[u] = len, u = nxt[u];
        while (u != v);
    }
    for (int i = q.size() - 1; i >= 0; i--) {   // 逆拓扑序：后继先算好
        int v = q[i];
        dist[v] = dist[nxt[v]] + 1, cyc_len[v] = cyc_len[nxt[v]];
    }
    return {cyc_len, dist};
}
