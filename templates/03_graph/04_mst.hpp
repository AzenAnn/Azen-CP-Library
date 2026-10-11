/**
 * 03_graph/04 最小生成树
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：02_ds/04 并查集
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Kruskal
 *   2. Prim（稠密图 O(n^2)）
 *   3. 严格次小生成树
 *   4. Kruskal 重构树
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/mst/
 *   cp-algorithms  https://cp-algorithms.com/graph/mst_kruskal.html
 *   cp-algorithms  https://cp-algorithms.com/graph/mst_prim.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3366  P3366 【模板】最小生成树
 *   https://www.luogu.com.cn/problem/P4180  P4180 [BJWC2010] 严格次小生成树
 *   https://judge.yosupo.jp/problem/minimum_spanning_tree  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1194  普及  P1194 买礼物  考点：图论、生成树
 *   https://www.luogu.com.cn/problem/P1195  普及  P1195 口袋的天空  考点：图论、并查集、生成树
 *   https://www.luogu.com.cn/problem/P1991  普及  P1991 无线通讯网  考点：图论、二分、并查集
 *   https://www.luogu.com.cn/problem/P2330  普及  P2330 [SCOI2005] 繁忙的都市  考点：图论、二分、并查集
 *   https://www.luogu.com.cn/problem/P10949  普及+/提高−  P10949 四叶草魔杖  考点：生成树、状压 DP
 *   https://www.luogu.com.cn/problem/P1265  普及+/提高−  P1265 公路修建  考点：图论、生成树
 *   https://www.luogu.com.cn/problem/P4047  普及+/提高−  P4047 [JSOI2010] 部落划分  考点：二分、并查集、生成树
 *   https://www.luogu.com.cn/problem/P8074  普及+/提高−  P8074 [COCI 2009/2010 #7] SVEMIR  考点：生成树
 *   https://codeforces.com/problemset/problem/1468/J  CF1800  CF1468J Road Reform  考点：并查集、图论、贪心
 *   https://codeforces.com/problemset/problem/1095/F  CF1900  CF1095F Make It Connected  考点：并查集、图论、贪心
 *   https://codeforces.com/problemset/problem/1245/D  CF1900  CF1245D Shichikuji and Power Grid  考点：并查集、图论、贪心
 *   https://codeforces.com/problemset/problem/959/E  CF1900  CF959E Mahmoud and Ehab and the xor-MST  考点：位运算、DP、图论
 *   https://codeforces.com/problemset/problem/1857/G  CF2000  CF1857G Counting Graphs  考点：组合数学、分治、并查集
 *   https://codeforces.com/problemset/problem/1108/F  CF2100  CF1108F MST Unification  考点：二分、并查集、图论
 *   https://codeforces.com/problemset/problem/2118/D2  CF2200  CF2118D2 Red Light, Green Light (Hard version)  考点：二分、暴力、数据结构
 *
 */

// 1. Kruskal：边按权从小到大，能连通两个不同集合就选。O(m log m)
//    edges 中每条边为 {w, u, v}，点编号 0..n-1；图不连通时返回 -1
ll kruskal(int n, vector<array<ll, 3>> edges) {
    sort(edges.begin(), edges.end());
    vector<int> fa(n);
    iota(fa.begin(), fa.end(), 0);
    auto find = [&](int x) {
        while (x != fa[x]) x = fa[x] = fa[fa[x]];
        return x;
    };
    ll total = 0;
    int used = 0;
    for (auto &[w, u, v] : edges) {
        int a = find(u), b = find(v);
        if (a == b) continue;
        fa[a] = b, total += w, used++;
    }
    return used == n - 1 ? total : -1;
}

// 2. Prim（朴素 O(n^2)）：适合稠密图（如完全图，边数 n^2 时比 Kruskal 快）
//    w[i][j] 为边权，没有边时为 no_edge；图不连通时返回 -1
ll prim(const vector<vector<ll>> &w, ll no_edge = LLONG_MAX) {
    int n = w.size();
    vector<ll> d(n, no_edge);   // 每个点到当前生成树的最小边
    vector<bool> in(n, false);
    d[0] = 0;
    ll total = 0;
    for (int it = 0; it < n; it++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!in[i] && (u == -1 || d[i] < d[u])) u = i;
        if (d[u] == no_edge) return -1;
        in[u] = true, total += d[u];
        for (int v = 0; v < n; v++)
            if (!in[v] && w[u][v] < d[v]) d[v] = w[u][v];
    }
    return total;
}
