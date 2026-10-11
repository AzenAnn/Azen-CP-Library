/**
 * 06_dp/11 四边形不等式与决策单调性
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：06_dp/04 区间 DP
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 四边形不等式
 *   2. 分治优化
 *   3. Knuth 优化
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/opt/quadrangle/
 *   cp-algorithms  https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html
 *   cp-algorithms  https://cp-algorithms.com/dynamic_programming/knuth-optimization.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/dp.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1912  P1912 [NOI2009] 诗人小G
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10786  省选/NOI−  P10786 [NOI2024] 百万富翁  考点：动态规划 DP、搜索、动态规划优化
 *   https://www.luogu.com.cn/problem/P3515  省选/NOI−  P3515 [POI 2011] Lightning Conductor  考点：动态规划 DP、凸完全单调性（wqs 二分）、四边形不等式
 *   https://www.luogu.com.cn/problem/P4767  省选/NOI−  P4767 [IOI 2000] 邮局 加强版  考点：数学、枚举、区间 DP
 *   https://www.luogu.com.cn/problem/P4983  省选/NOI−  P4983 忘情  考点：斜率优化、凸完全单调性（wqs 二分）、四边形不等式
 *   https://www.luogu.com.cn/problem/P5308  省选/NOI−  P5308 [COCI 2018/2019 #4] Akvizna  考点：斜率优化、凸完全单调性（wqs 二分）、决策单调性
 *   https://www.luogu.com.cn/problem/P5503  省选/NOI−  P5503 [JSOI2016] 灯塔  考点：动态规划 DP、凸完全单调性（wqs 二分）、四边形不等式
 *   https://www.luogu.com.cn/problem/P5892  省选/NOI−  P5892 [IOI 2014] holiday 假期  考点：分治、可持久化线段树、决策单调性
 *   https://www.luogu.com.cn/problem/P6173  省选/NOI−  P6173 [USACO16FEB] Circular Barn P  考点：动态规划 DP、分治、动态规划优化
 *   https://www.luogu.com.cn/problem/P14471  NOI/NOI+/CTS  P14471 [集训队互测 2025] 火花  考点：动态规划 DP、分治、动态规划优化
 *   https://www.luogu.com.cn/problem/P17319  NOI/NOI+/CTS  P17319 [ICPC 2018 Nanjing R] Tournament  考点：动态规划优化、凸完全单调性（wqs 二分）、四边形不等式
 *   https://www.luogu.com.cn/problem/P5244  NOI/NOI+/CTS  P5244 [USACO19FEB] Mowing Mischief P  考点：动态规划 DP、线段树、动态规划优化
 *   https://www.luogu.com.cn/problem/P5617  NOI/NOI+/CTS  P5617 [MtOI2019] 不可视境界线  考点：动态规划 DP、数学、计算几何
 *   https://www.luogu.com.cn/problem/P8864  NOI/NOI+/CTS  P8864 「KDOI-03」序列变换  考点：动态规划 DP、动态规划优化、矩阵加速
 *   https://www.luogu.com.cn/problem/P9266  NOI/NOI+/CTS  P9266 [PA 2022] Nawiasowe podziały  考点：莫队、凸完全单调性（wqs 二分）、笛卡尔树
 *   https://www.luogu.com.cn/problem/P9732  NOI/NOI+/CTS  P9732 [CEOI 2023] Trade  考点：线段树、并查集、决策单调性
 *
 */

// 四边形不等式：若对 a <= b <= c <= d 有 w(a, c) + w(b, d) <= w(a, d) + w(b, c)，
// 则形如 f[i] = min_j f[j] + w(j, i) 的转移具有"决策单调性"：最优决策点 opt(i) 随 i 单调不减。
// 常见满足条件的代价：w(j, i) = (区间和)^2、区间长度的凸函数等。

// 1. 分治优化：把序列分成 K 段，f[k][i] = min_{j < i} f[k-1][j] + cost(j, i)（段为 [j, i)），每层 O(n log n)。
//    求 mid 的最优决策时只在 [optl, optr] 中找，再递归左右两半。返回把 n 个元素分成恰好 K 段的最小代价
template <class Cost>
ll partition_min_cost(int n, int K, Cost cost) {
    const ll INF = LLONG_MAX / 4;
    vector<ll> prev(n + 1, INF), cur(n + 1, INF);
    prev[0] = 0;
    for (int k = 1; k <= K; k++) {
        fill(cur.begin(), cur.end(), INF);
        function<void(int, int, int, int)> solve = [&](int l, int r, int optl, int optr) {
            if (l > r) return;
            int mid = (l + r) / 2, best = -1;
            ll bv = INF;
            for (int j = optl; j <= min(mid - 1, optr); j++) {
                if (prev[j] >= INF) continue;
                ll v = prev[j] + cost(j, mid);
                if (v < bv) bv = v, best = j;
            }
            cur[mid] = bv;
            if (best == -1) best = optl;
            solve(l, mid - 1, optl, best), solve(mid + 1, r, best, optr);
        };
        solve(1, n, 0, n - 1);
        swap(prev, cur);
    }
    return prev[n];
}

// 2. Knuth 优化（区间 DP）：f[l][r] = min_{l <= k < r} f[l][k] + f[k+1][r] + w(l, r)，
//    w 满足四边形不等式且区间包含单调时，opt[l][r-1] <= opt[l][r] <= opt[l+1][r]，总复杂度降为 O(n^2)。
//    例：石子合并（链），w(l, r) = 区间和
ll stone_merge_knuth(const vector<ll> &a) {
    int n = a.size();
    if (n <= 1) return 0;
    vector<ll> s(n + 1, 0);
    for (int i = 0; i < n; i++) s[i + 1] = s[i] + a[i];
    vector<vector<ll>> f(n, vector<ll>(n, 0));
    vector<vector<int>> opt(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) opt[i][i] = i;
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            f[l][r] = LLONG_MAX;
            for (int k = opt[l][r - 1]; k <= min(opt[l + 1][r], r - 1); k++) {
                ll v = f[l][k] + f[k + 1][r] + s[r + 1] - s[l];
                if (v < f[l][r]) f[l][r] = v, opt[l][r] = k;
            }
        }
    return f[0][n - 1];
}

// 3. 1D/1D 的决策单调性也可以用"二分 + 单调队列"维护每个决策负责的区间（洛谷 P1912 诗人小G），O(n log n)
