/**
 * 06_dp/10 斜率优化与凸包技巧
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：06_dp/08 单调队列 / 单调栈优化 DP
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 把转移写成直线形式
 *   2. 单调队列维护下凸壳
 *   3. 李超线段树做法
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/opt/slope/
 *   cp-algorithms  https://cp-algorithms.com/geometry/convex_hull_trick.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/dp.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3195  P3195 [HNOI2008] 玩具装箱
 *   https://www.luogu.com.cn/problem/P5785  P5785 [SDOI2012] 任务安排
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/1083/E  CF2400  CF1083E The Fair Nut and Rectangles  考点：数据结构、DP、计算几何
 *   https://codeforces.com/problemset/problem/311/B  CF2400  CF311B Cats Transport  考点：数据结构、DP
 *   https://www.luogu.com.cn/problem/P5468  省选/NOI−  P5468 [NOI2019] 回家路线  考点：动态规划 DP、深度优先搜索 DFS、斜率优化
 *   https://www.luogu.com.cn/problem/P5504  省选/NOI−  P5504 [JSOI2011] 柠檬  考点：动态规划 DP、动态规划优化、斜率优化
 *   https://www.luogu.com.cn/problem/P6302  省选/NOI−  P6302 [NOI2019] 回家路线 加强版  考点：动态规划 DP、斜率优化
 *   https://codeforces.com/problemset/problem/660/F  CF2500  CF660F Bear and Bowling 4  考点：二分、数据结构、分治
 *   https://codeforces.com/problemset/problem/631/E  CF2600  CF631E Product Sum  考点：数据结构、DP、计算几何
 *   https://codeforces.com/problemset/problem/932/F  CF2700  CF932F Escape Through Leaf  考点：数据结构、DP、计算几何
 *   https://codeforces.com/problemset/problem/2107/F2  CF2800  CF2107F2 Cycling (Hard Version)  考点：二分、暴力、数据结构
 *   https://www.luogu.com.cn/problem/P1721  NOI/NOI+/CTS  P1721 [NOI2016] 国王饮水记  考点：动态规划 DP、斜率优化
 *   https://www.luogu.com.cn/problem/P2305  NOI/NOI+/CTS  P2305 [NOI2014] 购票  考点：图论、线段树、分治
 *   https://www.luogu.com.cn/problem/P3571  NOI/NOI+/CTS  P3571 [POI 2014] SUP-Supercomputer  考点：斜率优化、凸包
 *   https://www.luogu.com.cn/problem/P5896  NOI/NOI+/CTS  P5896 [IOI 2016] aliens  考点：动态规划 DP、斜率优化、凸完全单调性（wqs 二分）
 *   https://www.luogu.com.cn/problem/P6246  NOI/NOI+/CTS  P6246 [IOI 2000] 邮局 加强版 加强版  考点：二分、斜率优化、凸完全单调性（wqs 二分）
 *   https://codeforces.com/problemset/problem/1175/G  CF3000  CF1175G Yet Another Partiton Problem  考点：数据结构、分治、DP
 *
 */

// 斜率优化：转移形如 f[i] = min_j (f[j] + A(i)·B(j) + C(j)) + D(i) 时，
// 把每个决策 j 看成平面上的点 (X_j, Y_j)，问题变成"用斜率为 k_i 的直线去切点集"，
// 最优点一定在下凸壳上。若 X_j 单调、k_i 单调，可以用单调队列维护凸壳，均摊 O(n)。

// 1. 例（洛谷 P3195 玩具装箱）：把 n 个玩具按顺序分段装箱，一段 [j+1, i] 的代价为 (i - j - 1 + Σc - L)^2，求最小总代价。
//    令 s[i] = Σ_{k<=i} (c[k] + 1)，L' = L + 1，则 f[i] = min_j f[j] + (s[i] - s[j] - L')^2。
//    展开：f[j] + s[j]^2 = 2(s[i] - L')·s[j] + f[i] - (s[i] - L')^2，点为 (s[j], f[j] + s[j]^2)，斜率 2(s[i] - L') 递增。
//    数值很大，比较斜率时用 __int128 做交叉相乘，避免除法和溢出
ll toy_packing(const vector<ll> &c, ll L) {
    int n = c.size();
    vector<__int128> s(n + 1, 0), X(n + 1), Y(n + 1);
    vector<ll> f(n + 1, 0);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + c[i - 1] + 1;
    __int128 Lp = L + 1;
    X[0] = 0, Y[0] = 0;
    deque<int> q{0};
    for (int i = 1; i <= n; i++) {
        __int128 k = 2 * (s[i] - Lp);
        // 队头两点连线的斜率 <= k 时，队头不再是最优，弹出
        while (q.size() >= 2 && Y[q[1]] - Y[q[0]] <= k * (X[q[1]] - X[q[0]])) q.pop_front();
        int j = q.front();
        __int128 d = s[i] - s[j] - Lp;
        f[i] = (ll)(f[j] + d * d);
        X[i] = s[i], Y[i] = f[i] + s[i] * s[i];
        // 维护下凸壳：新点使队尾不再是凸壳上的点时弹出
        while (q.size() >= 2) {
            int a = q[q.size() - 2], b = q.back();
            if ((Y[b] - Y[a]) * (X[i] - X[b]) >= (Y[i] - Y[b]) * (X[b] - X[a])) q.pop_back();
            else break;
        }
        q.push_back(i);
    }
    return f[n];
}

// 2. 一般情况（斜率、查询都不单调）：用 LineContainer 维护直线 y = kx + m，
//    任意顺序插入、查询 x 处的最大值，都是 O(log n)（KACTL 的写法）。求最小值时把 k、m 取相反数
struct CHTLine {
    mutable ll k, m, p;   // p：这条直线在凸壳上的右端点（与下一条直线的交点）
    bool operator<(const CHTLine &o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};
struct LineContainer : multiset<CHTLine, less<>> {
    static const ll INF = LLONG_MAX;
    static ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }   // 向下取整的除法
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = INF, false;
        if (x->k == y->k) x->p = x->m > y->m ? INF : -INF;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }
    ll query(ll x) const {   // 要求非空
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
