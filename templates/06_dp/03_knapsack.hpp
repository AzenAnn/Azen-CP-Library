/**
 * 06_dp/03 背包 DP
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：06_dp/01 线性 DP 入门与记忆化搜索
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 0-1 背包（倒序枚举容量）
 *   2. 完全背包
 *   3. 多重背包（二进制拆分）
 *   4. 分组背包
 *   5. 求方案数与具体方案
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/knapsack/
 *   cp-algorithms  https://cp-algorithms.com/dynamic_programming/knapsack.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/dp.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1048  P1048 [NOIP 2005 普及组] 采药
 *   https://www.luogu.com.cn/problem/P1616  P1616 疯狂的采药
 *   https://www.luogu.com.cn/problem/P1776  P1776 宝物筛选
 *   https://www.luogu.com.cn/problem/P1757  P1757 通天之分组背包
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1833  普及  P1833 樱花  考点：动态规划 DP、背包 DP
 *   https://www.luogu.com.cn/problem/P2918  普及  P2918 [USACO08NOV] Buying Hay S  考点：动态规划 DP、背包 DP
 *   https://www.luogu.com.cn/problem/P6205  普及  P6205 [USACO06JAN] Dollar Dayz S  考点：动态规划 DP、高精度
 *   https://www.luogu.com.cn/problem/P6771  普及  P6771 [USACO05MAR] Space Elevator 太空电梯  考点：动态规划 DP、贪心
 *   https://www.luogu.com.cn/problem/P1064  普及+/提高−  P1064 [NOIP 2006 提高组] 金明的预算方案  考点：动态规划 DP、背包 DP、树形 DP
 *   https://www.luogu.com.cn/problem/P5322  普及+/提高−  P5322 [BJOI2019] 排兵布阵  考点：动态规划 DP、背包 DP
 *   https://codeforces.com/problemset/problem/1673/C  CF1500  CF1673C Palindrome Basis  考点：暴力、DP、数学
 *   https://codeforces.com/problemset/problem/212/E  CF1500  CF212E IT Restaurants  考点：搜索、DP、树
 *   https://codeforces.com/problemset/problem/1516/C  CF1700  CF1516C Baby Ehab Partitions Again  考点：位运算、构造、DP
 *   https://www.luogu.com.cn/problem/P1782  提高  P1782 旅行商的背包  考点：动态规划 DP、单调队列、背包 DP
 *   https://www.luogu.com.cn/problem/P4377  提高  P4377 [USACO18OPEN] Talent Show G  考点：贪心、二分、背包 DP
 *   https://codeforces.com/problemset/problem/577/B  CF1900  CF577B Modulo Sum  考点：组合数学、数据结构、DP
 *   https://codeforces.com/problemset/problem/2075/D  CF2000  CF2075D Equalization  考点：位运算、暴力、DP
 *   https://codeforces.com/problemset/problem/478/D  CF2000  CF478D Red-Green Towers  考点：DP
 *   https://codeforces.com/problemset/problem/837/D  CF2100  CF837D Round Subset  考点：DP、数学
 *
 */

// dp[j] 表示容量不超过 j 时的最大价值；w 为重量，v 为价值，W 为背包容量

// 1. 0-1 背包：每件物品最多选一次。容量从大到小枚举，保证每件物品只用一次
ll knapsack01(const vector<int> &w, const vector<ll> &v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int j = W; j >= w[i]; j--) dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    return dp[W];
}

// 2. 完全背包：每件物品可以选无限次。容量从小到大枚举
ll knapsack_complete(const vector<int> &w, const vector<ll> &v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int j = w[i]; j <= W; j++) dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    return dp[W];
}

// 3. 多重背包：第 i 件物品最多选 c[i] 次。二进制拆分成 1, 2, 4, ..., 剩余 份，
//    任意 0..c[i] 都能由这些份组合出来，于是转化为 0-1 背包，O(W · Σlog c[i])
ll knapsack_bounded(const vector<int> &w, const vector<ll> &v, const vector<int> &c, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++) {
        for (int k = 1, left = c[i]; left > 0; k <<= 1) {
            int take = min(k, left);
            left -= take;
            ll tw = (ll)take * w[i], tv = take * v[i];
            for (ll j = W; j >= tw; j--) dp[j] = max(dp[j], dp[j - tw] + tv);
        }
    }
    return dp[W];
}

// 4. 分组背包：每组最多选一件。顺序是：枚举组 → 容量从大到小 → 枚举组内物品
//    groups[g] = {(重量, 价值), ...}
ll knapsack_group(const vector<vector<pair<int, ll>>> &groups, int W) {
    vector<ll> dp(W + 1, 0);
    for (auto &grp : groups)
        for (int j = W; j >= 0; j--)
            for (auto [wi, vi] : grp)
                if (j >= wi) dp[j] = max(dp[j], dp[j - wi] + vi);
    return dp[W];
}

// 5. 计数：用若干物品（每件最多一次）恰好凑出重量 j 的方案数，返回 ways[0..W]
vector<ll> count_ways01(const vector<int> &w, int W, ll mod) {
    vector<ll> ways(W + 1, 0);
    ways[0] = 1 % mod;
    for (int wi : w)
        for (int j = W; j >= wi; j--) ways[j] = (ways[j] + ways[j - wi]) % mod;
    return ways;
}

// 6. "恰好装满"的最大价值：把 dp 初始化为 -INF、dp[0] = 0，其余转移不变
