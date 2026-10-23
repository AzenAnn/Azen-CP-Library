/**
 * 06_dp/14 动态 DP
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：06_dp/05 树形 DP 与换根 DP、05_math/08 矩阵与矩阵快速幂
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 问题模型：DP 状态转移带修改（如带修的树上最大独立集）
 *   2. 矩阵描述转移：把 DP 转移写成 (max,+) 或 (+,×) 矩阵乘法
 *   3. 树链剖分维护矩阵乘积，修改点权 → 路径矩阵乘更新
 *   4. 广义矩阵乘法：max-plus、min-plus 半环
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/dynamic/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4719  P4719 【模板】动态 DP
 *   https://www.luogu.com.cn/problem/P4751  P4751 【模板】动态 DP（加强版）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4513  提高  P4513 小白逛公园  考点：动态 DP 前置：线段树维护最大子段和
 *   https://www.luogu.com.cn/problem/P4115  省选/NOI−  P4115 Qtree4  考点：动态 DP、动态规划 DP、点分治
 *   https://www.luogu.com.cn/problem/P4332  省选/NOI−  P4332 [SHOI2014] 三叉神经树  考点：动态 DP、线段树、平衡树
 *   https://www.luogu.com.cn/problem/P5024  省选/NOI−  P5024 [NOIP 2018 提高组] 保卫王国  考点：动态 DP、动态规划 DP、倍增
 *   https://www.luogu.com.cn/problem/P6021  省选/NOI−  P6021 洪水  考点：动态 DP、动态规划 DP、线段树
 *   https://www.luogu.com.cn/problem/P8820  省选/NOI−  P8820 [CSP-S 2022] 数据传输  考点：动态 DP、动态规划 DP、倍增
 *   https://www.luogu.com.cn/problem/P3781  NOI/NOI+/CTS  P3781 [SDOI2017] 切树游戏  考点：动态 DP、线段树、树链剖分
 *   https://www.luogu.com.cn/problem/P4426  NOI/NOI+/CTS  P4426 [HNOI/AHOI2018] 毒瘤  考点：动态 DP、并查集、枚举
 *
 */

// 动态 DP（树上最大权独立集，支持单点修改点权，【模板】动态 DP）。
// f0[u] / f1[u]：u 不选 / 选时子树的最优值。把轻儿子的贡献合并成 g0[u] = Σ_轻 max(f0, f1)，g1[u] = a[u] + Σ_轻 f0，
// 则 (f0[u], f1[u]) = M_u ⊗ (f0[重儿子], f1[重儿子])，M_u = [[g0, g0], [g1, −∞]]，⊗ 为 (max, +) 矩阵乘法。
// 树链剖分后每条重链在线段树上连续；链尾一定是叶子，整条链矩阵乘积的第 0 列就是链顶的 (f0, f1)。
// 修改：改 g1[x]，然后沿链往上跳，每到一个链顶就更新它父亲的 g。每次 O(log² n)。点 0..n-1，根为 0。
struct DynamicDP {
    static constexpr ll NEG = LLONG_MIN / 4;
    struct Mat {
        ll a[2][2];
        Mat operator*(const Mat &o) const {   // (max, +)
            Mat r;
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++) r.a[i][j] = max(a[i][0] + o.a[0][j], a[i][1] + o.a[1][j]);
            return r;
        }
    };
    int n;
    vector<vector<int>> g;
    vector<int> fa, heavy, top, pos, endp, order;   // endp[t]：链顶 t 所在链在线段树上的最后位置
    vector<ll> val, g0, g1;
    vector<Mat> t;
    DynamicDP(const vector<vector<int>> &g, const vector<ll> &a)
        : n(g.size()), g(g), fa(n, -1), heavy(n, -1), top(n), pos(n), endp(n), val(a), g0(n, 0), g1(n, 0), t(4 * max(n, 1)) {
        vector<int> sz(n, 1), q = {0};
        for (size_t h = 0; h < q.size(); h++)
            for (int v : g[q[h]])
                if (v != fa[q[h]]) fa[v] = q[h], q.push_back(v);
        for (int i = n - 1; i > 0; i--) sz[fa[q[i]]] += sz[q[i]];
        for (int u : q)
            for (int v : g[u])
                if (v != fa[u] && (heavy[u] == -1 || sz[v] > sz[heavy[u]])) heavy[u] = v;
        // 重儿子优先的 DFS 序（非递归）
        vector<int> st = {0};
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            pos[u] = order.size(), order.push_back(u);
            top[u] = (u != 0 && heavy[fa[u]] == u) ? top[fa[u]] : u;
            for (int v : g[u])
                if (v != fa[u] && v != heavy[u]) st.push_back(v);
            if (heavy[u] != -1) st.push_back(heavy[u]);
        }
        for (int u = 0; u < n; u++) endp[top[u]] = max(endp[top[u]], pos[u]);
        // 初始 DP：按 BFS 逆序算 f，同时累加轻儿子的贡献
        vector<ll> f0(n, 0), f1(n, 0);
        for (int i = n - 1; i >= 0; i--) {
            int u = q[i];
            g1[u] += val[u];
            f0[u] = g0[u], f1[u] = g1[u];
            if (heavy[u] != -1) f0[u] += max(f0[heavy[u]], f1[heavy[u]]), f1[u] += f0[heavy[u]];
            if (fa[u] != -1 && heavy[fa[u]] != u) g0[fa[u]] += max(f0[u], f1[u]), g1[fa[u]] += f0[u];
        }
        build(1, 0, n - 1);
    }
    Mat leaf(int u) const { return Mat{{{g0[u], g0[u]}, {g1[u], NEG}}}; }
    void build(int o, int l, int r) {
        if (l == r) return void(t[o] = leaf(order[l]));
        int m = (l + r) / 2;
        build(o * 2, l, m), build(o * 2 + 1, m + 1, r);
        t[o] = t[o * 2] * t[o * 2 + 1];
    }
    void update(int o, int l, int r, int p) {
        if (l == r) return void(t[o] = leaf(order[l]));
        int m = (l + r) / 2;
        if (p <= m) update(o * 2, l, m, p);
        else update(o * 2 + 1, m + 1, r, p);
        t[o] = t[o * 2] * t[o * 2 + 1];
    }
    Mat query(int o, int l, int r, int ql, int qr) const {
        if (ql <= l && r <= qr) return t[o];
        int m = (l + r) / 2;
        if (qr <= m) return query(o * 2, l, m, ql, qr);
        if (ql > m) return query(o * 2 + 1, m + 1, r, ql, qr);
        return query(o * 2, l, m, ql, qr) * query(o * 2 + 1, m + 1, r, ql, qr);
    }
    pair<ll, ll> chain_f(int tp) const {   // 链顶 tp 的 (f0, f1)：链尾是叶子，乘积的第 0 列就是答案
        Mat m = query(1, 0, n - 1, pos[tp], endp[tp]);
        return {m.a[0][0], m.a[1][0]};
    }
    // 把点 x 的权值改成 v
    void modify(int x, ll v) {
        g1[x] += v - val[x], val[x] = v;
        while (x != -1) {
            int tp = top[x];
            auto [o0, o1] = chain_f(tp);
            update(1, 0, n - 1, pos[x]);
            auto [n0, n1] = chain_f(tp);
            int p = fa[tp];
            if (p != -1) g0[p] += max(n0, n1) - max(o0, o1), g1[p] += n0 - o0;
            x = p;
        }
    }
    ll answer() const {
        auto [a, b] = chain_f(0);
        return max(a, b);
    }
};
