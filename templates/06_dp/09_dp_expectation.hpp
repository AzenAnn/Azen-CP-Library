/**
 * 06_dp/09 概率与期望 DP
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：06_dp/01 线性 DP 入门与记忆化搜索
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 期望的线性性
 *   2. 逆推求期望
 *   3. DAG 上的期望
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/probability/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/dp.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4316  P4316 绿豆蛙的归宿
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1654  提高  P1654 OSU!  考点：动态规划 DP、数学、期望
 *   https://www.luogu.com.cn/problem/P2221  提高  P2221 [HAOI2012] 高速公路  考点：线段树、最大公约数 gcd、期望
 *   https://www.luogu.com.cn/problem/P2473  提高  P2473 [SCOI2008] 奖励关  考点：期望、状压 DP
 *   https://www.luogu.com.cn/problem/P4284  提高  P4284 [SHOI2014] 概率充电器  考点：动态规划 DP、树形 DP、概率论
 *   https://www.luogu.com.cn/problem/P4550  提高  P4550 收集邮票  考点：递推、期望
 *   https://www.luogu.com.cn/problem/P15649  提高+/省选−  P15649 [省选联考 2026] 找寻者  考点：多项式、背包 DP、树形 DP
 *   https://www.luogu.com.cn/problem/P4206  提高+/省选−  P4206 [NOI2005] 聪聪与可可  考点：动态规划 DP、搜索、图论
 *   https://www.luogu.com.cn/problem/P6835  提高+/省选−  P6835 [Cnoi2020] 线形生物  考点：动态规划 DP、期望
 *   https://codeforces.com/problemset/problem/1265/E  CF2100  CF1265E Beautiful Mirrors  考点：数据结构、DP、数学
 *   https://codeforces.com/problemset/problem/280/C  CF2200  CF280C Game on Tree  考点：实现、数学、概率期望
 *   https://www.luogu.com.cn/problem/P3211  省选/NOI−  P3211 [HNOI2011] XOR和路径  考点：期望、高斯消元、位运算
 *   https://www.luogu.com.cn/problem/P3239  省选/NOI−  P3239 [HNOI2015] 亚瑟王  考点：动态规划 DP、期望
 *   https://www.luogu.com.cn/problem/P3317  省选/NOI−  P3317 [SDOI2014] 重建  考点：矩阵树定理、生成树、期望
 *   https://www.luogu.com.cn/problem/P3750  省选/NOI−  P3750 [六省联考 2017] 分手是祝愿  考点：动态规划 DP、递推、枚举
 *   https://www.luogu.com.cn/problem/P3978  省选/NOI−  P3978 [TJOI2015] 概率论  考点：递推、Catalan 数、生成函数
 *
 */

// 概率与期望 DP。
// 核心工具：期望的线性性 E[X + Y] = E[X] + E[Y]（不要求独立）。
// 常用"逆推"：设 E[u] 为从状态 u 走到终点还需要的期望代价，终点 E = 0，
// E[u] = Σ P(u → v) · (cost(u → v) + E[v])。状态有环时需要解方程（或高斯消元）。
// 题目要求输出分数取模时，把除法换成乘逆元即可。

// 1. DAG 上的期望（洛谷 P4316 绿豆蛙的归宿）：从 s 出发，每一步等概率地选一条出边走，到 t 停止，
//    求期望路径长度。按拓扑序倒序计算 E[u] = Σ (w + E[v]) / outdeg(u)。edges[i] = {u, v, w}
double dag_expected_length(int n, const vector<array<ll, 3>> &edges, int s, int t) {
    vector<vector<pair<int, ll>>> g(n);
    vector<int> indeg(n, 0), order;
    for (auto &[u, v, w] : edges) g[u].push_back({(int)v, w}), indeg[v]++;
    for (int u = 0; u < n; u++)
        if (!indeg[u]) order.push_back(u);
    for (size_t i = 0; i < order.size(); i++)
        for (auto [v, w] : g[order[i]])
            if (--indeg[v] == 0) order.push_back(v);
    vector<double> E(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (u == t || g[u].empty()) continue;
        double sum = 0;
        for (auto [v, w] : g[u]) sum += w + E[v];
        E[u] = sum / g[u].size();
    }
    return E[s];
}

// 2. 期望次数：每次成功的概率为 p，直到成功为止的期望次数为 1 / p（几何分布）。
//    例：收集 n 种卡片（每次等概率得到一种）的期望次数。已有 k 种时，得到新卡片的概率为 (n - k) / n，
//    期望要 n / (n - k) 次；总和 = n · (1 + 1/2 + ... + 1/n)
double coupon_collector(int n) {
    double s = 0;
    for (int k = 0; k < n; k++) s += (double)n / (n - k);
    return s;
}

// 3. 带"原地不动"的期望：E[i] = 1 + p·E[i] + (1 - p)·E[i + 1]，移项得 E[i] = (1 + (1 - p)·E[i + 1]) / (1 - p)。
//    例：每一步以概率 p 停在原地、1 - p 前进一格，从 0 走到 n 的期望步数
double expected_steps_with_stay(int n, double p) {
    double E = 0;   // E[n] = 0
    for (int i = n - 1; i >= 0; i--) E = (1 + (1 - p) * E) / (1 - p);
    return E;
}
