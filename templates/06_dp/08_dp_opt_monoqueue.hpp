/**
 * 06_dp/08 单调队列 / 单调栈优化 DP
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/02 单调队列
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 转移来自滑动窗口时用单调队列
 *   2. 多重背包的单调队列优化
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/opt/monotonous-queue-stack/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/dp.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1725  P1725 琪露诺
 *   https://www.luogu.com.cn/problem/P2627  P2627 [USACO11OPEN] Mowing the Lawn G
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1070  提高  P1070 [NOIP 2009 普及组] 道路游戏  考点：动态规划 DP、单调队列、动态规划优化
 *   https://www.luogu.com.cn/problem/P1099  提高  P1099 [NOIP 2007 提高组] 树网的核  考点：模拟、动态规划 DP、树形数据结构
 *   https://www.luogu.com.cn/problem/P1295  提高  P1295 [TJOI2011] 书架  考点：动态规划 DP、线段树、二分
 *   https://www.luogu.com.cn/problem/P2569  提高  P2569 [SCOI2010] 股票交易  考点：动态规划 DP、线段树、单调队列
 *   https://www.luogu.com.cn/problem/P3957  提高  P3957 [NOIP 2017 普及组] 跳房子  考点：动态规划 DP、二分、单调队列
 *   https://codeforces.com/problemset/problem/487/B  CF2000  CF487B Strip  考点：二分、数据结构、DP
 *   https://codeforces.com/problemset/problem/940/E  CF2000  CF940E Cashback  考点：数据结构、DP、贪心
 *   https://www.luogu.com.cn/problem/P2254  提高+/省选−  P2254 [NOI2005] 瑰丽华尔兹  考点：动态规划 DP、单调队列、记忆化搜索
 *   https://codeforces.com/problemset/problem/372/C  CF2100  CF372C Watching Fireworks is Fun  考点：数据结构、DP、数学
 *   https://codeforces.com/problemset/problem/1208/E  CF2200  CF1208E Let Them Slide  考点：数据结构、实现
 *   https://www.luogu.com.cn/problem/P2300  省选/NOI−  P2300 合并神犇  考点：动态规划 DP、贪心、线段树
 *   https://www.luogu.com.cn/problem/P3580  省选/NOI−  P3580 [POI 2014] ZAL-Freight  考点：动态规划 DP、二分、树状数组
 *   https://www.luogu.com.cn/problem/P4852  省选/NOI−  P4852 yyf hates choukapai  考点：动态规划 DP、单调队列、凸完全单调性（wqs 二分）
 *   https://www.luogu.com.cn/problem/P4954  省选/NOI−  P4954 [USACO09OPEN] Tower of Hay G  考点：动态规划 DP、贪心、单调队列
 *   https://www.luogu.com.cn/problem/P5665  省选/NOI−  P5665 [CSP-S 2019] 划分  考点：动态规划 DP、贪心、单调队列
 *
 */

// 单调队列优化 DP：当转移形如 f[i] = max_{j ∈ [i - R, i - L]} g(j) + h(i) 时，
// 可选的 j 构成一个随 i 右移的滑动窗口，用单调队列维护窗口内 g(j) 的最大值，O(n)。

// 1. 例（洛谷 P1725 琪露诺）：从位置 0 出发，每次从 i 跳到 [i + L, i + R] 中的某个位置，
//    获得该位置的分数 a[i]，求到达每个位置时的最大总分（到不了为 NEG）。
//    f[i] = a[i] + max_{j ∈ [i - R, i - L]} f[j]。P1725 的答案为所有满足 i + R > n 的 f[i] 的最大值
vector<ll> window_dp(const vector<ll> &a, int L, int R) {
    int n = a.size();
    const ll NEG = LLONG_MIN / 4;
    vector<ll> f(n, NEG);
    f[0] = a[0];
    deque<int> q;   // 存下标，f 值从队头到队尾递减
    for (int i = 1; i < n; i++) {
        int j = i - L;   // 新进入窗口的决策点
        if (j >= 0) {
            while (!q.empty() && f[q.back()] <= f[j]) q.pop_back();
            q.push_back(j);
        }
        while (!q.empty() && q.front() < i - R) q.pop_front();   // 离开窗口的决策点
        if (!q.empty() && f[q.front()] > NEG) f[i] = f[q.front()] + a[i];
    }
    return f;
}

// 2. 多重背包的单调队列优化：O(n · W)（二进制拆分为 O(W · Σ log c)）
//    对第 i 件物品，按容量 j 除以 w 的余数 r 分组：j = r + k·w。
//    dp'[r + k·w] = max_{k - c <= t <= k} (dp[r + t·w] - t·v) + k·v，括号内对 t 用单调队列
ll knapsack_bounded_mq(const vector<int> &w, const vector<ll> &v, const vector<int> &c, int W) {
    vector<ll> dp(W + 1, 0), ndp(W + 1);
    for (size_t i = 0; i < w.size(); i++) {
        for (int r = 0; r < w[i] && r <= W; r++) {
            deque<pair<int, ll>> q;   // (t, dp[r + t·w] - t·v)，值从队头到队尾递减
            for (int k = 0; r + k * w[i] <= W; k++) {
                ll val = dp[r + k * w[i]] - k * v[i];
                while (!q.empty() && q.back().second <= val) q.pop_back();
                q.push_back({k, val});
                while (q.front().first < k - c[i]) q.pop_front();
                ndp[r + k * w[i]] = q.front().second + k * v[i];
            }
        }
        dp = ndp;
    }
    return dp[W];
}
