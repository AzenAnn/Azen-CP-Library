/**
 * 02_ds/06 树状数组
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：01_basic/02 前缀和与差分、01_basic/06 位运算
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 单点修改、区间查询
 *   2. 区间修改、单点查询（差分）
 *   3. 区间修改、区间查询（两个树状数组）
 *   4. 权值树状数组求逆序对
 *   5. 树状数组上二分求第 k 小
 *   6. 二维树状数组
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/fenwick/
 *   cp-algorithms  https://cp-algorithms.com/data_structures/fenwick.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/fenwick_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3374  P3374 【模板】树状数组 1
 *   https://www.luogu.com.cn/problem/P3368  P3368 【模板】树状数组 2
 *   https://www.luogu.com.cn/problem/P1908  P1908 逆序对
 *   https://judge.yosupo.jp/problem/point_add_range_sum  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1774  普及  P1774 最接近神的人  考点：线段树、树状数组、递归
 *   https://www.luogu.com.cn/problem/P2286  普及  P2286 [HNOI2004] 宠物收养场  考点：线段树、平衡树、树状数组
 *   https://www.luogu.com.cn/problem/P2782  普及  P2782 友好城市  考点：动态规划 DP、线段树、二分
 *   https://www.luogu.com.cn/problem/P3902  普及  P3902 递增  考点：动态规划 DP、二分、树状数组
 *   https://www.luogu.com.cn/problem/P2163  普及+/提高−  P2163 [SHOI2007] 园丁的烦恼  考点：树状数组、离散化、cdq 分治
 *   https://www.luogu.com.cn/problem/P5094  普及+/提高−  P5094 [USACO04OPEN] MooFest G 加强版  考点：树状数组、cdq 分治、分治
 *   https://codeforces.com/problemset/problem/1915/F  CF1500  CF1915F Greetings  考点：数据结构、分治、排序
 *   https://codeforces.com/problemset/problem/1234/D  CF1600  CF1234D Distinct Characters Queries  考点：数据结构
 *   https://www.luogu.com.cn/problem/P1966  提高  P1966 [NOIP 2013 提高组] 火柴排队  考点：贪心、树状数组、离散化
 *   https://www.luogu.com.cn/problem/P1972  提高  P1972 [SDOI2009] HH 的项链  考点：线段树、树状数组、可持久化线段树
 *   https://codeforces.com/problemset/problem/1430/E  CF1900  CF1430E String Reversal  考点：数据结构、贪心、字符串
 *   https://codeforces.com/problemset/problem/61/E  CF1900  CF61E Enemy is weak  考点：数据结构、树
 *   https://codeforces.com/problemset/problem/1891/F  CF2000  CF1891F A Growing Tree  考点：数据结构、搜索、树
 *   https://codeforces.com/problemset/problem/383/C  CF2000  CF383C Propagating tree  考点：数据结构、搜索、树
 *   https://codeforces.com/problemset/problem/629/D  CF2000  CF629D Babaei and Birthday Cake  考点：数据结构、DP
 *
 */

// 1. 树状数组：单点加、前缀和。下标从 1 开始
struct Fenwick {
    int n;
    vector<ll> t;
    Fenwick(int n) : n(n), t(n + 1) {}
    void add(int i, ll x) {
        for (; i <= n; i += i & -i) t[i] += x;
    }
    ll sum(int i) const {   // a[1] + ... + a[i]
        ll s = 0;
        for (; i > 0; i -= i & -i) s += t[i];
        return s;
    }
    ll sum(int l, int r) const { return sum(r) - sum(l - 1); }   // a[l] + ... + a[r]
    // 树状数组上二分：最小的 p 使 a[1] + ... + a[p] >= k（要求所有 a[i] >= 0），不存在返回 n + 1
    // 权值树状数组中，这就是"第 k 小的数"
    int lower_bound(ll k) const {
        int p = 0;
        for (int pw = n ? 1 << __lg(n) : 0; pw; pw >>= 1)
            if (p + pw <= n && t[p + pw] < k) p += pw, k -= t[p];
        return p + 1;
    }
};

// 2. 区间加、单点查询：用 Fenwick 维护差分数组 d，
//    给 [l, r] 加 x 就是 add(l, x), add(r + 1, -x)；a[p] = sum(p)

// 3. 区间加、区间求和：维护差分 d，a[1..p] 的和 = (p + 1) * Σd[i] - Σ(i * d[i])
struct RangeFenwick {
    Fenwick b1, b2;   // b1 维护 d[i]，b2 维护 i * d[i]
    RangeFenwick(int n) : b1(n), b2(n) {}
    void add(int l, int r, ll x) {   // a[l..r] 加 x
        b1.add(l, x), b1.add(r + 1, -x);
        b2.add(l, x * l), b2.add(r + 1, -x * (r + 1));
    }
    ll prefix(int p) const { return (p + 1) * b1.sum(p) - b2.sum(p); }
    ll sum(int l, int r) const { return prefix(r) - prefix(l - 1); }
};

// 4. 逆序对：离散化后从左到右扫，统计前面比 a[i] 大的个数
ll count_inversions(const vector<ll> &a) {
    vector<ll> v(a);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    Fenwick f(v.size());
    ll res = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        int id = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        res += i - f.sum(id);   // 前面 i 个数中 > a[i] 的个数
        f.add(id, 1);
    }
    return res;
}

// 5. 二维树状数组：单点加、子矩阵求和。下标从 1 开始
struct Fenwick2D {
    int n, m;
    vector<vector<ll>> t;
    Fenwick2D(int n, int m) : n(n), m(m), t(n + 1, vector<ll>(m + 1)) {}
    void add(int x, int y, ll v) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j) t[i][j] += v;
    }
    ll sum(int x, int y) const {
        ll s = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j) s += t[i][j];
        return s;
    }
    ll sum(int x1, int y1, int x2, int y2) const {   // 左上 (x1, y1) 到右下 (x2, y2)
        return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
    }
};
