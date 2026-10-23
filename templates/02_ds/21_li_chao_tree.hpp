/**
 * 02_ds/21 李超线段树
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/07 线段树（含懒标记）
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 理解线段树维护"区间内所有直线在某一 x 处的最值"
 *   2. 插入直线：与当前节点直线比较，在中点处占优的留下，劣势的下放到子节点
 *   3. 查询：从根到叶子路径上所有直线在 x 处的最值
 *   4. 进阶：支持线段（有限区间）、动态开点
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/li-chao-tree/
 *   cp-algorithms  https://cp-algorithms.com/geometry/convex_hull_trick.html
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4097  P4097 【模板】李超线段树 / [HEOI2013] Segment
 *
 * 【我的笔记】
 *   适用场景：动态插入直线（或线段），查询某点 x 处所有直线的最大/最小值。
 *   核心思想：每个线段树节点保存"在该节点区间中点处最优"的直线。
 *     插入时比较新旧直线在中点的值，劣势一方下放到其可能翻盘的子区间。
 *   复杂度：插入 O(log²n)（线段退化 O(log n) 分支），查询 O(log n)。
 *   易错点：
 *     - 比较大小要带 eps（浮点）或改用斜率比较避免除法；
 *     - 下放时只需往"劣势直线可能更优"的那一侧递归；
 *     - 插入线段时要先按区间定位 O(log n) 个节点，再在各节点内做直线插入。
 *   与斜率优化的联系：斜率优化 DP 的凸壳维护可以用李超树替代，
 *     支持任意顺序插入和任意 x 查询（不要求斜率/查询单调）。
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2497  提高+/省选−  P2497 [SDOI2012] 基站建设  考点：李超线段树、动态规划 DP、线段树
 *   https://www.luogu.com.cn/problem/P3628  提高+/省选−  P3628 [APIO2010] 特别行动队  考点：李超线段树、动态规划 DP、单调队列
 *   https://www.luogu.com.cn/problem/P4254  提高+/省选−  P4254 [JSOI2008] Blue Mary 开公司  考点：李超线段树、递归
 *   https://www.luogu.com.cn/problem/P4360  提高+/省选−  P4360 [CEOI 2004] 锯木厂选址  考点：李超线段树、模拟、动态规划 DP
 *   https://www.luogu.com.cn/problem/P4655  提高+/省选−  P4655 [CEOI 2017] Building Bridges  考点：李超线段树优化 DP（斜率不单调）
 *   https://www.luogu.com.cn/problem/P5785  提高+/省选−  P5785 [SDOI2012] 任务安排  考点：斜率不单调：李超树或凸包上二分
 *   https://www.luogu.com.cn/problem/P10602  省选/NOI−  P10602 [CEOI 2009] Harbingers  考点：树上斜率优化：可撤销李超树
 *   https://www.luogu.com.cn/problem/P4027  省选/NOI−  P4027 [NOI2007] 货币兑换  考点：李超线段树、动态规划 DP、平衡树
 *   https://www.luogu.com.cn/problem/P4069  省选/NOI−  P4069 [SDOI2016] 游戏  考点：树链剖分 + 李超线段树（线段版）
 *   https://codeforces.com/problemset/problem/932/F  CF2700  CF932F Escape Through Leaf  考点：李超线段树合并优化树上 DP
 *
 */

// 李超线段树（动态开点版，求最小值）：x 的范围可以很大（如 [-1e9, 1e9]），只在用到的地方建节点。
// 插入直线 O(log V)，插入只在 [xl, xr] 上存在的线段 O(log² V)，查询某个 x 处所有线段的最小值 O(log V)。
// 求最大值时把 k、b 取相反数插入，查询结果再取相反数。数组版（求最大值）见 02_ds/12。
struct LiChaoMin {
    static constexpr ll INF = LLONG_MAX;
    struct Line {
        ll k, b;
        ll at(ll x) const { return k * x + b; }
    };
    struct Node {
        Line ln;
        int lc = 0, rc = 0;
        bool has = false;
    };
    ll lo, hi;
    vector<Node> t;
    LiChaoMin(ll lo, ll hi) : lo(lo), hi(hi), t(2) {}   // t[0] 为空节点，t[1] 为根
    int child(int p, bool right) {   // 取儿子，没有就新建（不能持有 t 的引用：push_back 会让它失效）
        int c = right ? t[p].rc : t[p].lc;
        if (!c) {
            c = t.size();
            t.push_back(Node());
            (right ? t[p].rc : t[p].lc) = c;
        }
        return c;
    }
    void insert_at(int p, ll l, ll r, Line ln) {
        while (true) {
            if (!t[p].has) {
                t[p].ln = ln, t[p].has = true;
                return;
            }
            ll m = l + (r - l) / 2;   // 区间 [l, r]，左半 [l, m]，右半 [m+1, r]
            bool bl = ln.at(l) < t[p].ln.at(l), bm = ln.at(m) < t[p].ln.at(m);
            if (bm) swap(t[p].ln, ln);   // 节点保留在中点处更优的线段
            if (l == r) return;
            if (bl != bm) p = child(p, false), r = m;   // 换下来的线段只可能在左半更优
            else p = child(p, true), l = m + 1;
        }
    }
    void insert_line(ll k, ll b) { insert_at(1, lo, hi, {k, b}); }
    // 只在 x ∈ [xl, xr] 上存在的线段
    void insert_segment(ll k, ll b, ll xl, ll xr) { insert_seg(1, lo, hi, max(xl, lo), min(xr, hi), {k, b}); }
    void insert_seg(int p, ll l, ll r, ll ql, ll qr, Line ln) {
        if (qr < l || r < ql || ql > qr) return;
        if (ql <= l && r <= qr) return insert_at(p, l, r, ln);
        ll m = l + (r - l) / 2;
        if (ql <= m) insert_seg(child(p, false), l, m, ql, qr, ln);
        if (qr > m) insert_seg(child(p, true), m + 1, r, ql, qr, ln);
    }
    ll query(ll x) const {   // 没有线段覆盖 x 时返回 INF
        ll res = INF, l = lo, r = hi;
        int p = 1;
        while (p) {
            if (t[p].has) res = min(res, t[p].ln.at(x));
            if (l == r) break;
            ll m = l + (r - l) / 2;
            if (x <= m) p = t[p].lc, r = m;
            else p = t[p].rc, l = m + 1;
        }
        return res;
    }
};
