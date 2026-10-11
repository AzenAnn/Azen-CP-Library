/**
 * 02_ds/07 线段树（含懒标记）
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：02_ds/06 树状数组
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 建树、单点修改、区间查询
 *   2. 懒标记：区间加、区间求和
 *   3. 多种标记：先乘后加
 *   4. 维护可合并的信息（最大子段和）
 *   5. 线段树上二分
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/seg/
 *   cp-algorithms  https://cp-algorithms.com/data_structures/segment_tree.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/segment_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3372  P3372 【模板】线段树 1
 *   https://www.luogu.com.cn/problem/P3373  P3373 【模板】线段树 2
 *   https://www.luogu.com.cn/problem/P4513  P4513 小白逛公园
 *   https://judge.yosupo.jp/problem/point_set_range_composite  （Library Checker）
 *   https://judge.yosupo.jp/problem/range_affine_range_sum  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1110  普及  P1110 [ZJOI2007] 报表统计  考点：线段树、平衡树、堆
 *   https://www.luogu.com.cn/problem/P13976  普及  P13976 数列分块入门 1  考点：线段树、树状数组、分块
 *   https://www.luogu.com.cn/problem/P1840  普及  P1840 Color the Axis  考点：线段树、并查集、颜色段均摊（珂朵莉树 ODT）
 *   https://www.luogu.com.cn/problem/P2073  普及  P2073 送花  考点：线段树、平衡树、STL
 *   https://www.luogu.com.cn/problem/P1253  普及+/提高−  P1253 扶苏的问题  考点：线段树
 *   https://www.luogu.com.cn/problem/P1438  普及+/提高−  P1438 无聊的数列  考点：线段树、树状数组、分块
 *   https://www.luogu.com.cn/problem/P2068  普及+/提高−  P2068 统计和  考点：线段树、树状数组
 *   https://www.luogu.com.cn/problem/P4588  普及+/提高−  P4588 [TJOI2018] 数学计算  考点：线段树
 *   https://codeforces.com/problemset/problem/1413/D  CF1700  CF1413D Shurikens  考点：数据结构、贪心、实现
 *   https://codeforces.com/problemset/problem/1042/D  CF1800  CF1042D Petya and Array  考点：数据结构、分治、双指针
 *   https://codeforces.com/problemset/problem/1208/D  CF1900  CF1208D Restore Permutation  考点：二分、数据结构、贪心
 *   https://codeforces.com/problemset/problem/914/D  CF1900  CF914D Bash and a Tough Math Puzzle  考点：数据结构、数论
 *   https://codeforces.com/problemset/problem/380/C  CF2000  CF380C Sereja and Brackets  考点：数据结构、调度
 *   https://codeforces.com/problemset/problem/920/F  CF2000  CF920F SUM and REPLACE  考点：暴力、数据结构、并查集
 *   https://codeforces.com/problemset/problem/52/C  CF2200  CF52C Circular RMQ  考点：数据结构
 *
 */

// 通用懒标记线段树：只需要定义两个结构体
//   Info：区间信息。要有 Info operator+(左区间, 右区间) 表示合并，默认构造的 Info 表示空区间
//         以及成员函数 void apply(const Tag &t)：把标记作用到区间信息上
//   Tag ：懒标记。默认构造表示"什么也不做"，成员函数 void apply(const Tag &t)：在旧标记之后叠加新标记
// 下标从 0 开始，所有区间都是左闭右开 [l, r)
template <class Info, class Tag>
struct LazySegTree {
    int n;
    vector<Info> info;
    vector<Tag> tag;
    LazySegTree(const vector<Info> &a) : n(a.size()), info(4 * max(n, 1)), tag(4 * max(n, 1)) {
        if (n) build(1, 0, n, a);
    }
    void build(int p, int l, int r, const vector<Info> &a) {
        if (r - l == 1) { info[p] = a[l]; return; }
        int m = (l + r) / 2;
        build(2 * p, l, m, a), build(2 * p + 1, m, r, a);
        pull(p);
    }
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    void apply(int p, const Tag &t) { info[p].apply(t), tag[p].apply(t); }
    void push(int p) { apply(2 * p, tag[p]), apply(2 * p + 1, tag[p]), tag[p] = Tag(); }

    // 单点赋值 a[x] = v
    void modify(int x, const Info &v) { modify(1, 0, n, x, v); }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) { info[p] = v; return; }
        int m = (l + r) / 2;
        push(p);
        if (x < m) modify(2 * p, l, m, x, v);
        else modify(2 * p + 1, m, r, x, v);
        pull(p);
    }
    // 区间查询 [x, y)
    Info query(int x, int y) { return query(1, 0, n, x, y); }
    Info query(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) return Info();
        if (l >= x && r <= y) return info[p];
        int m = (l + r) / 2;
        push(p);
        return query(2 * p, l, m, x, y) + query(2 * p + 1, m, r, x, y);
    }
    // 区间修改：对 [x, y) 打上标记 t
    void range_apply(int x, int y, const Tag &t) { range_apply(1, 0, n, x, y, t); }
    void range_apply(int p, int l, int r, int x, int y, const Tag &t) {
        if (l >= y || r <= x) return;
        if (l >= x && r <= y) { apply(p, t); return; }
        int m = (l + r) / 2;
        push(p);
        range_apply(2 * p, l, m, x, y, t), range_apply(2 * p + 1, m, r, x, y, t);
        pull(p);
    }
    // 线段树上二分：[x, y) 中第一个满足 pred(a[i]) 的下标 i，不存在返回 -1
    // 要求 pred 对合并"单调"：只要区间里有一个元素满足，pred(区间的 Info) 就为真（如 mx >= k）
    template <class F>
    int find_first(int x, int y, F pred) { return find_first(1, 0, n, x, y, pred); }
    template <class F>
    int find_first(int p, int l, int r, int x, int y, F &pred) {
        if (l >= y || r <= x || !pred(info[p])) return -1;
        if (r - l == 1) return l;
        int m = (l + r) / 2;
        push(p);
        int res = find_first(2 * p, l, m, x, y, pred);
        if (res == -1) res = find_first(2 * p + 1, m, r, x, y, pred);
        return res;
    }
};

// ===== 例 1：区间加、区间求和、区间最大值（洛谷 P3372）=====
// 建树：vector<SumInfo> init(n); for (i) init[i] = {a[i], a[i], 1};
//       LazySegTree<SumInfo, AddTag> seg(init);
//       seg.range_apply(l, r, {x});   seg.query(l, r).sum;
struct AddTag {
    ll add = 0;
    void apply(const AddTag &t) { add += t.add; }
};
struct SumInfo {
    ll sum = 0, mx = LLONG_MIN;
    int len = 0;   // 区间长度；叶子为 1，空区间为 0
    void apply(const AddTag &t) {
        sum += t.add * len;
        if (len) mx += t.add;
    }
};
SumInfo operator+(const SumInfo &a, const SumInfo &b) {
    return {a.sum + b.sum, max(a.mx, b.mx), a.len + b.len};
}

// ===== 例 2：区间乘、区间加、区间求和，对 AFFINE_MOD 取模（洛谷 P3373）=====
// 标记表示 x -> x * mul + add；先乘后加。新标记 t 叠加在旧标记之后：
//   (x * mul + add) * t.mul + t.add = x * (mul * t.mul) + (add * t.mul + t.add)
ll AFFINE_MOD = 998244353;   // 按题目修改
struct AffineTag {
    ll mul = 1, add = 0;
    void apply(const AffineTag &t) {
        mul = mul * t.mul % AFFINE_MOD;
        add = (add * t.mul + t.add) % AFFINE_MOD;
    }
};
struct ModSumInfo {
    ll sum = 0;
    int len = 0;
    void apply(const AffineTag &t) { sum = (sum * t.mul + t.add % AFFINE_MOD * len) % AFFINE_MOD; }
};
ModSumInfo operator+(const ModSumInfo &a, const ModSumInfo &b) {
    return {(a.sum + b.sum) % AFFINE_MOD, a.len + b.len};
}

// ===== 例 3：单点修改、区间最大子段和（洛谷 P4513），不需要懒标记 =====
// 用 LazySegTree<SubInfo, NoTag>，叶子为 SubInfo::leaf(a[i])，只用 modify 和 query
struct NoTag {
    void apply(const NoTag &) {}
};
struct SubInfo {
    ll sum = 0, pre = 0, suf = 0, best = 0;   // 区间和、最大前缀和、最大后缀和、最大子段和（均非空）
    bool empty = true;
    static SubInfo leaf(ll x) { return {x, x, x, x, false}; }
    void apply(const NoTag &) {}
};
SubInfo operator+(const SubInfo &a, const SubInfo &b) {
    if (a.empty) return b;
    if (b.empty) return a;
    return {a.sum + b.sum, max(a.pre, a.sum + b.pre), max(b.suf, b.sum + a.suf),
            max({a.best, b.best, a.suf + b.pre}), false};
}
