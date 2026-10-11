/**
 * 02_ds/04 并查集
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 路径压缩 + 按大小合并
 *   2. 维护集合大小 / 连通块个数
 *   3. 带权并查集（到根的距离）
 *   4. 扩展域（种类）并查集
 *   5. 可撤销并查集（不路径压缩）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/dsu/
 *   cp-algorithms  https://cp-algorithms.com/data_structures/disjoint_set_union.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/union_find.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3367  P3367 【模板】并查集
 *   https://www.luogu.com.cn/problem/P1196  P1196 [NOI2002] 银河英雄传说
 *   https://www.luogu.com.cn/problem/P2024  P2024 [NOI2001] 食物链
 *   https://judge.yosupo.jp/problem/unionfind  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/1620/A  CF800  CF1620A Equal or Not Equal  考点：构造、并查集、实现
 *   https://www.luogu.com.cn/problem/P14077  普及−  P14077 [GESP202509 七级] 连通图  考点：图论、并查集、广度优先搜索 BFS
 *   https://www.luogu.com.cn/problem/P1536  普及−  P1536 村村通  考点：图论、并查集、广度优先搜索 BFS
 *   https://www.luogu.com.cn/problem/P2097  普及−  P2097 资料分发 1  考点：图论、并查集、广度优先搜索 BFS
 *   https://codeforces.com/problemset/problem/1829/E  CF1100  CF1829E The Lakes  考点：搜索、并查集、图论
 *   https://codeforces.com/problemset/problem/2008/D  CF1100  CF2008D Sakurako's Hobby  考点：DP、并查集、图论
 *   https://www.luogu.com.cn/problem/P1141  普及  P1141 01迷宫  考点：搜索、并查集、广度优先搜索 BFS
 *   https://www.luogu.com.cn/problem/P1551  普及  P1551 亲戚  考点：并查集
 *   https://www.luogu.com.cn/problem/P2661  普及  P2661 [NOIP 2015 提高组] 信息传递  考点：图论、并查集、深度优先搜索 DFS
 *   https://www.luogu.com.cn/problem/P3958  普及  P3958 [NOIP 2017 提高组] 奶酪  考点：搜索、数学、并查集
 *   https://codeforces.com/problemset/problem/755/C  CF1300  CF755C PolandBall and Forest  考点：搜索、并查集、图论
 *   https://codeforces.com/problemset/problem/1167/C  CF1400  CF1167C News Distribution  考点：搜索、并查集、图论
 *   https://www.luogu.com.cn/problem/P1955  普及+/提高−  P1955 [NOI2015] 程序自动分析  考点：并查集、离散化、哈希 hashing
 *   https://codeforces.com/problemset/problem/1791/F  CF1500  CF1791F Range Update Point Query  考点：二分、暴力、数据结构
 *   https://codeforces.com/problemset/problem/2060/E  CF1500  CF2060E Graph Composition  考点：搜索、并查集、图论
 *
 */

// 1. 并查集：路径压缩 + 按大小合并，单次操作近似 O(1)。点编号 0..n-1
struct DSU {
    vector<int> fa, sz;
    int comps;   // 连通块个数
    DSU(int n) : fa(n), sz(n, 1), comps(n) { iota(fa.begin(), fa.end(), 0); }
    int find(int x) {
        while (x != fa[x]) x = fa[x] = fa[fa[x]];   // 路径减半，非递归不会爆栈
        return x;
    }
    bool merge(int a, int b) {   // 原本就在同一集合时返回 false
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        fa[b] = a, sz[a] += sz[b], comps--;
        return true;
    }
    bool same(int a, int b) { return find(a) == find(b); }
    int size(int x) { return sz[find(x)]; }
};

// 2. 带权并查集：维护每个点的"势能" val，d[x] = val[x] - val[fa[x]]
//    用于处理"a 比 b 大 w"这类相对关系（如银河英雄传说、食物链的模 3 版本）
struct WeightedDSU {
    vector<int> fa, sz;
    vector<ll> d;
    WeightedDSU(int n) : fa(n), sz(n, 1), d(n) { iota(fa.begin(), fa.end(), 0); }
    int find(int x) {   // 按大小合并保证树高 O(log n)，递归不会爆栈
        if (fa[x] == x) return x;
        int r = find(fa[x]);
        d[x] += d[fa[x]];   // 此时 d[fa[x]] 已经是 val[fa[x]] - val[r]
        fa[x] = r;
        return r;
    }
    // 加入约束 val[a] - val[b] = w；与已有约束矛盾时返回 false
    bool merge(int a, int b, ll w) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return d[a] - d[b] == w;
        ll diff = w - d[a] + d[b];   // val[ra] - val[rb]
        if (sz[ra] > sz[rb]) swap(ra, rb), diff = -diff;
        fa[ra] = rb, d[ra] = diff, sz[rb] += sz[ra];
        return true;
    }
    ll diff(int a, int b) {   // val[a] - val[b]，要求 a、b 在同一集合
        find(a), find(b);
        return d[a] - d[b];
    }
};

// 3. 扩展域（种类）并查集：开 2n 或 3n 个点，x 表示"x 是同类"，x + n 表示"x 的敌人"，
//    "a 与 b 是敌人"就合并 (a, b + n) 和 (a + n, b)。直接用上面的 DSU 即可。

// 4. 可撤销并查集：不做路径压缩，只按大小合并，用栈记录每次合并，可以回到之前的状态
//    常用于线段树分治、离线删边
struct RollbackDSU {
    vector<int> fa, sz;
    vector<pair<int, int>> stk;   // (被挂上去的根 b, 新根 a)
    RollbackDSU(int n) : fa(n), sz(n, 1) { iota(fa.begin(), fa.end(), 0); }
    int find(int x) const {
        while (x != fa[x]) x = fa[x];
        return x;
    }
    bool merge(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        fa[b] = a, sz[a] += sz[b];
        stk.push_back({b, a});
        return true;
    }
    int snapshot() const { return stk.size(); }
    void rollback(int snap) {   // 撤销到 snapshot() 返回的时刻
        while ((int)stk.size() > snap) {
            auto [b, a] = stk.back();
            stk.pop_back();
            fa[b] = b, sz[a] -= sz[b];
        }
    }
};
