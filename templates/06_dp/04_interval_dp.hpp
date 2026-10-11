/**
 * 06_dp/04 区间 DP
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：06_dp/01 线性 DP 入门与记忆化搜索
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 按区间长度从小到大枚举
 *   2. 枚举分割点
 *   3. 环形区间：复制一倍
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/interval/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/dp.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1775  P1775 石子合并（弱化版）
 *   https://www.luogu.com.cn/problem/P1880  P1880 [NOI1995] 石子合并
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1140  普及  P1140 [ICPC 2001 Taejon R] 相似基因  考点：动态规划 DP、区间 DP
 *   https://www.luogu.com.cn/problem/P1435  普及  P1435 [IOI 2000] 回文字串  考点：动态规划 DP、区间 DP
 *   https://www.luogu.com.cn/problem/P2426  普及  P2426 删数  考点：动态规划 DP、区间 DP
 *   https://www.luogu.com.cn/problem/P2858  普及  P2858 [USACO06FEB] Treats for the Cows G/S  考点：动态规划 DP、区间 DP
 *   https://www.luogu.com.cn/problem/P1040  普及+/提高−  P1040 [NOIP 2003 提高组] 加分二叉树  考点：动态规划 DP、递归、区间 DP
 *   https://www.luogu.com.cn/problem/P1063  普及+/提高−  P1063 [NOIP 2006 提高组] 能量项链  考点：动态规划 DP、递归、枚举
 *   https://www.luogu.com.cn/problem/P1220  普及+/提高−  P1220 关路灯  考点：动态规划 DP、搜索、区间 DP
 *   https://www.luogu.com.cn/problem/P3205  普及+/提高−  P3205 [HNOI2010] 合唱队  考点：动态规划 DP、区间 DP
 *   https://codeforces.com/problemset/problem/1509/C  CF1800  CF1509C The Sports Festival  考点：DP、贪心
 *   https://codeforces.com/problemset/problem/245/H  CF1800  CF245H Queries for Number of Palindromes  考点：DP、哈希、字符串
 *   https://codeforces.com/problemset/problem/1114/D  CF1900  CF1114D Flood Fill  考点：DP
 *   https://codeforces.com/problemset/problem/607/B  CF1900  CF607B Zuma  考点：DP
 *   https://codeforces.com/problemset/problem/1132/F  CF2000  CF1132F Clear the String  考点：DP
 *   https://codeforces.com/problemset/problem/1025/D  CF2100  CF1025D Recovering BST  考点：暴力、DP、数学
 *   https://codeforces.com/problemset/problem/1336/C  CF2200  CF1336C Kaavi and Magic Spell  考点：DP、字符串
 *
 */

// 区间 DP：f[l][r] 表示区间 [l, r] 的最优值，由更短的区间转移而来。
// 固定写法：先枚举区间长度，再枚举左端点，最后枚举分割点。O(n^3)

// 1. 石子合并（链，洛谷 P1775）：每次合并相邻两堆，代价为两堆之和，求总代价的最小值（或最大值）
//    f[l][r] = min_{l <= k < r} f[l][k] + f[k+1][r] + sum(l..r)
ll stone_merge(const vector<ll> &a, bool want_max = false) {
    int n = a.size();
    if (n == 0) return 0;
    vector<ll> s(n + 1, 0);
    for (int i = 0; i < n; i++) s[i + 1] = s[i] + a[i];
    vector<vector<ll>> f(n, vector<ll>(n, 0));
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            f[l][r] = want_max ? LLONG_MIN : LLONG_MAX;
            for (int k = l; k < r; k++) {
                ll v = f[l][k] + f[k + 1][r] + s[r + 1] - s[l];
                f[l][r] = want_max ? max(f[l][r], v) : min(f[l][r], v);
            }
        }
    return f[0][n - 1];
}

// 2. 环形石子合并（洛谷 P1880）：把数组复制一份接在后面，变成长 2n 的链，
//    答案为所有长度为 n 的区间 [l, l + n - 1] 中的最优值
ll stone_merge_ring(const vector<ll> &a, bool want_max = false) {
    int n = a.size();
    if (n <= 1) return 0;
    vector<ll> b(a);
    b.insert(b.end(), a.begin(), a.end());
    int m = 2 * n;
    vector<ll> s(m + 1, 0);
    for (int i = 0; i < m; i++) s[i + 1] = s[i] + b[i];
    vector<vector<ll>> f(m, vector<ll>(m, 0));
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len - 1 < m; l++) {
            int r = l + len - 1;
            f[l][r] = want_max ? LLONG_MIN : LLONG_MAX;
            for (int k = l; k < r; k++) {
                ll v = f[l][k] + f[k + 1][r] + s[r + 1] - s[l];
                f[l][r] = want_max ? max(f[l][r], v) : min(f[l][r], v);
            }
        }
    ll best = f[0][n - 1];
    for (int l = 0; l < n; l++) best = want_max ? max(best, f[l][l + n - 1]) : min(best, f[l][l + n - 1]);
    return best;
}

// 3. 另一类区间 DP：只看两个端点的转移。例：最长回文子序列
//    f[l][r] = s[l] == s[r] ? f[l+1][r-1] + 2 : max(f[l+1][r], f[l][r-1])
int longest_palindrome_subseq(const string &s) {
    int n = s.size();
    if (n == 0) return 0;
    vector<vector<int>> f(n, vector<int>(n, 0));
    for (int l = n - 1; l >= 0; l--) {
        f[l][l] = 1;
        for (int r = l + 1; r < n; r++)
            f[l][r] = s[l] == s[r] ? (l + 1 <= r - 1 ? f[l + 1][r - 1] : 0) + 2 : max(f[l + 1][r], f[l][r - 1]);
    }
    return f[0][n - 1];
}
