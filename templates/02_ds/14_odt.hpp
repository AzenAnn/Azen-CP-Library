/**
 * 02_ds/14 珂朵莉树（ODT）
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/12 平衡树
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 用 set 维护颜色段
 *   2. split / assign 操作
 *   3. 适用条件：有区间赋值、数据随机
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/misc/odt/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/odt.go
 *
 * 【模板题 / 入门题】
 *   https://codeforces.com/problemset/problem/896/C  CF896C Willem, Chtholly and Seniorious
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P13980  提高  P13980 数列分块入门 5  考点：暴力数据结构、线段树、并查集
 *   https://www.luogu.com.cn/problem/P1442  提高  P1442 铁球落地  考点：动态规划 DP、线段树、颜色段均摊（珂朵莉树 ODT）
 *   https://www.luogu.com.cn/problem/P2061  提高  P2061 [USACO07OPEN] City Horizon S  考点：线段树、颜色段均摊（珂朵莉树 ODT）、离散化
 *   https://www.luogu.com.cn/problem/P2894  提高  P2894 [USACO08FEB] Hotel G  考点：线段树、二分、颜色段均摊（珂朵莉树 ODT）
 *   https://codeforces.com/problemset/problem/292/E  CF1900  CF292E Copying Data  考点：数据结构
 *   https://www.luogu.com.cn/problem/P2146  提高+/省选−  P2146 [NOI2015] 软件包管理器  考点：树形数据结构、线段树、颜色段均摊（珂朵莉树 ODT）
 *   https://www.luogu.com.cn/problem/P2824  提高+/省选−  P2824 [HEOI2016/TJOI2016] 排序  考点：线段树、二分、颜色段均摊（珂朵莉树 ODT）
 *   https://codeforces.com/problemset/problem/558/E  CF2300  CF558E A Simple Task  考点：数据结构、排序、字符串
 *   https://codeforces.com/problemset/problem/817/F  CF2300  CF817F MEX Queries  考点：二分、数据结构、树
 *   https://codeforces.com/problemset/problem/915/E  CF2300  CF915E Physical Education Lessons  考点：数据结构、实现、排序
 *   https://codeforces.com/problemset/problem/1638/E  CF2400  CF1638E Colorful Operations  考点：暴力、数据结构、实现
 *   https://www.luogu.com.cn/problem/P4690  省选/NOI−  P4690 [Ynoi Easy Round 2016] 镜中的昆虫  考点：树状数组、颜色段均摊（珂朵莉树 ODT）、cdq 分治
 *   https://www.luogu.com.cn/problem/P5350  省选/NOI−  P5350 序列  考点：平衡树、颜色段均摊（珂朵莉树 ODT）、可持久化
 *   https://www.luogu.com.cn/problem/P5586  省选/NOI−  P5586 [P5350] 序列 (加强版)  考点：平衡树、可持久化
 *   https://codeforces.com/problemset/problem/981/G  CF2500  CF981G Magic multisets  考点：数据结构
 *
 */

// 珂朵莉树（ODT）：用 map 把序列存成若干"值相同的连续段"，key 为段的左端点。
// 有区间赋值操作、且数据随机时，段数很快变少，复杂度期望 O(n log log n)；数据不随机时会被卡。
// 下标从 0 开始，区间左闭右开 [l, r)
struct ODT {
    int n;
    map<int, ll> seg;   // seg[l] = v 表示从 l 到下一个段的左端点之前，值都是 v
    ODT(const vector<ll> &a) : n(a.size()) {
        for (int i = 0; i < n; i++) seg[i] = a[i];
        seg[n] = 0;   // 哨兵
    }
    // 在 pos 处切开，返回以 pos 为左端点的段
    map<int, ll>::iterator split(int pos) {
        auto it = seg.lower_bound(pos);
        if (it != seg.end() && it->first == pos) return it;
        --it;
        return seg.emplace(pos, it->second).first;
    }
    // 区间赋值：删除 [l, r) 内的所有段，换成一个段
    void assign(int l, int r, ll v) {
        auto itr = split(r), itl = split(l);   // 必须先 split(r) 再 split(l)，否则 itl 可能失效
        seg.erase(itl, itr);
        seg[l] = v;
    }
    // 其他操作都是"切出 [l, r)，然后暴力遍历其中的段"
    template <class F>
    void for_each(int l, int r, F f) {   // f(段左端点, 段右端点, 值的引用)
        auto itr = split(r), itl = split(l);
        for (auto it = itl; it != itr; ++it) f(it->first, next(it)->first, it->second);
    }
    void add(int l, int r, ll x) {
        for_each(l, r, [&](int, int, ll &v) { v += x; });
    }
    ll kth(int l, int r, int k) {   // 区间第 k 小（k 从 1 开始）
        vector<pair<ll, int>> v;
        for_each(l, r, [&](int a, int b, ll &x) { v.push_back({x, b - a}); });
        sort(v.begin(), v.end());
        for (auto [x, c] : v)
            if ((k -= c) <= 0) return x;
        return -1;
    }
    ll pow_sum(int l, int r, ll e, ll mod) {   // Σ a[i]^e mod mod（CF896C 的操作 4）
        ll res = 0;
        for_each(l, r, [&](int a, int b, ll &x) {
            ll base = x % mod, p = 1 % mod;
            for (ll t = e; t; t >>= 1, base = base * base % mod)
                if (t & 1) p = p * base % mod;
            res = (res + p * (b - a)) % mod;
        });
        return res;
    }
};
