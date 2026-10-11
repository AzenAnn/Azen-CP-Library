/**
 * 06_dp/02 LIS、LCS 与编辑距离
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：06_dp/01 线性 DP 入门与记忆化搜索、01_basic/03 二分查找、二分答案与三分
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. LIS：O(n^2)
 *   2. LIS：O(n log n) 贪心 + 二分
 *   3. LCS
 *   4. 编辑距离
 *   5. 排列的 LCS 转化为 LIS
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/basic/
 *   cp-algorithms  https://cp-algorithms.com/sequences/longest_increasing_subsequence.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/dp.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/B3637  B3637 最长上升子序列
 *   https://www.luogu.com.cn/problem/P1439  P1439 两个排列的最长公共子序列
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1091  普及−  P1091 [NOIP 2004 提高组] 合唱队形  考点：动态规划 DP、线性 DP
 *   https://www.luogu.com.cn/problem/P1108  普及  P1108 [USACO99FALL] 低价购买  考点：动态规划 DP、递推、枚举
 *   https://www.luogu.com.cn/problem/P2364  普及  P2364 [CHCI 2001 Final Exam #2] 胖男孩  考点：动态规划 DP
 *   https://www.luogu.com.cn/problem/P2758  普及  P2758 编辑距离  考点：字符串、动态规划 DP、数学
 *   https://www.luogu.com.cn/problem/P2782  普及  P2782 友好城市  考点：动态规划 DP、线段树、二分
 *   https://www.luogu.com.cn/problem/P3903  普及  P3903 导弹拦截III
 *   https://codeforces.com/problemset/problem/1350/B  CF1400  CF1350B Orac and Models  考点：DP、数学、数论
 *   https://www.luogu.com.cn/problem/P1020  普及+/提高−  P1020 [NOIP 1999 提高组] 导弹拦截  考点：动态规划 DP、贪心、线段树
 *   https://www.luogu.com.cn/problem/P1637  普及+/提高−  P1637 三元上升子序列  考点：线段树、平衡树、树状数组
 *   https://www.luogu.com.cn/problem/P2516  普及+/提高−  P2516 [HAOI2010] 最长公共子序列  考点：字符串、动态规划 DP、容斥原理
 *   https://www.luogu.com.cn/problem/P5939  普及+/提高−  P5939 [POI 1998 R3] 折线  考点：动态规划 DP、数学、二分
 *   https://codeforces.com/problemset/problem/2167/G  CF1600  CF2167G Mukhammadali and the Smooth Array  考点：数据结构、DP
 *   https://codeforces.com/problemset/problem/2242/D  CF1600  CF2242D Two Digit Strings  考点：DP、字符串
 *
 */

// 1. LIS 长度 O(n log n)：d[k] 为"长度为 k+1 的上升子序列"的最小结尾，d 单调递增
//    严格上升用 lower_bound；不下降（允许相等）用 upper_bound
int lis(const vector<ll> &a, bool strict = true) {
    vector<ll> d;
    for (ll x : a) {
        auto it = strict ? lower_bound(d.begin(), d.end(), x) : upper_bound(d.begin(), d.end(), x);
        if (it == d.end()) d.push_back(x);
        else *it = x;
    }
    return d.size();
}

// 2. 还原一个严格上升子序列，返回下标（从小到大）
vector<int> lis_indices(const vector<ll> &a) {
    int n = a.size();
    vector<ll> d;
    vector<int> pos, prev(n, -1);   // pos[k]：d[k] 对应的下标；prev[i]：i 在序列中的前一个下标
    for (int i = 0; i < n; i++) {
        int k = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (k == (int)d.size()) d.push_back(a[i]), pos.push_back(i);
        else d[k] = a[i], pos[k] = i;
        prev[i] = k ? pos[k - 1] : -1;
    }
    vector<int> res;
    for (int i = pos.empty() ? -1 : pos.back(); i != -1; i = prev[i]) res.push_back(i);
    reverse(res.begin(), res.end());
    return res;
}

// 3. LCS：f[i][j] = a 的前 i 个与 b 的前 j 个的最长公共子序列，O(nm)
template <class S>
int lcs(const S &a, const S &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> f(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            f[i][j] = a[i - 1] == b[j - 1] ? f[i - 1][j - 1] + 1 : max(f[i - 1][j], f[i][j - 1]);
    return f[n][m];
}

// 4. 编辑距离：插入、删除、替换一个字符各算一步，把 a 变成 b 的最少步数，O(nm)
template <class S>
int edit_distance(const S &a, const S &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> f(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) f[i][0] = i;
    for (int j = 0; j <= m; j++) f[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            f[i][j] = min({f[i - 1][j] + 1, f[i][j - 1] + 1, f[i - 1][j - 1] + (a[i - 1] != b[j - 1])});
    return f[n][m];
}

// 5. 两个排列的 LCS（洛谷 P1439）：把 b 中每个数换成它在 a 中的位置，
//    公共子序列就变成位置严格上升的子序列，求 LIS 即可，O(n log n)
int lcs_permutation(const vector<int> &a, const vector<int> &b) {
    vector<int> pos(a.size() + 1);
    for (int i = 0; i < (int)a.size(); i++) pos[a[i]] = i;   // a、b 都是 1..n 的排列
    vector<ll> c;
    for (int x : b) c.push_back(pos[x]);
    return lis(c);
}
