/**
 * 02_ds/10 分块与根号分治
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/07 线段树（含懒标记）
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 块状数组：区间加、区间求和
 *   2. 整块打标记、散块暴力
 *   3. 根号分治（按大小分两类处理）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/decompose/
 *   cp-algorithms  https://cp-algorithms.com/data_structures/sqrt_decomposition.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/sqrt_decomposition.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2801  P2801 教主的魔法
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1471  提高  P1471 方差  考点：数学、线段树、分块
 *   https://www.luogu.com.cn/problem/P1533  提高  P1533 可怜的狗狗  考点：莫队、线段树、二分
 *   https://www.luogu.com.cn/problem/P1989  提高  P1989 【模板】无向图三元环计数  考点：图论、枚举、根号分治
 *   https://www.luogu.com.cn/problem/P4145  提高  P4145 上帝造题的七分钟 2 / 花神游历各国  考点：线段树、并查集、树状数组
 *   https://codeforces.com/problemset/problem/1921/F  CF1900  CF1921F Sum of Progression  考点：暴力、数据结构、DP
 *   https://codeforces.com/problemset/problem/797/E  CF2000  CF797E Array Queries  考点：暴力、数据结构、DP
 *   https://www.luogu.com.cn/problem/P3203  提高+/省选−  P3203 [HNOI2010] 弹飞绵羊  考点：平衡树、动态树 LCT、分块
 *   https://codeforces.com/problemset/problem/1207/F  CF2100  CF1207F Remainder Problem  考点：暴力、数据结构、实现
 *   https://codeforces.com/problemset/problem/1790/F  CF2100  CF1790F Timofey and Black-White Tree  考点：暴力、搜索、分治
 *   https://codeforces.com/problemset/problem/1806/E  CF2200  CF1806E Tree Master  考点：暴力、数据结构、搜索
 *   https://codeforces.com/problemset/problem/342/E  CF2400  CF342E Xenia and Tree  考点：数据结构、分治、树
 *   https://www.luogu.com.cn/problem/P3157  省选/NOI−  P3157 [CQOI2011] 动态逆序对  考点：树状数组、cdq 分治、树套树
 *   https://www.luogu.com.cn/problem/P4168  省选/NOI−  P4168 [Violet] 蒲公英  考点：离散化、枚举、分块
 *   https://www.luogu.com.cn/problem/P6466  省选/NOI−  P6466 【模板】分散层叠算法（Fractional Cascading）  考点：二分、排序、分散层叠
 *   https://codeforces.com/problemset/problem/13/E  CF2700  CF13E Holes  考点：数据结构、并查集
 *
 */

// 分块：把序列分成大小约为 B = √n 的块。修改 / 查询时，完整的块整体处理（打标记），
// 两端不完整的"散块"暴力处理。单次操作 O(√n)。下标从 0 开始，区间左闭右开 [l, r)

// 1. 区间加、区间求和
struct BlockSum {
    int n, B;
    vector<ll> a, sum, tag;   // tag[k]：第 k 块整体加了多少（还没加到 a 上）
    BlockSum(const vector<ll> &v) : n(v.size()), B(max(1, (int)sqrt(v.size()))), a(v) {
        sum.assign(n / B + 1, 0), tag.assign(n / B + 1, 0);
        for (int i = 0; i < n; i++) sum[i / B] += a[i];
    }
    void add(int l, int r, ll x) {
        while (l < r && l % B) a[l] += x, sum[l / B] += x, l++;              // 左边散块
        while (l + B <= r) tag[l / B] += x, sum[l / B] += x * B, l += B;     // 完整的块
        while (l < r) a[l] += x, sum[l / B] += x, l++;                        // 右边散块
    }
    ll query(int l, int r) const {
        ll s = 0;
        while (l < r && l % B) s += a[l] + tag[l / B], l++;
        while (l + B <= r) s += sum[l / B], l += B;
        while (l < r) s += a[l] + tag[l / B], l++;
        return s;
    }
};

// 2. 区间加、查询区间内 >= x 的数的个数（洛谷 P2801 教主的魔法）
//    每块额外保存一份排好序的副本；整块加不改变块内顺序，只改标记；散块修改后重新排序。
//    查询时整块用二分，单次 O(√n log n)
struct BlockCount {
    int n, B;
    vector<ll> a, tag;
    vector<vector<ll>> sorted;
    BlockCount(const vector<ll> &v) : n(v.size()), B(max(1, (int)sqrt(v.size()))), a(v) {
        int k = (n + B - 1) / B;
        tag.assign(k, 0), sorted.resize(k);
        for (int b = 0; b < k; b++) rebuild(b);
    }
    void rebuild(int b) {
        sorted[b].assign(a.begin() + b * B, a.begin() + min(n, (b + 1) * B));
        sort(sorted[b].begin(), sorted[b].end());
    }
    void add(int l, int r, ll x) {
        if (l >= r) return;
        int bl = l / B, br = (r - 1) / B;
        if (bl == br) {
            for (int i = l; i < r; i++) a[i] += x;
            rebuild(bl);
            return;
        }
        for (int i = l; i < (bl + 1) * B; i++) a[i] += x;
        rebuild(bl);
        for (int b = bl + 1; b < br; b++) tag[b] += x;
        for (int i = br * B; i < r; i++) a[i] += x;
        rebuild(br);
    }
    int count_ge(int l, int r, ll x) const {
        if (l >= r) return 0;
        int bl = l / B, br = (r - 1) / B, res = 0;
        if (bl == br) {
            for (int i = l; i < r; i++) res += a[i] + tag[bl] >= x;
            return res;
        }
        for (int i = l; i < (bl + 1) * B; i++) res += a[i] + tag[bl] >= x;
        for (int b = bl + 1; b < br; b++)
            res += sorted[b].end() - lower_bound(sorted[b].begin(), sorted[b].end(), x - tag[b]);
        for (int i = br * B; i < r; i++) res += a[i] + tag[br] >= x;
        return res;
    }
};

// 3. 根号分治：按某个量和 √n 的大小关系分两类，分别用两种算法。
//    例：多次询问"下标 ≡ y (mod x) 的元素之和"。x <= √n 时预处理 ans[x][y]（O(n√n)）；
//    x > √n 时这样的下标不超过 √n 个，直接暴力累加。
