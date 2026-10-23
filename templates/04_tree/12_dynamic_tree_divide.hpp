/**
 * 04_tree/12 动态点分治（点分树）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：04_tree/10 点分治
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 回顾静态点分治：离线处理树上路径统计
 *   2. 点分树：点分治重心构成一棵高 O(log n) 的树
 *   3. 每个节点维护到各祖先重心的距离信息（线段树/平衡树/堆）
 *   4. 支持动态修改 + 查询最近点、距离和等
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/dynamic-tree-divide/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P6329  P6329 【模板】点分树 / 震波
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10603  省选/NOI−  P10603 BZOJ4372 烁烁的游戏  考点：动态树分治、线段树、树状数组
 *   https://www.luogu.com.cn/problem/P10604  省选/NOI−  P10604 BZOJ4317 Atm 的树  考点：动态树分治、平衡树
 *   https://www.luogu.com.cn/problem/P2056  省选/NOI−  P2056 [ZJOI2007] 捉迷藏  考点：动态树分治、线段树、点分治
 *   https://www.luogu.com.cn/problem/P3241  省选/NOI−  P3241 [HNOI2015] 开店  考点：动态树分治、点分治、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P3345  省选/NOI−  P3345 [ZJOI2015] 幻想乡战略游戏  考点：动态树分治、线段树、点分治
 *   https://www.luogu.com.cn/problem/P6845  省选/NOI−  P6845 [CEOI 2019] Dynamic Diameter  考点：动态树分治、线段树、点分治
 *
 */

// 动态点分治（点分树）：单点修改点权，查询"到 x 距离 ≤ k 的所有点的点权和"（【模板】点分树 | 震波）。
// 点分树高 O(log n)；每个分治中心 c 用两个树状数组：A_c[d] = c 的分治块内到 c 距离为 d 的点权和，
// B_c[d] = c 的分治块内到"c 在点分树上的父亲"距离为 d 的点权和（用来减掉重复统计的部分）。
// 预处理 O(n log n)，修改、查询 O(log² n)。点 0..n-1，非递归实现。
struct DynamicTreeDivide {
    int n;
    vector<vector<int>> g;
    vector<vector<pair<int, int>>> anc;   // anc[v]：v 在点分树上的祖先（从最上层到 v 自己）及距离
    vector<int> cfa, lv;                  // 点分树上的父亲、所在层数（= anc[v].size() - 1）
    vector<vector<ll>> A, B;              // 树状数组（下标从 1 开始，存距离 d 时用 d + 1）
    DynamicTreeDivide(const vector<vector<int>> &g, const vector<ll> &w) : n(g.size()), g(g), anc(n), cfa(n, -1), lv(n), A(n), B(n) {
        vector<char> removed(n, 0);
        vector<int> sz(n), par(n);
        vector<pair<int, int>> todo = {{0, -1}};   // {块内任意一点, 上一层中心}
        while (!todo.empty()) {
            auto [s, up] = todo.back();
            todo.pop_back();
            // 找重心：先 BFS 出这个块，再按逆序求子树大小
            vector<int> q = {s};
            par[s] = -1;
            for (size_t h = 0; h < q.size(); h++)
                for (int v : g[q[h]])
                    if (!removed[v] && v != par[q[h]]) par[v] = q[h], q.push_back(v);
            int tot = q.size(), c = s;
            for (int i = tot - 1; i >= 0; i--) {
                int u = q[i], mx = 0;
                sz[u] = 1;
                for (int v : g[u])
                    if (!removed[v] && v != par[u]) sz[u] += sz[v], mx = max(mx, sz[v]);
                mx = max(mx, tot - sz[u]);
                if (mx * 2 <= tot) c = u;
            }
            cfa[c] = up;
            // 从重心 BFS，记录块内每个点到 c 的距离
            vector<pair<int, int>> bq = {{c, 0}};
            par[c] = -1;
            for (size_t h = 0; h < bq.size(); h++) {
                auto [u, d] = bq[h];
                anc[u].push_back({c, d});
                for (int v : g[u])
                    if (!removed[v] && v != par[u]) par[v] = u, bq.push_back({v, d + 1});
            }
            A[c].assign(tot + 2, 0), B[c].assign(tot + 2, 0);
            removed[c] = 1;
            for (int v : g[c])
                if (!removed[v]) todo.push_back({v, c});
        }
        for (int v = 0; v < n; v++) lv[v] = anc[v].size() - 1;
        for (int v = 0; v < n; v++) modify(v, w[v]);
    }
    static void bit_add(vector<ll> &b, int i, ll x) {
        for (i++; i < (int)b.size(); i += i & -i) b[i] += x;
    }
    static ll bit_sum(const vector<ll> &b, int i) {   // 下标 0..i 的和
        ll s = 0;
        for (i = min(i + 1, (int)b.size() - 1); i > 0; i -= i & -i) s += b[i];
        return s;
    }
    // 点 x 的权值加 delta
    void modify(int x, ll delta) {
        for (int i = lv[x]; i >= 0; i--) {
            auto [c, d] = anc[x][i];
            bit_add(A[c], d, delta);
            if (i > 0) bit_add(B[c], anc[x][i - 1].second, delta);
        }
    }
    // 到 x 距离 ≤ k 的点的权值和
    ll query(int x, int k) const {
        ll res = 0;
        for (int i = lv[x]; i >= 0; i--) {
            auto [c, d] = anc[x][i];
            if (d <= k) res += bit_sum(A[c], k - d);
            if (i < lv[x]) {   // 减去从下一层中心那一块重复算过的
                int child = anc[x][i + 1].first;
                if (d <= k) res -= bit_sum(B[child], k - d);
            }
        }
        return res;
    }
};
