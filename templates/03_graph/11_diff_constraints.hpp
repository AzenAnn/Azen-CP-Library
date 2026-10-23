/**
 * 03_graph/11 差分约束
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：03_graph/03 最短路
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 把不等式 x_j - x_i <= w 建成边
 *   2. SPFA 判负环 / 求可行解
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/diff-constraints/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5960  P5960 【模板】差分约束
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10935  提高  P10935 银河  考点：动态规划 DP、拓扑排序、最短路
 *   https://www.luogu.com.cn/problem/P10941  提高  P10941 [ICPC 2000 Tehran R] Cashier Employment  考点：二分、差分约束
 *   https://www.luogu.com.cn/problem/P3275  提高  P3275 [SCOI2011] 糖果  考点：动态规划 DP、拓扑排序、Tarjan
 *   https://www.luogu.com.cn/problem/P4578  提高  P4578 [FJOI2018] 所罗门王的宝藏  考点：图论、枚举、差分约束
 *   https://www.luogu.com.cn/problem/P5590  提高  P5590 赛车游戏  考点：差分约束
 *   https://www.luogu.com.cn/problem/P5751  提高  P5751 [NOI1999] 01 串  考点：差分约束、前缀和
 *   https://www.luogu.com.cn/problem/P12976  提高+/省选−  P12976 受力分析 Force  考点：差分约束
 *   https://www.luogu.com.cn/problem/P3530  提高+/省选−  P3530 [POI 2012] FES-Festival  考点：负权环、Tarjan、差分约束
 *   https://www.luogu.com.cn/problem/P4926  提高+/省选−  P4926 [1007] 倍杀测量者  考点：二分、最短路、差分约束
 *   https://www.luogu.com.cn/problem/P7624  提高+/省选−  P7624 [AHOI2021初中组] 地铁  考点：二分、图论建模、负权环
 *   https://www.luogu.com.cn/problem/P11427  省选/NOI−  P11427 [清华集训 2024] 绝顶之战  考点：搜索、剪枝、差分约束
 *   https://www.luogu.com.cn/problem/P2474  省选/NOI−  P2474 [SCOI2008] 天平  考点：图论建模、差分约束
 *   https://www.luogu.com.cn/problem/P3084  省选/NOI−  P3084 [USACO13OPEN] Photo G  考点：动态规划 DP、线段树、单调队列
 *   https://www.luogu.com.cn/problem/P5532  省选/NOI−  P5532 [CCO 2019] Sirtet  考点：图论建模、最短路、差分约束
 *   https://www.luogu.com.cn/problem/P7515  省选/NOI−  P7515 [省选联考 2021 A 卷] 矩阵游戏  考点：图论、差分约束、构造
 *
 */

// 差分约束：n 个变量 x[0..n-1]，若干约束 x[v] - x[u] <= w。
// 把约束看成边 u -> v（权 w），则最短路满足 dist[v] <= dist[u] + w，正好就是一组解。
// 加一个超级源点向所有点连权 0 的边（等价于所有 dist 初始为 0、所有点先入队），跑 SPFA。
// 有负环 ⇔ 无解。求得的是满足 x[i] <= 0 的"最大"解（每个 x[i] 都尽可能大）。
// 其他形式的约束：x[v] - x[u] >= w ⇔ x[u] - x[v] <= -w；x[v] - x[u] = w ⇔ 同时加 <= w 和 >= w
// cons[i] = {u, v, w} 表示 x[v] - x[u] <= w；无解返回空 vector
vector<ll> diff_constraints(int n, const vector<array<ll, 3>> &cons) {
    vector<vector<pair<int, ll>>> g(n);
    for (auto &[u, v, w] : cons) g[u].push_back({(int)v, w});
    vector<ll> dist(n, 0);
    vector<int> cnt(n, 0);   // 最短路上的边数（不算源点的边），达到 n 说明有负环
    vector<bool> inq(n, true);
    queue<int> q;
    for (int i = 0; i < n; i++) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop(), inq[u] = false;
        for (auto [v, w] : g[u]) {
            if (dist[u] + w >= dist[v]) continue;
            dist[v] = dist[u] + w, cnt[v] = cnt[u] + 1;
            if (cnt[v] >= n) return {};
            if (!inq[v]) inq[v] = true, q.push(v);
        }
    }
    return dist;
}
