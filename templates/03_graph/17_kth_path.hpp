/**
 * 03_graph/17 K 短路
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：03_graph/03 最短路
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 第 k 短路定义：允许重复经过点的第 k 短简单路径（通常允许非简单路径）
 *   2. A* 算法：估价函数 f = 已走距离 + 到终点的最短距离（反图 Dijkstra 预处理）
 *   3. 每个点第 k 次出队时即得到起点的第 k 短路
 *   4. 进阶：可持久化可并堆（左偏树）做法 O(m log m + k log k)
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/kth-path/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2483  P2483 【模板】k 短路 / [SDOI2010] 魔法猪学院
 *   https://www.luogu.com.cn/problem/P4467  P4467 [SCOI2007] k短路
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1379  普及+/提高−  P1379 八数码难题  考点：A* 入门：估价函数 = 不在位的格子数
 *   https://www.luogu.com.cn/problem/P2324  提高  P2324 [SCOI2005] 骑士精神  考点：IDA*：乐观估计剪枝
 *   https://www.luogu.com.cn/problem/P2901  提高  P2901 [USACO08MAR] Cow Jogging G  考点：A*  算法、动态规划 DP、广度优先搜索 BFS
 *   https://codeforces.com/problemset/problem/1196/F  CF2200  CF1196F K-th Path  考点：第 k 短的点对最短路：只保留最小的 k 条边再 Floyd
 *
 */

// K 短路（可持久化左偏树做法，Eppstein 思想）：求有向图中 s 到 t 的前 k 短路径长度（路径可以重复经过点和边）。
// 边权须非负。复杂度 O((n + m) log m + k log k)。
// 思路：反图上从 t 跑 Dijkstra 得到 dist 和最短路树；任何一条 s→t 路径都可以写成"最短路 + 若干条非树边"，
// 每条非树边 (u→v, w) 的额外代价 δ = w + dist[v] − dist[u] ≥ 0。把每个点能用的非树边放进可持久化堆（继承最短路树上父亲的堆），
// 再用一个优先队列按"已选非树边序列"的总代价从小到大扩展。
vector<ll> k_shortest_paths(int n, const vector<array<ll, 3>> &edges, int s, int t, int k) {
    const ll INF = LLONG_MAX / 4;
    vector<vector<pair<int, int>>> rg(n);   // 反图：{起点, 边编号}
    for (int i = 0; i < (int)edges.size(); i++) rg[edges[i][1]].push_back({(int)edges[i][0], i});
    vector<ll> dist(n, INF);
    vector<int> tree_e(n, -1), order;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    dist[t] = 0, pq.push({0, t});
    vector<char> done(n, 0);
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (done[v]) continue;
        done[v] = 1, order.push_back(v);
        for (auto [u, id] : rg[v])
            if (d + edges[id][2] < dist[u]) dist[u] = d + edges[id][2], tree_e[u] = id, pq.push({dist[u], u});
    }
    if (dist[s] >= INF) return {};
    // 可持久化左偏树：节点 {val, 边终点, 左, 右, 距离}
    struct Node { ll val; int to, l, r, d; };
    vector<Node> h = {{0, 0, 0, 0, -1}};   // 0 号为空节点
    function<int(int, int)> merge = [&](int a, int b) -> int {
        if (!a || !b) return a | b;
        if (h[a].val > h[b].val) swap(a, b);
        h.push_back(h[a]);   // 复制 a，保证原来的堆不变
        int c = h.size() - 1;
        int nr = merge(h[c].r, b);
        h[c].r = nr;
        if (h[h[c].l].d < h[h[c].r].d) swap(h[c].l, h[c].r);
        h[c].d = h[h[c].r].d + 1;
        return c;
    };
    // 按 dist 从小到大处理：最短路树上的父亲（树边的终点）先处理完，root[v] = 父亲的堆 + v 自己的非树出边
    vector<int> root(n, 0);
    vector<vector<int>> out(n);
    for (int i = 0; i < (int)edges.size(); i++) out[edges[i][0]].push_back(i);
    for (int v : order) {
        int r = tree_e[v] == -1 ? 0 : root[edges[tree_e[v]][1]];
        for (int id : out[v]) {
            int to = edges[id][1];
            if (id == tree_e[v] || dist[to] >= INF) continue;
            h.push_back({edges[id][2] + dist[to] - dist[v], to, 0, 0, 0});
            r = merge(r, h.size() - 1);
        }
        root[v] = r;
    }
    vector<ll> res = {dist[s]};
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> q;
    if (root[s]) q.push({dist[s] + h[root[s]].val, root[s]});
    while ((int)res.size() < k && !q.empty()) {
        auto [c, x] = q.top();
        q.pop();
        res.push_back(c);
        // 换成同一个堆里的下一个候选（左右儿子），或者在这条非树边之后再接一条
        if (h[x].l) q.push({c - h[x].val + h[h[x].l].val, h[x].l});
        if (h[x].r) q.push({c - h[x].val + h[h[x].r].val, h[x].r});
        int nx = root[h[x].to];
        if (nx) q.push({c + h[nx].val, nx});
    }
    if ((int)res.size() > k) res.resize(k);
    return res;
}
