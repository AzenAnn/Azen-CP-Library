/**
 * 06_dp/15 DP 套 DP
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：06_dp/06 状压 DP、06_dp/01 线性 DP 入门与记忆化搜索
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 内层 DP：计算某个具体方案的权值（如 LIS 长度、匹配数）
 *   2. 外层 DP：把内层 DP 的状态作为外层状态的一维
 *   3. 经典模型：统计 LIS 长度 ≤ k 的排列数、LCS 自动机上 DP
 *   4. 自动机视角：内层 DP 状态转移 → 自动机，外层在自动机上计数
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/dp-of-dp/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P10614  P10614 BZOJ3864 Hero meet devil
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P8386  提高+/省选−  P8386 [PA 2021] Od deski do deski  考点：DP 套 DP、动态规划 DP
 *   https://www.luogu.com.cn/problem/P15650  省选/NOI−  P15650 [省选联考 2026] 摩卡串  考点：DP 套 DP、字符串、动态规划 DP
 *   https://www.luogu.com.cn/problem/P4590  省选/NOI−  P4590 [TJOI2018] 游园会  考点：DP 套 DP、字符串、递推
 *   https://www.luogu.com.cn/problem/P8352  省选/NOI−  P8352 [SDOI/SXOI2022] 小 N 的独立集  考点：DP 套 DP
 *   https://www.luogu.com.cn/problem/P5279  NOI/NOI+/CTS  P5279 [ZJOI2019] 麻将  考点：DP 套 DP
 *   https://www.luogu.com.cn/problem/P8497  NOI/NOI+/CTS  P8497 [NOI2022] 移除石子  考点：DP 套 DP
 *
 */

// DP 套 DP：外层 DP 的状态是"内层 DP 的整个状态"。
// 例题：给定串 s（长度 m ≤ 15 左右）和字符集，对每个 k 求长度为 n、与 s 的 LCS 恰好为 k 的串的个数（Hero meet devil）。
// 内层：LCS 的一行 dp[0..m]（dp[j] = 当前串与 s 前 j 个字符的 LCS），相邻两项差为 0 或 1，用 m 位二进制表示差分；
// 预处理每个差分状态加一个字符后变成哪个状态（内层 DP 的转移 = 自动机），外层 DP 在这个自动机上数路径。
// 复杂度 O(2^m · m · |Σ| + n · 2^m · |Σ|)。
vector<ll> count_by_lcs(const string &s, int n, const string &alphabet, ll mod) {
    int m = s.size(), S = 1 << m, A = alphabet.size();
    vector<vector<int>> trans(S, vector<int>(A));
    for (int mask = 0; mask < S; mask++) {
        vector<int> dp(m + 1, 0);   // 由差分还原这一行
        for (int j = 0; j < m; j++) dp[j + 1] = dp[j] + (mask >> j & 1);
        for (int c = 0; c < A; c++) {
            vector<int> nd(m + 1, 0);
            for (int j = 1; j <= m; j++)
                nd[j] = s[j - 1] == alphabet[c] ? dp[j - 1] + 1 : max(nd[j - 1], dp[j]);
            int nm = 0;
            for (int j = 0; j < m; j++)
                if (nd[j + 1] - nd[j]) nm |= 1 << j;
            trans[mask][c] = nm;
        }
    }
    vector<ll> f(S, 0), g(S);
    f[0] = 1 % mod;
    for (int step = 0; step < n; step++) {
        fill(g.begin(), g.end(), 0);
        for (int mask = 0; mask < S; mask++)
            if (f[mask])
                for (int c = 0; c < A; c++) g[trans[mask][c]] = (g[trans[mask][c]] + f[mask]) % mod;
        swap(f, g);
    }
    vector<ll> res(m + 1, 0);
    for (int mask = 0; mask < S; mask++) res[__builtin_popcount(mask)] = (res[__builtin_popcount(mask)] + f[mask]) % mod;
    return res;
}
