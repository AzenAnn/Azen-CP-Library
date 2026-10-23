/**
 * 02_ds/23 树套树
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：02_ds/12 线段树进阶、02_ds/14 平衡树
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 问题模型：带修改的区间第 k 小（动态区间 kth）
 *   2. 树状数组套权值线段树：外层维护前缀，内层维护权值线段树（可持久化或动态开点）
 *   3. 线段树套平衡树：外层区间，内层平衡树维护有序集合
 *   4. 复杂度：修改 O(log²n)，查询 O(log²n) 或 O(log³n)
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/seg-in-bit/
 *   OI-wiki        https://oi-wiki.org/ds/balanced-in-seg/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3380  P3380 【模板】树套树
 *   https://www.luogu.com.cn/problem/P2617  P2617 Dynamic Rankings
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2464  提高+/省选−  P2464 [SDOI2008] 郁闷的小 J  考点：树套树、莫队、树状数组
 *   https://www.luogu.com.cn/problem/P3157  提高+/省选−  P3157 [CQOI2011] 动态逆序对  考点：树套树、树状数组、cdq 分治
 *   https://www.luogu.com.cn/problem/P3332  提高+/省选−  P3332 [ZJOI2013] K 大数查询  考点：树套树、线段树、整体二分
 *   https://www.luogu.com.cn/problem/P3242  省选/NOI−  P3242 [HNOI2015] 接水果  考点：树套树、深度优先搜索 DFS、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P3759  省选/NOI−  P3759 [TJOI2017] 不勤劳的图书管理员  考点：树套树、线段树、cdq 分治
 *   https://www.luogu.com.cn/problem/P4093  省选/NOI−  P4093 [HEOI2016/TJOI2016] 序列  考点：树套树、动态规划 DP、线段树
 *   https://www.luogu.com.cn/problem/P4175  省选/NOI−  P4175 [CTSC2008] 网络管理  考点：树套树、莫队、线段树
 *   https://www.luogu.com.cn/problem/P4690  省选/NOI−  P4690 [Ynoi Easy Round 2016] 镜中的昆虫  考点：树套树、树状数组、颜色段均摊（珂朵莉树 ODT）
 *   https://www.luogu.com.cn/problem/P5445  省选/NOI−  P5445 [APIO2019] 路灯  考点：树套树、线段树、cdq 分治
 *
 */

// 树套树：树状数组（外层，按位置）套动态开点权值线段树（内层，按值）。
// 支持单点修改、区间第 k 小、区间内比 v 小的个数，每次 O(log n · log V)，空间 O((n + q) log n log V)。
// 位置 0..n-1，值域 [0, V)（值很大时先离线离散化）。
struct BitSegKth {
    int n, V;
    vector<int> root, lc, rc, cnt;
    BitSegKth(int n, int V) : n(n), V(V), root(n + 1, 0), lc(1, 0), rc(1, 0), cnt(1, 0) {}
    int new_node() {
        lc.push_back(0), rc.push_back(0), cnt.push_back(0);
        return lc.size() - 1;
    }
    void seg_add(int &p, int l, int r, int x, int c) {
        if (!p) p = new_node();
        cnt[p] += c;
        if (l == r) return;
        int m = (l + r) / 2;
        if (x <= m) {
            int t = lc[p];
            seg_add(t, l, m, x, c), lc[p] = t;
        } else {
            int t = rc[p];
            seg_add(t, m + 1, r, x, c), rc[p] = t;
        }
    }
    // 在位置 pos 加入（c = 1）或删除（c = -1）一个值 x。把 a[pos] 从 u 改成 v：add(pos, u, -1), add(pos, v, 1)
    void add(int pos, int x, int c) {
        for (int i = pos + 1; i <= n; i += i & -i) {
            int t = root[i];
            seg_add(t, 0, V - 1, x, c), root[i] = t;
        }
    }
    // 收集"前缀 r 减前缀 l"对应的若干棵线段树的根
    void collect(int l, int r, vector<int> &pos, vector<int> &neg) const {
        for (int i = r; i > 0; i -= i & -i) pos.push_back(root[i]);
        for (int i = l; i > 0; i -= i & -i) neg.push_back(root[i]);
    }
    // 位置 [l, r] 内第 k 小的值（k 从 1 开始，要求 k 不超过区间元素个数）
    int kth(int l, int r, int k) const {
        vector<int> P, N;
        collect(l, r + 1, P, N);
        int lo = 0, hi = V - 1;
        while (lo < hi) {
            int m = (lo + hi) / 2, s = 0;
            for (int p : P) s += cnt[lc[p]];
            for (int p : N) s -= cnt[lc[p]];
            bool left = k <= s;
            if (!left) k -= s;
            for (int &p : P) p = left ? lc[p] : rc[p];
            for (int &p : N) p = left ? lc[p] : rc[p];
            if (left) hi = m;
            else lo = m + 1;
        }
        return lo;
    }
    // 位置 [l, r] 内严格小于 v 的个数（v 的排名 = 它 + 1）
    int count_less(int l, int r, int v) const {
        if (v <= 0) return 0;
        vector<int> P, N;
        collect(l, r + 1, P, N);
        int lo = 0, hi = V - 1, res = 0;
        while (lo < hi && v > lo) {
            int m = (lo + hi) / 2;
            if (v > m) {   // 左半 [lo, m] 全部 < v
                for (int p : P) res += cnt[lc[p]];
                for (int p : N) res -= cnt[lc[p]];
                for (int &p : P) p = rc[p];
                for (int &p : N) p = rc[p];
                lo = m + 1;
            } else {
                for (int &p : P) p = lc[p];
                for (int &p : N) p = lc[p];
                hi = m;
            }
        }
        if (lo < v && lo == hi) {   // 叶子 lo < v
            for (int p : P) res += cnt[p];
            for (int p : N) res -= cnt[p];
        }
        return res;
    }
};
