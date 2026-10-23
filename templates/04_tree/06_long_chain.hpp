/**
 * 04_tree/06 长链剖分
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：04_tree/05 树链剖分、01_basic/09 倍增
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 长儿子：子树高度最大的儿子；按长儿子剖分，所有长链长度之和为 n
 *   2. 性质：任意点 u 的 k 级祖先所在的长链长度 ≥ k；从 u 跳到根最多经过 O(√n) 条长链
 *   3. O(n log n) 预处理、O(1) 查询树上 k 级祖先：倍增先跳最高位，再用链顶的 up / down 数组
 *   4. 优化"以深度为下标"的树形 DP：长儿子直接继承（指针偏移一位），短儿子暴力合并，总复杂度 O(n)
 *   5. 经典题：Dominant Indices（每个子树哪一层点最多）、HOT-Hotels（三点两两等距）、重建计划（+ 分数规划）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/hld/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5903  P5903 【模板】树上 K 级祖先
 *   https://codeforces.com/problemset/problem/1009/F  CF1009F Dominant Indices
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3565  提高+/省选−  P3565 [POI 2014] HOT-Hotels  考点：长链剖分优化深度 DP
 *   https://www.luogu.com.cn/problem/P3899  提高+/省选−  P3899 [湖南集训] 更为厉害  考点：树链剖分、线段树、树状数组
 *   https://codeforces.com/problemset/problem/208/E  CF2100  CF208E Blood Cousins  考点：k 级祖先 + 按深度统计，长链剖分或 dsu on tree
 *   https://www.luogu.com.cn/problem/P4292  省选/NOI−  P4292 [WC2010] 重建计划  考点：分数规划 + 长链剖分 / 点分治
 *   https://www.luogu.com.cn/problem/P5904  省选/NOI−  P5904 [POI 2014] HOT-Hotels 加强版  考点：长链剖分优化深度 DP（O(n)）
 *   https://codeforces.com/problemset/problem/526/G  CF3300  CF526G Spiders Evil Plan  考点：长链剖分思想：贪心选前 2k 条最长链
 *
 */

// 长链剖分。树 g（点 0..n-1，无向邻接表），根 root。全部用非递归实现，链状大树也不会爆栈。
// len[u]：u 子树内从 u 往下最长链的点数；son[u]：长儿子（-1 表示叶子）；top[u]：所在长链的链顶；
// pos[u]：长儿子优先的 DFS 序（同一条长链上的点编号连续），长链 DP 用它分配内存。
struct LongChain {
    int n, root, LOG;
    vector<int> fa, dep, len, son, top, pos, pre;   // pre：按 pos 排列的点
    vector<vector<int>> anc;                         // anc[j][u]：u 的 2^j 级祖先（不存在为 -1）
    vector<vector<int>> up, down;                    // 链顶 t：up[t][i] 为 t 的 i 级祖先，down[t][i] 为链上往下第 i 个点
    vector<int> hb;                                  // hb[k]：k 的最高二进制位
    vector<vector<int>> ch;                          // 儿子列表
    LongChain(const vector<vector<int>> &g, int root = 0)
        : n(g.size()), root(root), LOG(__lg(max(n, 1)) + 1), fa(n, -1), dep(n, 0), len(n, 1), son(n, -1), top(n), pos(n), hb(n + 1, 0), ch(n) {
        vector<int> bfs = {root};
        for (size_t h = 0; h < bfs.size(); h++)
            for (int v : g[bfs[h]])
                if (v != fa[bfs[h]]) fa[v] = bfs[h], dep[v] = dep[bfs[h]] + 1, ch[bfs[h]].push_back(v), bfs.push_back(v);
        for (int i = n - 1; i > 0; i--) {
            int u = bfs[i], p = fa[u];
            if (len[u] + 1 > len[p]) len[p] = len[u] + 1, son[p] = u;
        }
        // 长儿子优先的 DFS 序
        vector<int> st = {root};
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            pos[u] = pre.size(), pre.push_back(u);
            top[u] = (u != root && son[fa[u]] == u) ? top[fa[u]] : u;
            for (int v : g[u])
                if (v != fa[u] && v != son[u]) st.push_back(v);
            if (son[u] != -1) st.push_back(son[u]);   // 最后压栈 → 最先访问
        }
        anc.assign(LOG, vector<int>(n, -1));
        anc[0] = fa;
        for (int j = 1; j < LOG; j++)
            for (int u = 0; u < n; u++) anc[j][u] = anc[j - 1][u] < 0 ? -1 : anc[j - 1][anc[j - 1][u]];
        for (int k = 2; k <= n; k++) hb[k] = hb[k / 2] + 1;
        up.assign(n, {}), down.assign(n, {});
        for (int t = 0; t < n; t++) {
            if (top[t] != t) continue;
            for (int i = 0, u = t; i < len[t] && u != -1; i++, u = fa[u]) up[t].push_back(u);
            for (int i = 0, u = t; i < len[t]; i++, u = son[u]) down[t].push_back(u);
        }
    }
    // 1. u 的 k 级祖先，O(1)（不存在返回 -1）
    int kth_ancestor(int u, int k) const {
        if (k == 0) return u;
        if (k > dep[u]) return -1;
        int j = hb[k];
        u = anc[j][u], k -= 1 << j;   // 跳完后 u 所在长链长度 ≥ 2^j > 剩余的 k
        int t = top[u], d = dep[u] - dep[t];
        return k >= d ? up[t][k - d] : down[t][d - k];
    }
    // 2. 长链优化 DP 的例子（CF1009F）：f[u][i] = u 子树中深度为 dep[u] + i 的点数，
    //    返回每个 u 使 f[u][i] 最大的最小 i。f[u] 存放在 buf[pos[u] ..]，长儿子与父亲共用（错开一位）
    vector<int> dominant_index() const {
        vector<int> buf(n, 0), ans(n, 0);
        for (int i = n - 1; i >= 0; i--) {   // pos 倒序：儿子都先于父亲完成
            int u = pre[i];
            int *f = buf.data() + pos[u];
            f[0] = 1;
            if (son[u] != -1) {   // 长儿子的数组就是 f + 1，直接继承答案
                ans[u] = ans[son[u]] + 1;
                if (f[ans[u]] <= 1) ans[u] = 0;
            }
            for (int v : ch[u]) {   // 短儿子：逐层暴力合并，代价为短儿子的链长，总和 O(n)
                if (v == son[u]) continue;
                const int *h = buf.data() + pos[v];
                for (int d = 0; d < len[v]; d++) {
                    f[d + 1] += h[d];
                    if (f[d + 1] > f[ans[u]] || (f[d + 1] == f[ans[u]] && d + 1 < ans[u])) ans[u] = d + 1;
                }
            }
        }
        return ans;
    }
};
