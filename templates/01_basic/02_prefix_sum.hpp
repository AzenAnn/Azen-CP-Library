/**
 * 01_basic/02 前缀和与差分
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 一维前缀和
 *   2. 二维前缀和
 *   3. 一维差分
 *   4. 二维差分
 *   5. 前缀和 + 哈希表（和为 k 的子数组）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/basic/prefix-sum/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P8218  P8218 【深进1.例1】求区间和
 *   https://www.luogu.com.cn/problem/P3397  P3397 地毯
 *   https://www.luogu.com.cn/problem/P2004  P2004 领地选择
 *   https://judge.yosupo.jp/problem/static_range_sum  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P15545  入门  P15545 「Stoi2037」晴天  考点：模拟、前缀和
 *   https://www.luogu.com.cn/problem/P1614  入门  P1614 爱与愁的心痛  考点：模拟、贪心、枚举
 *   https://www.luogu.com.cn/problem/P3717  入门  P3717 [AHOI2017初中组] cover  考点：模拟、搜索、枚举
 *   https://www.luogu.com.cn/problem/P4702  入门  P4702 取石子  考点：博弈论、进制、前缀和
 *   https://www.luogu.com.cn/problem/P1496  普及−  P1496 火烧赤壁  考点：模拟、离散化、排序
 *   https://www.luogu.com.cn/problem/P2345  入门  P2345 [USACO04OPEN] MooFest G  考点：模拟、枚举
 *   https://www.luogu.com.cn/problem/P2367  普及−  P2367 语文成绩  考点：差分
 *   https://codeforces.com/problemset/problem/1921/D  CF1100  CF1921D Very Different Array  考点：数据结构、贪心、排序
 *   https://www.luogu.com.cn/problem/P1083  普及  P1083 [NOIP 2012 提高组] 借教室  考点：线段树、二分、前缀和
 *   https://codeforces.com/problemset/problem/1006/C  CF1200  CF1006C Three Parts of the Array  考点：二分、数据结构、双指针
 *   https://codeforces.com/problemset/problem/1178/B  CF1300  CF1178B WOW Factor  考点：DP、字符串
 *   https://codeforces.com/problemset/problem/1915/E  CF1300  CF1915E Romantic Glasses  考点：数据结构、贪心、数学
 *   https://codeforces.com/problemset/problem/1923/C  CF1400  CF1923C Find B  考点：构造、贪心
 *   https://codeforces.com/problemset/problem/816/B  CF1400  CF816B Karen and Coffee  考点：二分、数据结构、实现
 *   https://codeforces.com/problemset/problem/276/C  CF1500  CF276C Little Girl and Maximum Sum  考点：数据结构、贪心、实现
 *
 */

// 1. 一维前缀和：s[i] = a[0] + ... + a[i-1]
//    下标从 0 开始，区间左闭右开：[l, r) 的和 = s[r] - s[l]
vector<ll> prefix_sum(const vector<ll> &a) {
    vector<ll> s(a.size() + 1);
    for (size_t i = 0; i < a.size(); i++) s[i + 1] = s[i] + a[i];
    return s;
}

// 2. 二维前缀和：s[i][j] = 以 (0,0) 为左上角、(i-1,j-1) 为右下角的矩形和
struct PrefixSum2D {
    vector<vector<ll>> s;
    PrefixSum2D(const vector<vector<ll>> &a) {
        int n = a.size(), m = n ? a[0].size() : 0;
        s.assign(n + 1, vector<ll>(m + 1));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                s[i + 1][j + 1] = s[i][j + 1] + s[i + 1][j] - s[i][j] + a[i][j];
    }
    // 行 [r1, r2) × 列 [c1, c2) 的子矩形和
    ll query(int r1, int c1, int r2, int c2) const {
        return s[r2][c2] - s[r1][c2] - s[r2][c1] + s[r1][c1];
    }
};

// 3. 一维差分：给 [l, r) 加 x 只需 d[l] += x, d[r] -= x，最后求前缀和还原
struct Diff1D {
    vector<ll> d;
    Diff1D(int n) : d(n + 1) {}
    void add(int l, int r, ll x) { d[l] += x, d[r] -= x; }
    vector<ll> build() const {
        vector<ll> a(d.size() - 1);
        ll cur = 0;
        for (size_t i = 0; i + 1 < d.size(); i++) cur += d[i], a[i] = cur;
        return a;
    }
};

// 4. 二维差分：给行 [r1, r2) × 列 [c1, c2) 加 x
struct Diff2D {
    int n, m;
    vector<vector<ll>> d;
    Diff2D(int n, int m) : n(n), m(m), d(n + 1, vector<ll>(m + 1)) {}
    void add(int r1, int c1, int r2, int c2, ll x) {
        d[r1][c1] += x, d[r1][c2] -= x, d[r2][c1] -= x, d[r2][c2] += x;
    }
    vector<vector<ll>> build() const {
        vector<vector<ll>> a(n, vector<ll>(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                a[i][j] = d[i][j] + (i ? a[i - 1][j] : 0) + (j ? a[i][j - 1] : 0) - (i && j ? a[i - 1][j - 1] : 0);
        return a;
    }
};

// 5. 和为 k 的子数组个数：枚举右端点，哈希表记录之前每个前缀和出现的次数
ll count_subarrays_sum_k(const vector<ll> &a, ll k) {
    unordered_map<ll, int> cnt;
    cnt[0] = 1;
    ll s = 0, ans = 0;
    for (ll x : a) {
        s += x;
        auto it = cnt.find(s - k);
        if (it != cnt.end()) ans += it->second;
        cnt[s]++;
    }
    return ans;
}
