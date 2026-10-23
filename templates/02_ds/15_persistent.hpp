/**
 * 02_ds/15 可持久化数据结构
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/12 线段树进阶、02_ds/08 字典树 Trie 与 01-Trie
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 可持久化线段树（主席树）：区间第 k 小
 *   2. 可持久化数组
 *   3. 可持久化 Trie
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/persistent-seg/
 *   OI-wiki        https://oi-wiki.org/ds/persistent-trie/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/segment_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3834  P3834 【模板】可持久化线段树 2（静态区间第 k 小）
 *   https://www.luogu.com.cn/problem/P3919  P3919 【模板】可持久化线段树 1（可持久化数组）
 *   https://www.luogu.com.cn/problem/P4735  P4735 最大异或和
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3963  提高  P3963 [TJOI2013] 奖学金  考点：贪心、二分、堆
 *   https://www.luogu.com.cn/problem/P5677  提高  P5677 [GZOI2017] 配对统计  考点：线段树、树状数组、排序
 *   https://www.luogu.com.cn/problem/P7252  提高  P7252 [JSOI2011] 棒棒糖  考点：莫队、线段树、二分
 *   https://www.luogu.com.cn/problem/P8776  提高  P8776 [蓝桥杯 2022 省 A/Python B] 最长不下降子序列  考点：动态规划 DP、线段树、树状数组
 *   https://www.luogu.com.cn/problem/P8844  提高  P8844 [传智杯 #4 初赛] 小卡与落叶  考点：树状数组、树上启发式合并、可持久化线段树
 *   https://www.luogu.com.cn/problem/P2633  提高+/省选−  P2633 Count on a tree  考点：线段树、最近公共祖先 LCA、树链剖分
 *   https://www.luogu.com.cn/problem/P3402  提高+/省选−  P3402 【模板】可持久化并查集  考点：并查集、可持久化
 *   https://www.luogu.com.cn/problem/P3567  提高+/省选−  P3567 [POI 2014] KUR-Couriers  考点：莫队、线段树、二分
 *   https://www.luogu.com.cn/problem/P4137  提高+/省选−  P4137 Rmq Problem / mex  考点：莫队、线段树、树状数组
 *   https://www.luogu.com.cn/problem/P4768  提高+/省选−  P4768 [NOI2018] 归程  考点：并查集、Kruskal 重构树、最短路
 *   https://www.luogu.com.cn/problem/P2048  省选/NOI−  P2048 [NOI2010] 超级钢琴  考点：贪心、二分、堆
 *   https://www.luogu.com.cn/problem/P2414  省选/NOI−  P2414 [NOI2011] 阿狸的打字机  考点：字符串、树形数据结构、线段树
 *   https://www.luogu.com.cn/problem/P2839  省选/NOI−  P2839 [国家集训队] middle  考点：二分、可持久化线段树
 *   https://www.luogu.com.cn/problem/P4587  省选/NOI−  P4587 [FJOI2016] 神秘数  考点：莫队、树套树、可持久化线段树
 *   https://www.luogu.com.cn/problem/P5055  省选/NOI−  P5055 【模板】可持久化文艺平衡树  考点：平衡树、可持久化
 *
 */

// 可持久化：修改时不改原节点，而是复制一条从根到叶子的路径（O(log n) 个新节点），
// 旧版本的根仍然指向旧节点，于是所有历史版本都能访问。节点 0 为空节点。

// 1. 可持久化权值线段树（主席树）：静态区间第 k 小（洛谷 P3834）
//    离散化后，root[i] 为插入前 i 个数的版本；区间 [l, r) 的值分布 = root[r] - root[l]
//    用法：PersistentSeg ps(m);  root[0] = 0;  root[i + 1] = ps.insert(root[i], id(a[i]));
//          第 k 小 = vals[ps.kth(root[r], root[l], k)]
struct PersistentSeg {
    int n;   // 值域 [0, n)
    vector<int> L, R, cnt;
    PersistentSeg(int n) : n(n), L(1, 0), R(1, 0), cnt(1, 0) {}
    int insert(int prev, int pos) { return insert(prev, 0, n, pos); }
    int insert(int prev, int l, int r, int pos) {
        int p = L.size();
        L.push_back(L[prev]), R.push_back(R[prev]), cnt.push_back(cnt[prev] + 1);   // 复制旧节点
        if (r - l > 1) {
            int m = (l + r) / 2;
            if (pos < m) { int x = insert(L[prev], l, m, pos); L[p] = x; }
            else { int x = insert(R[prev], m, r, pos); R[p] = x; }
        }
        return p;
    }
    int kth(int u, int v, int k) const {   // 版本 u 减去版本 v 中第 k 小的值（k 从 1 开始）
        int l = 0, r = n;
        while (r - l > 1) {
            int m = (l + r) / 2, c = cnt[L[u]] - cnt[L[v]];
            if (k <= c) u = L[u], v = L[v], r = m;
            else k -= c, u = R[u], v = R[v], l = m;
        }
        return l;
    }
};

// 2. 可持久化数组（洛谷 P3919）：在某个历史版本上修改一个位置，或访问某个位置，都会产生新版本
struct PersistentArray {
    int n;
    vector<int> L, R, roots;
    vector<ll> val;
    PersistentArray(const vector<ll> &a) : n(a.size()), L(1, 0), R(1, 0), val(1, 0) {
        roots.push_back(build(0, n, a));
    }
    int new_node(int l, int r, ll v) {
        L.push_back(l), R.push_back(r), val.push_back(v);
        return L.size() - 1;
    }
    int build(int l, int r, const vector<ll> &a) {
        if (r - l == 1) return new_node(0, 0, a[l]);
        int m = (l + r) / 2;
        int x = build(l, m, a), y = build(m, r, a);
        return new_node(x, y, 0);
    }
    int set(int p, int l, int r, int pos, ll v) {
        if (r - l == 1) return new_node(0, 0, v);
        int m = (l + r) / 2;
        if (pos < m) { int x = set(L[p], l, m, pos, v); return new_node(x, R[p], 0); }
        int y = set(R[p], m, r, pos, v);
        return new_node(L[p], y, 0);
    }
    int update(int ver, int pos, ll v) {   // 基于版本 ver 令 a[pos] = v，返回新版本号
        roots.push_back(set(roots[ver], 0, n, pos, v));
        return roots.size() - 1;
    }
    ll get(int ver, int pos) const {
        int p = roots[ver], l = 0, r = n;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (pos < m) p = L[p], r = m;
            else p = R[p], l = m;
        }
        return val[p];
    }
    int copy_version(int ver) { roots.push_back(roots[ver]); return roots.size() - 1; }
};

// 3. 可持久化 01-Trie：x 与 a[l, r) 中某个数异或的最大值（洛谷 P4735）
//    roots[i] 为插入前 i 个数的版本，cnt 相减就得到区间内经过某节点的数的个数
struct PersistentTrie {
    static const int B = 30;   // 数值范围 [0, 2^30)
    vector<array<int, 2>> ch;
    vector<int> cnt, roots;
    PersistentTrie() : ch(1, {0, 0}), cnt(1, 0), roots(1, 0) {}
    int copy_node(int q) {
        array<int, 2> c = ch[q];
        int k = cnt[q];
        ch.push_back(c), cnt.push_back(k + 1);
        return ch.size() - 1;
    }
    void push(int x) {   // 在末尾追加一个数，产生新版本
        int prev = roots.back(), p = copy_node(prev);
        roots.push_back(p);
        for (int b = B - 1; b >= 0; b--) {
            int c = x >> b & 1, q = copy_node(ch[prev][c]);
            ch[p][c] = q;
            p = q, prev = ch[prev][c];
        }
    }
    int max_xor(int l, int r, int x) const {   // 要求 l < r
        int u = roots[r], v = roots[l], res = 0;
        for (int b = B - 1; b >= 0; b--) {
            int c = x >> b & 1;
            if (cnt[ch[u][c ^ 1]] - cnt[ch[v][c ^ 1]] > 0) res |= 1 << b, u = ch[u][c ^ 1], v = ch[v][c ^ 1];
            else u = ch[u][c], v = ch[v][c];
        }
        return res;
    }
};
