/**
 * 01_basic/13 01 分数规划
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：01_basic/03 二分查找、二分答案与三分、01_basic/07 贪心常见模型
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 问题模型：每个物品有 a_i、b_i > 0，选一些物品使 Σa / Σb 最大（或最小）
 *   2. 二分答案 λ：Σa / Σb ≥ λ  ⇔  Σ(a_i − λ·b_i) ≥ 0，于是只需判断"按权值 a_i − λ·b_i 能否选出非负和"
 *   3. 判定部分换成别的模型：选 k 个（排序取前 k）、背包（Talent Show）、最优比率环（SPFA 判正/负环）、
 *      最优比率生成树（最小生成树）、树上连通块（树形 DP）
 *   4. Dinkelbach 迭代：用当前最优解的比值作为下一个 λ，通常比二分收敛快得多
 *   5. 精度：实数二分固定迭代 60–100 次；答案要求整数（如 ×1000 取整）时注意 floor 的误差
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/misc/frac-programming/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P10505  P10505 Dropping Test
 *   https://www.luogu.com.cn/problem/P4377  P4377 [USACO18OPEN] Talent Show G
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1404  普及  P1404 平均数  考点：分数规划、数学、贪心
 *   https://www.luogu.com.cn/problem/P1570  普及  P1570 KC 喝咖啡  考点：分数规划、二分
 *   https://www.luogu.com.cn/problem/P1642  提高  P1642 规划  考点：分数规划、动态规划 DP、二分
 *   https://www.luogu.com.cn/problem/P1730  提高  P1730 最小密度路径  考点：分数规划、图论、二分
 *   https://www.luogu.com.cn/problem/P1768  提高  P1768 天路  考点：分数规划、图论、二分
 *   https://www.luogu.com.cn/problem/P2115  提高  P2115 [USACO14MAR] Sabotage G  考点：分数规划、动态规划 DP、二分
 *   https://www.luogu.com.cn/problem/P2868  提高  P2868 [USACO07DEC] Sightseeing Cows G  考点：分数规划、搜索、二分
 *   https://www.luogu.com.cn/problem/P4322  提高  P4322 [JSOI2016] 最佳团体  考点：分数规划、动态规划 DP、二分
 *   https://www.luogu.com.cn/problem/P4951  提高  P4951 [USACO01OPEN] Earthquake  考点：分数规划、二分、生成树
 *   https://www.luogu.com.cn/problem/P3199  提高+/省选−  P3199 [HNOI2009] 最小圈  考点：分数规划、图论、二分
 *   https://www.luogu.com.cn/problem/P3288  省选/NOI−  P3288 [SCOI2014] 方伯伯运椰子  考点：分数规划、网络流、负权环
 *   https://www.luogu.com.cn/problem/P6087  省选/NOI−  P6087 [JSOI2015] 送礼物  考点：分数规划、二分、单调队列
 *
 */

// 01 分数规划：最大化 Σa / Σb（b > 0）。核心是把"比值 ≥ λ"变成"Σ(a − λb) ≥ 0"，然后二分 λ。
// 1. 通用二分：ok(λ) 判断"存在一种选法使 Σ(a − λb) ≥ 0"，返回满足 ok 的最大 λ（ok 关于 λ 单调）
template <class F>
double frac_max(double lo, double hi, F ok, int iters = 100) {
    for (int it = 0; it < iters; it++) {
        double mid = (lo + hi) / 2;
        if (ok(mid)) lo = mid;
        else hi = mid;
    }
    return lo;
}

// 2. 例：恰好选 k 个物品，最大化 Σa / Σb。判定：按 a_i − λb_i 从大到小取前 k 个，看和是否 ≥ 0。O(n log n · 迭代次数)
double frac_choose_k(const vector<double> &a, const vector<double> &b, int k) {
    int n = a.size();
    double lo = 0, hi = 0;
    for (int i = 0; i < n; i++) lo = min(lo, a[i] / b[i]), hi = max(hi, a[i] / b[i]);
    vector<double> c(n);
    return frac_max(lo, hi, [&](double lam) {
        for (int i = 0; i < n; i++) c[i] = a[i] - lam * b[i];
        nth_element(c.begin(), c.begin() + (k - 1), c.end(), greater<double>());
        double s = 0;
        for (int i = 0; i < k; i++) s += c[i];
        return s >= 0;
    });
}

// 3. Dinkelbach：从任意 λ 出发，求出使 Σ(a − λb) 最大的选法 S，令 λ = Σ_S a / Σ_S b，直到不再增大。
//    这里同样以"恰好选 k 个"为例；换模型时只需改"求最优选法"那一段
double frac_choose_k_dinkelbach(const vector<double> &a, const vector<double> &b, int k) {
    int n = a.size();
    vector<int> id(n);
    double lam = 0;
    for (int round = 0; round < 100; round++) {
        iota(id.begin(), id.end(), 0);
        nth_element(id.begin(), id.begin() + (k - 1), id.end(),
                    [&](int x, int y) { return a[x] - lam * b[x] > a[y] - lam * b[y]; });
        double sa = 0, sb = 0;
        for (int i = 0; i < k; i++) sa += a[id[i]], sb += b[id[i]];
        double nl = sa / sb;
        if (fabs(nl - lam) < 1e-12) break;
        lam = nl;
    }
    return lam;
}
