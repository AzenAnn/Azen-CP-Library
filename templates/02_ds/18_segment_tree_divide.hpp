/**
 * 02_ds/18 线段树分治（离线删边）
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/04 并查集、02_ds/07 线段树（含懒标记）
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 适用场景：操作可以"加入"但很难"删除"（并查集、线性基、凸包……），且可以离线
 *   2. 把每个元素的存在时间段 [l, r] 像区间修改一样挂到线段树的 O(log T) 个节点上
 *   3. DFS 线段树：进入节点时加入挂在上面的元素，离开时撤销；到叶子 t 时，结构里恰好是时刻 t 存在的元素
 *   4. 可撤销并查集：按大小合并、不路径压缩，用栈记录修改，O(log n) 查询
 *   5. 经典应用：动态图连通性、动态二分图判定（带奇偶性的并查集）、动态线性基（八纵八横）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/topic/segment-tree-offline/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5787  P5787 【模板】线段树分治 / 二分图
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4585  提高+/省选−  P4585 [FJOI2015] 火星商店问题  考点：线段树分治、线段树、分治
 *   https://www.luogu.com.cn/problem/P5227  提高+/省选−  P5227 [AHOI2013] 连通图  考点：线段树分治、并查集、动态树 LCT
 *   https://www.luogu.com.cn/problem/P3206  省选/NOI−  P3206 [HNOI2010] 城市建设  考点：线段树分治、cdq 分治、分治
 *   https://www.luogu.com.cn/problem/P3733  省选/NOI−  P3733 [HAOI2017] 八纵八横  考点：线段树分治、线段树、分治
 *   https://codeforces.com/problemset/problem/1140/F  CF2600  CF1140F Extending Set of Points  考点：按时间离线 + 可撤销并查集，维护行列二分图的点积
 *   https://www.luogu.com.cn/problem/P5416  NOI/NOI+/CTS  P5416 [CTSC2016] 时空旅行  考点：线段树分治、可持久化线段树、凸包
 *   https://codeforces.com/problemset/problem/576/E  CF3300  CF576E Painting Edges  考点：线段树分治 + 每种颜色一个带奇偶的并查集
 *
 */

// 线段树分治 + 可撤销（带奇偶性）并查集：离线回答每个时刻 0..T-1 的连通块个数、整张图是否为二分图。
// 用法：SegTreeDivide sd(n, T); sd.add_edge(u, v, l, r)（边在时刻 [l, r] 存在）；sd.solve();
//       之后 sd.comps[t]、sd.bip[t] 即为答案。总复杂度 O(m log T log n)
struct SegTreeDivide {
    int n, T;
    vector<vector<pair<int, int>>> node;   // 挂在线段树节点上的边
    vector<int> fa, sz, par;               // par[x]：x 与父亲的奇偶关系（0 同侧，1 异侧）
    vector<array<int, 3>> stk;             // 撤销栈：{被挂上去的根, 新根, 之前是否已出现奇环}
    int comp, odd;                         // 当前连通块数、出现过的奇环数（只增不减，撤销时恢复）
    vector<int> comps;
    vector<char> bip;
    SegTreeDivide(int n, int T) : n(n), T(T), node(4 * max(T, 1)), fa(n), sz(n, 1), par(n, 0) {}
    void add_edge(int u, int v, int l, int r) { insert(1, 0, T - 1, l, r, {u, v}); }
    void insert(int o, int l, int r, int ql, int qr, pair<int, int> e) {
        if (qr < l || r < ql || ql > qr) return;
        if (ql <= l && r <= qr) return node[o].push_back(e);
        int m = (l + r) / 2;
        insert(o * 2, l, m, ql, qr, e), insert(o * 2 + 1, m + 1, r, ql, qr, e);
    }
    pair<int, int> find(int x) {   // 返回 {根, x 到根的奇偶性}
        int p = 0;
        while (fa[x] != x) p ^= par[x], x = fa[x];
        return {x, p};
    }
    void link(int u, int v) {
        auto [a, pa] = find(u);
        auto [b, pb] = find(v);
        if (a == b) {
            stk.push_back({-1, -1, odd});
            if (pa == pb) odd++;   // u、v 在同一侧又连边 → 奇环
            return;
        }
        if (sz[a] > sz[b]) swap(a, b), swap(pa, pb);
        fa[a] = b, sz[b] += sz[a], par[a] = pa ^ pb ^ 1, comp--;
        stk.push_back({a, b, odd});
    }
    void undo() {
        auto [a, b, o] = stk.back();
        stk.pop_back();
        odd = o;
        if (a == -1) return;
        fa[a] = a, sz[b] -= sz[a], par[a] = 0, comp++;
    }
    void dfs(int o, int l, int r) {
        size_t old = stk.size();
        for (auto [u, v] : node[o]) link(u, v);
        if (l == r) comps[l] = comp, bip[l] = odd == 0;
        else {
            int m = (l + r) / 2;
            dfs(o * 2, l, m), dfs(o * 2 + 1, m + 1, r);
        }
        while (stk.size() > old) undo();
    }
    void solve() {
        iota(fa.begin(), fa.end(), 0);
        comp = n, odd = 0;
        comps.assign(T, 0), bip.assign(T, 0);
        if (T > 0) dfs(1, 0, T - 1);
    }
};
