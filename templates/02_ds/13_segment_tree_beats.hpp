/**
 * 02_ds/13 吉司机线段树（区间最值操作）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：02_ds/07 线段树（含懒标记）、02_ds/12 线段树进阶
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 区间取 min（a_i = min(a_i, x)）：每个节点维护最大值、严格次大值、最大值个数
 *   2. 三种情况：x ≥ 最大值 → 不用改；次大值 < x < 最大值 → 只改最大值（打标记，sum -= (mx − x)·cnt）；
 *      x ≤ 次大值 → 继续递归。势能分析：总复杂度 O((n + q) log n)（加上区间加后为 O(q log² n)）
 *   3. 同时支持区间取 max：对称地维护最小值、严格次小值；注意节点只有一两种值时两组信息会互相影响
 *   4. 标记下传：先下传加法标记，再用父亲的最大值 / 最小值去"修剪"儿子（不需要单独的 chmin 标记）
 *   5. 进阶：区间历史最大值（【模板】线段树 3、CPU 监控）—— 维护"加法标记的历史最大前缀"
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/seg-beats/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P10639  P10639 BZOJ4695 最假女选手
 *   https://www.luogu.com.cn/problem/P6242  P6242 【模板】线段树 3（区间最值操作、区间历史最值）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P13963  提高  P13963 [ICPC 2023 Nanjing R] 接雨水  考点：吉司机线段树 segment tree beats、线段树、颜色段均摊（珂朵莉树 ODT）
 *   https://www.luogu.com.cn/problem/P4314  提高+/省选−  P4314 CPU 监控  考点：区间加、区间赋值、历史最大值
 *   https://www.luogu.com.cn/problem/P10637  省选/NOI−  P10637 BZOJ4262 Sum  考点：吉司机线段树 segment tree beats、线段树
 *   https://www.luogu.com.cn/problem/P10638  省选/NOI−  P10638 BZOJ4355 Play with sequence  考点：吉司机线段树 segment tree beats、线段树
 *   https://www.luogu.com.cn/problem/P14343  省选/NOI−  P14343 [JOISC 2019] 两个天线 / Two Antennas  考点：吉司机线段树 segment tree beats、扫描线
 *   https://www.luogu.com.cn/problem/P9631  省选/NOI−  P9631 [ICPC 2020 Nanjing R] Just Another Game of Stones  考点：吉司机线段树 segment tree beats、线段树
 *   https://www.luogu.com.cn/problem/P6792  NOI/NOI+/CTS  P6792 [SNOI2020] 区间和  考点：吉司机线段树 segment tree beats、线段树、KTT / Kinetic Tournament Tree
 *   https://codeforces.com/problemset/problem/1290/E  CF3300  CF1290E Cartesian Tree  考点：笛卡尔树子树大小之和、区间取 min 与区间加
 *
 */

// 吉司机线段树：区间加、区间取 min、区间取 max，查询区间和 / 最大值 / 最小值。下标 0..n-1，区间 [l, r] 闭区间
struct SegBeats {
    static constexpr ll INF = LLONG_MAX / 4;
    int n;
    vector<ll> sum, mx1, mx2, mn1, mn2, tag;
    vector<int> cmx, cmn, len;
    SegBeats(const vector<ll> &a) : n(a.size()) {
        int sz = 4 * max(n, 1);
        sum.assign(sz, 0), mx1 = mx2 = mn1 = mn2 = tag = sum;
        cmx.assign(sz, 0), cmn = len = cmx;
        build(1, 0, n - 1, a);
    }
    void pull(int o) {
        int l = o * 2, r = o * 2 + 1;
        sum[o] = sum[l] + sum[r];
        if (mx1[l] == mx1[r]) mx1[o] = mx1[l], cmx[o] = cmx[l] + cmx[r], mx2[o] = max(mx2[l], mx2[r]);
        else if (mx1[l] > mx1[r]) mx1[o] = mx1[l], cmx[o] = cmx[l], mx2[o] = max(mx2[l], mx1[r]);
        else mx1[o] = mx1[r], cmx[o] = cmx[r], mx2[o] = max(mx1[l], mx2[r]);
        if (mn1[l] == mn1[r]) mn1[o] = mn1[l], cmn[o] = cmn[l] + cmn[r], mn2[o] = min(mn2[l], mn2[r]);
        else if (mn1[l] < mn1[r]) mn1[o] = mn1[l], cmn[o] = cmn[l], mn2[o] = min(mn2[l], mn1[r]);
        else mn1[o] = mn1[r], cmn[o] = cmn[r], mn2[o] = min(mn1[l], mn2[r]);
    }
    void build(int o, int l, int r, const vector<ll> &a) {
        len[o] = r - l + 1;
        if (l == r) {
            sum[o] = mx1[o] = mn1[o] = a[l], mx2[o] = -INF, mn2[o] = INF, cmx[o] = cmn[o] = 1;
            return;
        }
        int m = (l + r) / 2;
        build(o * 2, l, m, a), build(o * 2 + 1, m + 1, r, a);
        pull(o);
    }
    void apply_add(int o, ll v) {
        sum[o] += v * len[o], mx1[o] += v, mn1[o] += v, tag[o] += v;
        if (mx2[o] != -INF) mx2[o] += v;
        if (mn2[o] != INF) mn2[o] += v;
    }
    void apply_min(int o, ll v) {   // 要求 mx2 < v < mx1：只有最大值会变
        if (mx1[o] <= v) return;
        sum[o] -= (mx1[o] - v) * cmx[o];
        if (mn1[o] == mx1[o]) mn1[o] = v;        // 只有一种值
        else if (mn2[o] == mx1[o]) mn2[o] = v;   // 恰好两种值：最大值也是次小值
        mx1[o] = v;
    }
    void apply_max(int o, ll v) {   // 要求 mn1 < v < mn2：只有最小值会变
        if (mn1[o] >= v) return;
        sum[o] += (v - mn1[o]) * cmn[o];
        if (mx1[o] == mn1[o]) mx1[o] = v;
        else if (mx2[o] == mn1[o]) mx2[o] = v;
        mn1[o] = v;
    }
    void push(int o) {
        for (int c : {o * 2, o * 2 + 1}) {
            if (tag[o]) apply_add(c, tag[o]);
            apply_min(c, mx1[o]);   // 用父亲的最大值、最小值修剪儿子
            apply_max(c, mn1[o]);
        }
        tag[o] = 0;
    }
    void range_add(int ql, int qr, ll v, int o = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) return apply_add(o, v);
        push(o);
        int m = (l + r) / 2;
        range_add(ql, qr, v, o * 2, l, m), range_add(ql, qr, v, o * 2 + 1, m + 1, r);
        pull(o);
    }
    void range_chmin(int ql, int qr, ll v, int o = 1, int l = 0, int r = -1) {   // a_i = min(a_i, v)
        if (r == -1) r = n - 1;
        if (qr < l || r < ql || mx1[o] <= v) return;
        if (ql <= l && r <= qr && mx2[o] < v) return apply_min(o, v);
        push(o);
        int m = (l + r) / 2;
        range_chmin(ql, qr, v, o * 2, l, m), range_chmin(ql, qr, v, o * 2 + 1, m + 1, r);
        pull(o);
    }
    void range_chmax(int ql, int qr, ll v, int o = 1, int l = 0, int r = -1) {   // a_i = max(a_i, v)
        if (r == -1) r = n - 1;
        if (qr < l || r < ql || mn1[o] >= v) return;
        if (ql <= l && r <= qr && mn2[o] > v) return apply_max(o, v);
        push(o);
        int m = (l + r) / 2;
        range_chmax(ql, qr, v, o * 2, l, m), range_chmax(ql, qr, v, o * 2 + 1, m + 1, r);
        pull(o);
    }
    // op：0 求和，1 最大值，2 最小值
    ll query(int ql, int qr, int op, int o = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (qr < l || r < ql) return op == 0 ? 0 : op == 1 ? -INF : INF;
        if (ql <= l && r <= qr) return op == 0 ? sum[o] : op == 1 ? mx1[o] : mn1[o];
        push(o);
        int m = (l + r) / 2;
        ll x = query(ql, qr, op, o * 2, l, m), y = query(ql, qr, op, o * 2 + 1, m + 1, r);
        return op == 0 ? x + y : op == 1 ? max(x, y) : min(x, y);
    }
    ll query_sum(int l, int r) { return query(l, r, 0); }
    ll query_max(int l, int r) { return query(l, r, 1); }
    ll query_min(int l, int r) { return query(l, r, 2); }
};
