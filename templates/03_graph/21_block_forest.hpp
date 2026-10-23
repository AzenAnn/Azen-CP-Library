/**
 * 03_graph/21 圆方树
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：03_graph/08 割点、桥与双连通分量
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 点双连通分量（v-BCC）与 Tarjan 求法
 *   2. 圆方树建树：每个点双建方点，方点与分量内所有圆点连边 → 得到一棵树/森林
 *   3. 性质：圆点间路径 ↔ 圆方树上路径，方点度数 = 点双大小
 *   4. 应用：仙人掌等价转化、必经点/路径计数、点双上 DP
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/block-forest/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4630  P4630 [APIO2018] 铁人两项
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P5058  普及+/提高−  P5058 [ZJOI2004] 嗅探器  考点：圆方树、Tarjan、双连通分量
 *   https://www.luogu.com.cn/problem/P3225  提高  P3225 [ICPC 2011 WF / HNOI2012] 矿场搭建  考点：圆方树、深度优先搜索 DFS、Tarjan
 *   https://www.luogu.com.cn/problem/P3469  提高  P3469 [POI 2008] BLO-Blockade  考点：圆方树、Tarjan、双连通分量
 *   https://www.luogu.com.cn/problem/P10779  提高+/省选−  P10779 BZOJ4316 小 C 的独立集  考点：仙人掌、动态规划 DP、Tarjan
 *   https://www.luogu.com.cn/problem/P4320  提高+/省选−  P4320 道路相遇  考点：圆方树、图论、倍增
 *   https://www.luogu.com.cn/problem/P4244  省选/NOI−  P4244 [SHOI2008] 仙人掌图 II  考点：仙人掌、动态规划 DP、单调队列
 *   https://www.luogu.com.cn/problem/P4334  省选/NOI−  P4334 [COI 2007] Policija  考点：圆方树、Tarjan
 *   https://www.luogu.com.cn/problem/P4410  省选/NOI−  P4410 [HNOI2009] 无归岛  考点：圆方树、动态规划 DP、Tarjan
 *   https://www.luogu.com.cn/problem/P4606  省选/NOI−  P4606 [SDOI2018] 战略游戏  考点：圆方树、深度优先搜索 DFS、双连通分量
 *   https://www.luogu.com.cn/problem/P8456  省选/NOI−  P8456 「SWTR-8」地地铁铁  考点：圆方树
 *
 */

// 圆方树：无向图中每个点双连通分量建一个方点，方点向分量内所有点连边（原图的点叫圆点）。
// 圆点 0..n-1，方点 n..n+cnt-1；结果是一个森林。孤立点不属于任何点双，没有方点。
// 性质：u、v 之间所有路径都必须经过的点 = 圆方树上 u→v 路径上的圆点；割点 ⇔ 度数 ≥ 2 的圆点。
// Tarjan 用显式栈实现，不会爆栈。允许重边、自环（自环忽略）。
struct BlockForest {
    int n, cnt = 0;
    vector<vector<int>> tree;
    BlockForest(int n, const vector<pair<int, int>> &edges) : n(n), tree(n) {
        vector<vector<int>> g(n);
        for (auto [u, v] : edges)
            if (u != v) g[u].push_back(v), g[v].push_back(u);
        vector<int> dfn(n, -1), low(n, 0), stk;
        int timer = 0;
        for (int r = 0; r < n; r++) {
            if (dfn[r] != -1) continue;
            vector<pair<int, int>> cs = {{r, 0}};   // {点, 下一个要看的邻边下标}
            dfn[r] = low[r] = timer++, stk.push_back(r);
            while (!cs.empty()) {
                auto [u, i] = cs.back();
                if (i < (int)g[u].size()) {
                    cs.back().second++;
                    int v = g[u][i];
                    if (dfn[v] == -1) {
                        dfn[v] = low[v] = timer++, stk.push_back(v);
                        cs.push_back({v, 0});
                    } else low[u] = min(low[u], dfn[v]);
                } else {
                    cs.pop_back();
                    if (cs.empty()) break;
                    int p = cs.back().first;
                    low[p] = min(low[p], low[u]);
                    if (low[u] >= dfn[p]) {   // p 是割点（或根）：弹出一个点双，建方点
                        int sq = n + cnt++;
                        tree.push_back({});
                        while (true) {
                            int x = stk.back();
                            stk.pop_back();
                            tree[sq].push_back(x), tree[x].push_back(sq);
                            if (x == u) break;
                        }
                        tree[sq].push_back(p), tree[p].push_back(sq);
                    }
                }
            }
            stk.clear();
        }
    }
};
