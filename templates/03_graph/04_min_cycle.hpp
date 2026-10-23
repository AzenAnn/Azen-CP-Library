/**
 * 03_graph/04 最小环与次短路
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：03_graph/03 最短路
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 无向图最小环（Floyd）：枚举环上编号最大的点 k，在 dist 只经过 < k 的点时，用 dist[i][j] + w(j,k) + w(k,i) 更新
 *   2. 输出最小环的方案：记录 Floyd 的中转点 mid[i][j]，递归还原 i→j 的路径
 *   3. 有向图最小环：Floyd 后取 min dist[i][i]；或者对每个点跑一次 Dijkstra
 *   4. 严格次短路：Dijkstra 时每个点保留最短、次短两个距离，次短也要入堆继续扩展
 *   5. 变形：删一条边后的最短路、"恰好经过一次某种边"的分层图、第 k 短路（见 03_graph/17）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/min-cycle/
 *   OI-wiki        https://oi-wiki.org/graph/shortest-path/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P6175  P6175 无向图的最小环问题
 *   https://www.luogu.com.cn/problem/P2865  P2865 [USACO06NOV] Roadblocks G
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2176  普及+/提高−  P2176 [USACO11DEC] RoadBlock S / [USACO14FEB] Roadblock G/S  考点：最短路、搜索、图论
 *   https://www.luogu.com.cn/problem/P10927  提高  P10927 [CEOI 1999] Sightseeing trip  考点：最小环、深度优先搜索 DFS、最短路
 *   https://www.luogu.com.cn/problem/P1491  提高  P1491 集合位置  考点：最短路、搜索、图论
 *   https://www.luogu.com.cn/problem/P2738  提高  P2738 [USACO4.1] 篱笆回路 Fence Loops  考点：搜索、图论、优先队列
 *   https://www.luogu.com.cn/problem/P2829  提高  P2829 大逃离  考点：最短路、图论
 *   https://www.luogu.com.cn/problem/P10044  省选/NOI−  P10044 [CCPC 2023 北京市赛] 最小环  考点：最小环、图论、最短路
 *
 */

// 1. 无向图最小环（Floyd，O(n^3)）。w 为邻接矩阵，没有边时为 MIN_CYCLE_INF，w[i][i] 忽略；重边请提前取 min。
//    返回最小环长度（至少 3 个点；不存在返回 MIN_CYCLE_INF），cyc 非空时写入环上的点
const ll MIN_CYCLE_INF = LLONG_MAX / 4;
ll floyd_min_cycle(vector<vector<ll>> w, vector<int> *cyc = nullptr) {
    int n = w.size();
    auto d = w;
    vector<vector<int>> mid(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) d[i][i] = 0;
    ll best = MIN_CYCLE_INF;
    function<void(int, int, vector<int> &)> path = [&](int i, int j, vector<int> &out) {   // i→j 路径中间的点
        int k = mid[i][j];
        if (k == -1) return;
        path(i, k, out), out.push_back(k), path(k, j, out);
    };
    for (int k = 0; k < n; k++) {
        // 此时 d[i][j] 只经过编号 < k 的点，环 = i → j（经过 < k 的点）→ k → i
        for (int i = 0; i < k; i++)
            for (int j = i + 1; j < k; j++)
                if (d[i][j] < MIN_CYCLE_INF && w[j][k] < MIN_CYCLE_INF && w[k][i] < MIN_CYCLE_INF &&
                    d[i][j] + w[j][k] + w[k][i] < best) {
                    best = d[i][j] + w[j][k] + w[k][i];
                    if (cyc) {
                        cyc->clear();
                        cyc->push_back(i), path(i, j, *cyc), cyc->push_back(j), cyc->push_back(k);
                    }
                }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][k] < MIN_CYCLE_INF && d[k][j] < MIN_CYCLE_INF && d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j], mid[i][j] = k;
    }
    return best;
}

// 2. 有向图最小环（Floyd）：d[i][i] 初始为 INF，跑完后 min d[i][i] 就是最小环（自环也算）
ll floyd_min_cycle_directed(vector<vector<ll>> d) {
    int n = d.size();
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (d[i][k] < MIN_CYCLE_INF)
                for (int j = 0; j < n; j++)
                    if (d[k][j] < MIN_CYCLE_INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    ll best = MIN_CYCLE_INF;
    for (int i = 0; i < n; i++) best = min(best, d[i][i]);
    return best;
}

// 3. 严格次短路（允许重复经过点和边）：返回 {最短, 严格次短}，不存在时为 MIN_CYCLE_INF。边权须为正。O(m log m)
pair<vector<ll>, vector<ll>> second_shortest(const vector<vector<pair<int, ll>>> &g, int s) {
    int n = g.size();
    vector<ll> d1(n, MIN_CYCLE_INF), d2(n, MIN_CYCLE_INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    d1[s] = 0, pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > d2[u]) continue;   // 已经是第三短以上，没用
        for (auto [v, w] : g[u]) {
            ll nd = d + w;
            if (nd < d1[v]) swap(nd, d1[v]), pq.push({d1[v], v});
            if (d1[v] < nd && nd < d2[v]) d2[v] = nd, pq.push({d2[v], v});
        }
    }
    return {d1, d2};
}
