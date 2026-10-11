/**
 * 06_dp/06 状压 DP
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：01_basic/06 位运算
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 用二进制表示集合
 *   2. 旅行商问题 TSP
 *   3. 棋盘类状压
 *   4. 高维前缀和（SOS DP）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/state/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/dp.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1879  P1879 [USACO06NOV] Corn Fields G
 *   https://www.luogu.com.cn/problem/P1171  P1171 售货员的难题
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1850  提高  P1850 [NOIP 2016 提高组] 换教室  考点：动态规划 DP、期望、Floyd 算法
 *   https://www.luogu.com.cn/problem/P1896  提高  P1896 [SCOI2005] 互不侵犯  考点：动态规划 DP、深度优先搜索 DFS、轮廓线 DP
 *   https://www.luogu.com.cn/problem/P2704  提高  P2704 [NOI2001] 炮兵阵地  考点：搜索、记忆化搜索、进制
 *   https://codeforces.com/problemset/problem/580/D  CF1800  CF580D Kefa and Dishes  考点：位运算、DP
 *   https://codeforces.com/problemset/problem/16/E  CF1900  CF16E Fish  考点：位运算、DP、概率期望
 *   https://codeforces.com/problemset/problem/1753/C  CF2000  CF1753C Wish I Knew How to Sort  考点：DP、数学、概率期望
 *   https://codeforces.com/problemset/problem/453/B  CF2000  CF453B Little Pony and Harmony Chest  考点：位运算、暴力、DP
 *   https://www.luogu.com.cn/problem/P4484  提高+/省选−  P4484 [BJWC2018] 最长上升子序列  考点：差分、杨表、状压 DP
 *   https://codeforces.com/problemset/problem/165/E  CF2200  CF165E Compatible Numbers  考点：位运算、暴力、搜索
 *   https://codeforces.com/problemset/problem/1316/E  CF2300  CF1316E Team Building  考点：位运算、DP、贪心
 *   https://codeforces.com/problemset/problem/449/D  CF2400  CF449D Jzzhu and Numbers  考点：位运算、组合数学、DP
 *   https://www.luogu.com.cn/problem/P10614  省选/NOI−  P10614 BZOJ3864 Hero meet devil  考点：字符串、有限状态自动机、DP 套 DP
 *   https://www.luogu.com.cn/problem/P3959  省选/NOI−  P3959 [NOIP 2017 提高组] 宝藏  考点：搜索、贪心、枚举
 *   https://www.luogu.com.cn/problem/P4590  省选/NOI−  P4590 [TJOI2018] 游园会  考点：字符串、递推、枚举
 *   https://www.luogu.com.cn/problem/P5369  省选/NOI−  P5369 [PKUSC2018] 最大前缀和  考点：动态规划 DP、状压 DP
 *
 */

// 状压 DP：用二进制数 mask 表示一个集合（第 i 位为 1 表示第 i 个元素在集合中），把集合作为 DP 的状态。
// 适用于 n <= 20 左右的问题。

// 1. 旅行商问题（TSP）：从 0 出发经过每个点恰好一次再回到 0 的最短回路。O(2^n · n^2)
//    f[mask][i]：已经访问过 mask 中的点、当前在 i 的最短路程
ll tsp(const vector<vector<ll>> &d) {
    int n = d.size();
    if (n == 1) return 0;
    const ll INF = LLONG_MAX / 4;
    vector<vector<ll>> f(1 << n, vector<ll>(n, INF));
    f[1][0] = 0;
    for (int mask = 1; mask < (1 << n); mask++)
        for (int i = 0; i < n; i++) {
            if (f[mask][i] >= INF || !(mask >> i & 1)) continue;
            for (int j = 0; j < n; j++)
                if (!(mask >> j & 1)) f[mask | 1 << j][j] = min(f[mask | 1 << j][j], f[mask][i] + d[i][j]);
        }
    ll best = INF;
    for (int i = 1; i < n; i++) best = min(best, f[(1 << n) - 1][i] + d[i][0]);
    return best;
}

// 2. 棋盘类状压（洛谷 P1879 Corn Fields）：在可种植的格子（fertile[i][j] = 1）中选一些种草，
//    任意两块不能上下左右相邻，求方案数（可以一块都不种）。逐行转移，状态为这一行选了哪些格子。
//    一行内不相邻：(s & (s << 1)) == 0；上下不相邻：(s & t) == 0。O(rows · 合法状态数^2)
ll corn_fields(const vector<vector<int>> &fertile, ll mod) {
    int R = fertile.size(), C = fertile[0].size();
    vector<int> good;   // 一行内不相邻的状态
    for (int s = 0; s < (1 << C); s++)
        if (!(s & (s << 1))) good.push_back(s);
    vector<ll> f(1 << C, 0);
    f[0] = 1 % mod;   // 第 0 行之前：空状态
    for (int i = 0; i < R; i++) {
        int allow = 0;
        for (int j = 0; j < C; j++)
            if (fertile[i][j]) allow |= 1 << j;
        vector<ll> g(1 << C, 0);
        for (int s : good) {
            if ((s & allow) != s) continue;
            for (int t : good)
                if (!(s & t) && f[t]) g[s] = (g[s] + f[t]) % mod;
        }
        f = g;
    }
    ll ans = 0;
    for (ll v : f) ans = (ans + v) % mod;
    return ans;
}

// 3. 高维前缀和（SOS DP）：f[mask] = Σ_{sub ⊆ mask} a[sub]。逐位做前缀和，O(n · 2^n)（直接枚举子集为 O(3^n)）
vector<ll> sos_subset_sum(vector<ll> a, int n) {
    for (int b = 0; b < n; b++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask >> b & 1) a[mask] += a[mask ^ (1 << b)];
    return a;
}
//    超集和：把条件改成 !(mask >> b & 1)，a[mask] += a[mask | (1 << b)]
