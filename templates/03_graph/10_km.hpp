/**
 * 03_graph/10 二分图最大权匹配（KM / 匈牙利算法）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：03_graph/09 二分图
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 顶标（势能）：lx[i] + ly[j] ≥ w[i][j]，相等子图中的完美匹配就是最大权完美匹配
 *   2. 每次找不到增广路时，用 slack 求最小的 d 调整顶标，让新的边进入相等子图
 *   3. BFS 写法 O(n^3)；DFS 写法最坏 O(n^4)，会被 P6577 卡掉
 *   4. 非完美匹配 / 左右点数不同：补 0 权边或虚点；只求"最大权匹配"（不要求完美）时，把不存在的边设为 0
 *   5. 与费用流的关系：KM 就是二分图上的最小费用最大流，但常数小得多；n ≤ 500 时首选 KM
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/graph-matching/bigraph-weight-match/
 *   cp-algorithms  https://cp-algorithms.com/graph/hungarian-algorithm.html
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P6577  P6577 【模板】二分图最大权完美匹配
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2457  提高  P2457 [SDOI2006] 仓库管理员的烦恼  考点：二分图、费用流
 *   https://www.luogu.com.cn/problem/P4014  提高+/省选−  P4014 分配问题  考点：KM 求最小和最大权完美匹配
 *   https://www.luogu.com.cn/problem/P3705  省选/NOI−  P3705 [SDOI2017] 新生舞会  考点：分数规划 + KM / 费用流
 *   https://www.luogu.com.cn/problem/P3967  省选/NOI−  P3967 [TJOI2014] 匹配  考点：KM + 判断哪些边必须在最优匹配里
 *   https://www.luogu.com.cn/problem/UVA1411  省选/NOI−  UVA1411 Ants  考点：最小权完美匹配的匹配线段互不相交
 *   https://codeforces.com/problemset/problem/1107/F  CF2600  CF1107F Vasya and Endless Credits  考点：按还款月份建二分图，KM 或费用流
 *
 */

// 匈牙利算法（带势能的 O(n^2 m) BFS 写法）：左边 n 个点、右边 m 个点（n ≤ m），每个左点都要匹配，
// 求权值和最大的匹配。w[i][j] 可以为负；不允许的边设成很小的数（如 -1e15），结果小于 -1e15 量级就说明无解。
// 返回最大权值和，match_left[i] 为左点 i 匹配的右点。
ll km_max_weight(const vector<vector<ll>> &w, vector<int> *match_left = nullptr) {
    int n = w.size(), m = n ? w[0].size() : 0;
    const ll INF = LLONG_MAX / 4;
    // 转成最小费用：cost = -w。下面的数组都从 1 开始编号，p[j] 为右点 j 匹配的左点，0 号是虚点
    vector<ll> u(n + 1, 0), v(m + 1, 0);
    vector<int> p(m + 1, 0), way(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<ll> minv(m + 1, INF);
        vector<char> used(m + 1, 0);
        do {
            used[j0] = 1;
            int i0 = p[j0], j1 = 0;
            ll delta = INF;
            for (int j = 1; j <= m; j++)
                if (!used[j]) {
                    ll cur = -w[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j]) minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta) delta = minv[j], j1 = j;
                }
            for (int j = 0; j <= m; j++)
                if (used[j]) u[p[j]] += delta, v[j] -= delta;
                else minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {   // 沿 way 回溯，翻转增广路
            int j1 = way[j0];
            p[j0] = p[j1], j0 = j1;
        } while (j0);
    }
    ll res = 0;
    if (match_left) match_left->assign(n, -1);
    for (int j = 1; j <= m; j++)
        if (p[j]) {
            res += w[p[j] - 1][j - 1];
            if (match_left) (*match_left)[p[j] - 1] = j - 1;
        }
    return res;
}
