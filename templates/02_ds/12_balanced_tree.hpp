/**
 * 02_ds/12 平衡树
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/07 线段树（含懒标记）
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. pb_ds 的 tree（求排名 / 第 k 小）
 *   2. multiset 的常用技巧
 *   3. FHQ Treap：按值分裂、按排名分裂
 *   4. 文艺平衡树：区间翻转
 *   5. Splay
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/treap/
 *   OI-wiki        https://oi-wiki.org/lang/pb-ds/tree/
 *   cp-algorithms  https://cp-algorithms.com/data_structures/treap.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/treap.go
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/splay.go
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/orderedset.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3369  P3369 【模板】普通平衡树
 *   https://www.luogu.com.cn/problem/P6136  P6136 【模板】普通平衡树（数据加强版）
 *   https://www.luogu.com.cn/problem/P3391  P3391 【模板】文艺平衡树
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1486  提高  P1486 [NOI2004] 郁闷的出纳员  考点：线段树、二分、平衡树
 *   https://www.luogu.com.cn/problem/P3466  提高  P3466 [POI 2008] KLO-Building blocks  考点：贪心、线段树、平衡树
 *   https://www.luogu.com.cn/problem/P3850  提高  P3850 [TJOI2007] 书架  考点：平衡树、枚举
 *   https://www.luogu.com.cn/problem/P4879  提高  P4879 ycz的妹子  考点：线段树、二分、平衡树
 *   https://www.luogu.com.cn/problem/P5482  提高  P5482 [JLOI2011] 不等式组  考点：平衡树、树状数组
 *   https://www.luogu.com.cn/problem/P2486  提高+/省选−  P2486 [SDOI2011] 染色  考点：线段树、平衡树、颜色段均摊（珂朵莉树 ODT）
 *   https://www.luogu.com.cn/problem/P2596  提高+/省选−  P2596 [ZJOI2006] 书架  考点：平衡树
 *   https://www.luogu.com.cn/problem/P3380  提高+/省选−  P3380 【模板】树套树  考点：线段树、平衡树、树状数组
 *   https://www.luogu.com.cn/problem/P4008  提高+/省选−  P4008 [NOI2003] 文本编辑器  考点：字符串、平衡树、递归
 *   https://codeforces.com/problemset/problem/85/D  CF2300  CF85D Sum of Medians  考点：二分、暴力、数据结构
 *   https://www.luogu.com.cn/problem/P2042  省选/NOI−  P2042 [NOI2005] 维护数列  考点：平衡树
 *   https://www.luogu.com.cn/problem/P3835  省选/NOI−  P3835 【模板】可持久化平衡树  考点：线段树、平衡树、深度优先搜索 DFS
 *   https://www.luogu.com.cn/problem/P3960  省选/NOI−  P3960 [NOIP 2017 提高组] 列队  考点：线段树、二分、平衡树
 *   https://codeforces.com/problemset/problem/609/F  CF2500  CF609F Frogs and mosquitoes  考点：数据结构、贪心
 *   https://codeforces.com/problemset/problem/455/D  CF2700  CF455D Serega and Fun  考点：数据结构
 *
 */

// 1. pb_ds 的平衡树：比赛中最省事的写法（GCC 才有）
//    order_of_key(x)：严格小于 x 的元素个数；find_by_order(k)：第 k 小（从 0 开始）的迭代器
//    它是 set，不能存重复元素。需要可重复时存 pair<值, 唯一编号>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <class T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
                                     __gnu_pbds::tree_order_statistics_node_update>;

// 2. multiset 的常用技巧：
//    删除一个 x（而不是全部）：ms.erase(ms.find(x));
//    前驱：*prev(ms.lower_bound(x))（需判断 lower_bound 不是 begin）；后继：*ms.upper_bound(x)
//    multiset 不能 O(log n) 求排名，需要排名时用 FHQ Treap 或 pb_ds

// 3. FHQ Treap（无旋 Treap）：按值维护一个可重集合（洛谷 P3369 普通平衡树）
//    核心只有 split 和 merge 两个操作，其余操作都由它们拼出来。节点 0 为空节点
struct FHQTreap {
    vector<int> l, r, sz;
    vector<ll> key;
    vector<unsigned> pri;
    int root = 0;
    mt19937 rng{20240601};
    FHQTreap() : l(1), r(1), sz(1), key(1), pri(1) {}
    int new_node(ll k) {
        l.push_back(0), r.push_back(0), sz.push_back(1), key.push_back(k), pri.push_back(rng());
        return key.size() - 1;
    }
    void pull(int p) { sz[p] = sz[l[p]] + sz[r[p]] + 1; }
    // 按值分裂：a 中的值都 <= k，b 中的值都 > k
    void split(int p, ll k, int &a, int &b) {
        if (!p) { a = b = 0; return; }
        if (key[p] <= k) a = p, split(r[p], k, r[p], b);
        else b = p, split(l[p], k, a, l[p]);
        pull(p);
    }
    // 合并：要求 a 中的值都 <= b 中的值；按优先级决定谁当根
    int merge(int a, int b) {
        if (!a || !b) return a | b;
        if (pri[a] > pri[b]) { r[a] = merge(r[a], b); pull(a); return a; }
        l[b] = merge(a, l[b]);
        pull(b);
        return b;
    }
    void insert(ll k) {
        int a, b;
        split(root, k, a, b);
        int x = new_node(k);
        root = merge(merge(a, x), b);
    }
    void erase(ll k) {   // 删除一个 k（不存在则什么也不做）
        int a, b, c;
        split(root, k, a, c);
        split(a, k - 1, a, b);   // b 中都是 k
        b = merge(l[b], r[b]);   // 去掉 b 的根，就删掉了一个
        root = merge(merge(a, b), c);
    }
    int rank(ll k) {   // 小于 k 的个数 + 1
        int a, b;
        split(root, k - 1, a, b);
        int res = sz[a] + 1;
        root = merge(a, b);
        return res;
    }
    ll kth(int k) const {   // 第 k 小（k 从 1 开始）
        int p = root;
        while (true) {
            if (k <= sz[l[p]]) p = l[p];
            else if (k == sz[l[p]] + 1) return key[p];
            else k -= sz[l[p]] + 1, p = r[p];
        }
    }
    ll prev(ll k) {   // 小于 k 的最大值（要求存在）
        int a, b;
        split(root, k - 1, a, b);
        int p = a;
        while (r[p]) p = r[p];
        root = merge(a, b);
        return key[p];
    }
    ll next(ll k) {   // 大于 k 的最小值（要求存在）
        int a, b;
        split(root, k, a, b);
        int p = b;
        while (l[p]) p = l[p];
        root = merge(a, b);
        return key[p];
    }
    int size() const { return sz[root]; }
};

// 4. 文艺平衡树：按"位置"分裂的 Treap，支持区间翻转（洛谷 P3391）
//    split(p, k) 把前 k 个元素分到 a；翻转用懒标记，访问儿子前先下传
struct ImplicitTreap {
    vector<int> l, r, sz;
    vector<ll> val;
    vector<unsigned> pri;
    vector<char> rev;
    int root = 0;
    mt19937 rng{20240602};
    ImplicitTreap() : l(1), r(1), sz(1), val(1), pri(1), rev(1) {}
    int new_node(ll v) {
        l.push_back(0), r.push_back(0), sz.push_back(1), val.push_back(v), pri.push_back(rng()), rev.push_back(0);
        return val.size() - 1;
    }
    void pull(int p) { sz[p] = sz[l[p]] + sz[r[p]] + 1; }
    void push(int p) {
        if (!rev[p]) return;
        swap(l[p], r[p]);
        if (l[p]) rev[l[p]] ^= 1;
        if (r[p]) rev[r[p]] ^= 1;
        rev[p] = 0;
    }
    void split(int p, int k, int &a, int &b) {
        if (!p) { a = b = 0; return; }
        push(p);
        if (sz[l[p]] < k) a = p, split(r[p], k - sz[l[p]] - 1, r[p], b);
        else b = p, split(l[p], k, a, l[p]);
        pull(p);
    }
    int merge(int a, int b) {
        if (!a || !b) return a | b;
        if (pri[a] > pri[b]) { push(a); r[a] = merge(r[a], b); pull(a); return a; }
        push(b);
        l[b] = merge(a, l[b]);
        pull(b);
        return b;
    }
    void push_back(ll v) { int x = new_node(v); root = merge(root, x); }
    void reverse(int lo, int hi) {   // 翻转第 [lo, hi) 个元素（从 0 开始）
        int a, b, c;
        split(root, lo, a, b);
        split(b, hi - lo, b, c);
        if (b) rev[b] ^= 1;
        root = merge(merge(a, b), c);
    }
    vector<ll> to_vector() {   // 中序遍历得到当前序列
        vector<ll> res;
        vector<int> st;
        int p = root;
        while (p || !st.empty()) {
            while (p) push(p), st.push_back(p), p = l[p];
            p = st.back(), st.pop_back();
            res.push_back(val[p]);
            p = r[p];
        }
        return res;
    }
};

// 5. Splay：每次访问后把节点旋转到根，均摊 O(log n)。功能同 FHQ Treap（按值的可重集合）。
//    Splay 是 LCT（02_ds/17）的基础。cnt[x] 为值 key[x] 的个数，节点 0 为空节点
struct Splay {
    vector<array<int, 2>> ch;
    vector<int> fa, cnt, sz;
    vector<ll> key;
    int root = 0;
    Splay() : ch(1, {0, 0}), fa(1, 0), cnt(1, 0), sz(1, 0), key(1, 0) {}
    int new_node(ll k, int f) {
        ch.push_back({0, 0}), fa.push_back(f), cnt.push_back(1), sz.push_back(1), key.push_back(k);
        return key.size() - 1;
    }
    void pull(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x]; }
    int dir(int x) const { return ch[fa[x]][1] == x; }
    void rotate(int x) {
        int y = fa[x], z = fa[y], k = dir(x);
        if (z) ch[z][dir(y)] = x;
        fa[x] = z;
        ch[y][k] = ch[x][k ^ 1];
        if (ch[x][k ^ 1]) fa[ch[x][k ^ 1]] = y;
        ch[x][k ^ 1] = y, fa[y] = x;
        pull(y), pull(x);
    }
    void splay(int x) {   // 把 x 旋到根：同向时先转父亲（双旋），保证均摊复杂度
        while (fa[x]) {
            int y = fa[x];
            if (fa[y]) rotate(dir(x) == dir(y) ? y : x);
            rotate(x);
        }
        root = x;
    }
    void insert(ll k) {
        int x = root, f = 0;
        while (x && key[x] != k) f = x, x = ch[x][k > key[x]];
        if (x) cnt[x]++, pull(x);
        else {
            x = new_node(k, f);
            if (f) ch[f][k > key[f]] = x;
        }
        splay(x);
    }
    void find(ll k) {   // 把值为 k 的节点（不存在时为它的前驱或后继）旋到根
        int x = root;
        if (!x) return;
        while (key[x] != k && ch[x][k > key[x]]) x = ch[x][k > key[x]];
        splay(x);
    }
    int rank(ll k) {   // 小于 k 的个数 + 1
        if (!root) return 1;
        find(k);
        return sz[ch[root][0]] + (key[root] < k ? cnt[root] : 0) + 1;
    }
    ll kth(int k) {   // 第 k 小（k 从 1 开始）
        int x = root;
        while (true) {
            if (k <= sz[ch[x][0]]) x = ch[x][0];
            else if (k <= sz[ch[x][0]] + cnt[x]) break;
            else k -= sz[ch[x][0]] + cnt[x], x = ch[x][1];
        }
        splay(x);
        return key[x];
    }
    int prev_node(ll k) {   // 小于 k 的最大值所在的节点（不存在返回 0）
        find(k);
        int x = root;
        if (key[x] < k) return x;
        x = ch[x][0];
        if (!x) return 0;
        while (ch[x][1]) x = ch[x][1];
        splay(x);
        return x;
    }
    int next_node(ll k) {   // 大于 k 的最小值所在的节点（不存在返回 0）
        find(k);
        int x = root;
        if (key[x] > k) return x;
        x = ch[x][1];
        if (!x) return 0;
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
    }
    ll prev(ll k) { return key[prev_node(k)]; }   // 要求存在
    ll next(ll k) { return key[next_node(k)]; }
    void erase(ll k) {   // 删除一个 k（不存在则什么也不做）
        find(k);
        int x = root;
        if (!x || key[x] != k) return;
        if (cnt[x] > 1) { cnt[x]--, pull(x); return; }
        int L = ch[x][0], R = ch[x][1];
        if (!L || !R) {
            root = L | R;
            if (root) fa[root] = 0;
            return;
        }
        fa[L] = 0;   // 把左子树中的最大值旋到左子树的根，再接上右子树
        int y = L;
        while (ch[y][1]) y = ch[y][1];
        splay(y);
        ch[y][1] = R, fa[R] = y;
        pull(y);
    }
    int size() const { return sz[root]; }
};
