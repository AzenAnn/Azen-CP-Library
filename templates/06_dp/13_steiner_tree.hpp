/**
 * 06_dp/13 最小斯坦纳树
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：06_dp/06 状压 DP、03_graph/03 最短路
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 问题：无向带权图中给出 k 个关键点，选一些边使关键点连通，边权和最小（k 一般 ≤ 10）
 *   2. 状态：dp[S][v] = 以 v 为根、包含关键点集合 S 的树的最小代价
 *   3. 转移一（合并子树）：dp[S][v] = min dp[T][v] + dp[S−T][v]，枚举 S 的子集，总共 O(3^k · n)
 *   4. 转移二（换根 / 延伸）：dp[S][v] = min dp[S][u] + w(u, v)，对每个 S 跑一遍 Dijkstra，O(2^k · m log m)
 *   5. 点权版本（游览计划）：合并时要减去重复算的根的点权；还要输出方案时记录转移来源
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/steiner-tree/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P6192  P6192 【模板】最小斯坦纳树
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3264  省选/NOI−  P3264 [JLOI2015] 管道连接  考点：斯坦纳树 + 子集 DP 合并同频道
 *   https://www.luogu.com.cn/problem/P4294  省选/NOI−  P4294 [WC2008] 游览计划  考点：点权斯坦纳树并输出方案
 *   https://codeforces.com/problemset/problem/152/E  CF2500  CF152E Garden  考点：网格上的斯坦纳树并输出方案
 *   https://www.luogu.com.cn/problem/P7450  NOI/NOI+/CTS  P7450 [THUSC 2017] 巧克力  考点：随机映射颜色到 k 种 + 斯坦纳树
 *
 */

// 最小斯坦纳树（边权）。g 为无向图邻接表 {邻点, 边权}（边权非负），keys 为关键点。
// 返回 dp：dp[S][v] = 连通 S 中的关键点且包含 v 的最小代价；答案为 min_v dp[full][v]（不连通时为 STEINER_INF）。
// O(3^k · n + 2^k · m log m)
const ll STEINER_INF = LLONG_MAX / 4;
vector<vector<ll>> steiner_tree(const vector<vector<pair<int, ll>>> &g, const vector<int> &keys) {
    int n = g.size(), k = keys.size();
    vector<vector<ll>> dp(1 << k, vector<ll>(n, STEINER_INF));
    for (int i = 0; i < k; i++) dp[1 << i][keys[i]] = 0;
    for (int v = 0; v < n; v++) dp[0][v] = 0;
    for (int S = 1; S < (1 << k); S++) {
        auto &d = dp[S];
        // 转移一：在同一个根 v 上合并两棵子树（只枚举包含最低位的一半子集，避免重复）
        for (int T = (S - 1) & S; T > 0; T = (T - 1) & S)
            if (T & (S & -S))
                for (int v = 0; v < n; v++)
                    if (dp[T][v] < STEINER_INF && dp[S ^ T][v] < STEINER_INF) d[v] = min(d[v], dp[T][v] + dp[S ^ T][v]);
        // 转移二：沿边延伸，相当于以 d 为初值的多源 Dijkstra
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        for (int v = 0; v < n; v++)
            if (d[v] < STEINER_INF) pq.push({d[v], v});
        while (!pq.empty()) {
            auto [du, u] = pq.top();
            pq.pop();
            if (du > d[u]) continue;
            for (auto [v, w] : g[u])
                if (du + w < d[v]) d[v] = du + w, pq.push({d[v], v});
        }
    }
    return dp;
}
// 直接求答案
ll steiner_tree_cost(const vector<vector<pair<int, ll>>> &g, const vector<int> &keys) {
    if (keys.empty()) return 0;
    auto dp = steiner_tree(g, keys);
    return *min_element(dp.back().begin(), dp.back().end());
}
