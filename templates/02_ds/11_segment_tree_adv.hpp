/**
 * 02_ds/11 线段树进阶
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/07 线段树（含懒标记）
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 动态开点
 *   2. 权值线段树
 *   3. 线段树合并与分裂
 *   4. 李超线段树
 *   5. 扫描线（见 08_geometry/04）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/seg/
 *   OI-wiki        https://oi-wiki.org/ds/li-chao-tree/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/segment_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4556  P4556 【模板】线段树合并 / [Vani 有约会] 雨天的尾巴
 *   https://www.luogu.com.cn/problem/P5494  P5494 【模板】线段树分裂
 *   https://www.luogu.com.cn/problem/P4097  P4097 【模板】李超线段树 / [HEOI2013] Segment
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P14080  提高  P14080 [GESP202509 八级] 最小生成树  考点：线段树、倍增、并查集
 *   https://www.luogu.com.cn/problem/P1972  提高  P1972 [SDOI2009] HH 的项链  考点：线段树、树状数组、可持久化线段树
 *   https://www.luogu.com.cn/problem/P2680  提高  P2680 [NOIP 2015 提高组] 运输计划  考点：图论、二分、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P3201  提高  P3201 [HNOI2009] 梦幻布丁  考点：线段树、平衡树、枚举
 *   https://www.luogu.com.cn/problem/P3605  提高  P3605 [USACO17JAN] Promotion Counting P  考点：线段树、树状数组、树上启发式合并
 *   https://www.luogu.com.cn/problem/P1552  提高+/省选−  P1552 [APIO2012] 派遣  考点：动态规划 DP、贪心、线段树
 *   https://www.luogu.com.cn/problem/P2617  提高+/省选−  P2617 Dynamic Rankings  考点：莫队、线段树、平衡树
 *   https://www.luogu.com.cn/problem/P3224  提高+/省选−  P3224 [HNOI2012] 永无乡  考点：线段树、并查集、平衡树
 *   https://www.luogu.com.cn/problem/P3628  提高+/省选−  P3628 [APIO2010] 特别行动队  考点：动态规划 DP、单调队列、斜率优化
 *   https://www.luogu.com.cn/problem/P5787  提高+/省选−  P5787 【模板】线段树分治 / 二分图  考点：并查集、二分图、线段树分治
 *   https://www.luogu.com.cn/problem/P1600  省选/NOI−  P1600 [NOIP 2016 提高组] 天天爱跑步  考点：线段树、树上启发式合并、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P4027  省选/NOI−  P4027 [NOI2007] 货币兑换  考点：动态规划 DP、平衡树、离散化
 *   https://www.luogu.com.cn/problem/P5298  省选/NOI−  P5298 [PKUWC2018] Minimax  考点：线段树、树形 DP、概率论
 *   https://codeforces.com/problemset/problem/1140/F  CF2600  CF1140F Extending Set of Points  考点：数据结构、分治、并查集
 *   https://codeforces.com/problemset/problem/2104/G  CF2700  CF2104G Modulo 3  考点：数据结构、分治、并查集
 *
 */

// 1~3. 动态开点的权值线段树（节点池写法），值域为 [lo, hi)，可以很大（如 [-1e9, 1e9]）
//      只在用到时才新建节点，每次插入新建 O(log V) 个节点。节点 0 是空节点，表示"空树"
//      多棵树共用一个节点池，可以做线段树合并 / 分裂（洛谷 P4556、P5494）
struct DynSeg {
    struct Node {
        int l = 0, r = 0;
        ll cnt = 0;
    };
    vector<Node> t;
    ll lo, hi;
    DynSeg(ll lo, ll hi) : t(1), lo(lo), hi(hi) {}
    int new_node() { t.push_back(Node()); return t.size() - 1; }

    // 在以 root 为根的树中，值 pos 的个数加 c（root 为 0 时新建一棵树），返回根
    int add(int root, ll pos, ll c) { return add(root, lo, hi, pos, c); }
    int add(int p, ll l, ll r, ll pos, ll c) {
        if (!p) p = new_node();
        t[p].cnt += c;
        if (r - l == 1) return p;
        ll m = l + (r - l) / 2;
        if (pos < m) { int x = add(t[p].l, l, m, pos, c); t[p].l = x; }
        else { int x = add(t[p].r, m, r, pos, c); t[p].r = x; }
        return p;
    }
    // 值在 [ql, qr) 内的个数
    ll count(int root, ll ql, ll qr) const { return count(root, lo, hi, ql, qr); }
    ll count(int p, ll l, ll r, ll ql, ll qr) const {
        if (!p || qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return t[p].cnt;
        ll m = l + (r - l) / 2;
        return count(t[p].l, l, m, ql, qr) + count(t[p].r, m, r, ql, qr);
    }
    // 第 k 小的值（k 从 1 开始，要求 k <= 总个数）
    ll kth(int p, ll k) const {
        ll l = lo, r = hi;
        while (r - l > 1) {
            ll m = l + (r - l) / 2, c = t[t[p].l].cnt;
            if (k <= c) p = t[p].l, r = m;
            else k -= c, p = t[p].r, l = m;
        }
        return l;
    }
    // 线段树合并：把树 b 并入树 a，返回新根（之后 b 不能再单独使用）。所有合并的总复杂度 O(n log V)
    int merge(int a, int b) {
        if (!a || !b) return a | b;
        t[a].cnt += t[b].cnt;
        int x = merge(t[a].l, t[b].l);
        t[a].l = x;
        int y = merge(t[a].r, t[b].r);
        t[a].r = y;
        return a;
    }
    // 线段树分裂：把树 root 中值在 [ql, qr) 的部分拆出来，返回 {剩下部分的根, 拆出部分的根}
    pair<int, int> split(int root, ll ql, ll qr) { return split(root, lo, hi, ql, qr); }
    pair<int, int> split(int p, ll l, ll r, ll ql, ll qr) {
        if (!p || qr <= l || r <= ql) return {p, 0};
        if (ql <= l && r <= qr) return {0, p};
        int q = new_node();
        ll m = l + (r - l) / 2;
        auto [pl, ql2] = split(t[p].l, l, m, ql, qr);
        auto [pr, qr2] = split(t[p].r, m, r, ql, qr);
        t[p].l = pl, t[p].r = pr, t[q].l = ql2, t[q].r = qr2;
        t[p].cnt = t[pl].cnt + t[pr].cnt;
        t[q].cnt = t[ql2].cnt + t[qr2].cnt;
        return {p, q};
    }
};

// 4. 李超线段树：维护若干线段 y = kx + b，查询某个整数 x 处的最大值（洛谷 P4097）。
//    每个节点保存一条"在区间中点处最优"的线段；插入时较差的那条只可能在一侧更优，递归下去。
//    插入直线 O(log n)，插入线段 O(log^2 n)，查询 O(log n)。x 的范围为 [lo, hi)
//    求最小值：把 k、b 都取相反数，答案再取相反数
struct LiChao {
    struct Line {
        ll k, b;
        ll at(ll x) const { return k * x + b; }
    };
    ll lo;
    int n;
    vector<Line> t;
    vector<bool> has;
    LiChao(ll lo, ll hi) : lo(lo), n(hi - lo), t(4 * max(n, 1)), has(4 * max(n, 1), false) {}
    void insert_at(int p, int l, int r, Line ln) {   // 在节点 p（对应 [l, r)）上插入
        if (!has[p]) { t[p] = ln, has[p] = true; return; }
        int m = (l + r) / 2;
        bool better_l = ln.at(lo + l) > t[p].at(lo + l), better_m = ln.at(lo + m) > t[p].at(lo + m);
        if (better_m) swap(t[p], ln);   // 节点保留中点处更优的线段
        if (r - l == 1) return;
        if (better_l != better_m) insert_at(2 * p, l, m, ln);   // 被换下的线段只可能在左半更优
        else insert_at(2 * p + 1, m, r, ln);                    // 否则只可能在右半更优
    }
    void insert_line(ll k, ll b) { insert_at(1, 0, n, {k, b}); }
    // 只在 x ∈ [xl, xr) 上存在的线段
    void insert_segment(ll k, ll b, ll xl, ll xr) { insert_seg(1, 0, n, xl - lo, xr - lo, {k, b}); }
    void insert_seg(int p, int l, int r, ll ql, ll qr, Line ln) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) { insert_at(p, l, r, ln); return; }
        int m = (l + r) / 2;
        insert_seg(2 * p, l, m, ql, qr, ln), insert_seg(2 * p + 1, m, r, ql, qr, ln);
    }
    ll query(ll x) const {   // 没有任何线段覆盖 x 时返回 LLONG_MIN
        ll res = LLONG_MIN;
        int p = 1, l = 0, r = n, i = x - lo;
        while (true) {
            if (has[p]) res = max(res, t[p].at(x));
            if (r - l == 1) break;
            int m = (l + r) / 2;
            if (i < m) p = 2 * p, r = m;
            else p = 2 * p + 1, l = m;
        }
        return res;
    }
};
