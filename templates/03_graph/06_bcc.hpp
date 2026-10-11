/**
 * 03_graph/06 割点、桥与双连通分量
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：03_graph/05 强连通分量与缩点
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 割点
 *   2. 桥
 *   3. 边双连通分量
 *   4. 点双连通分量与圆方树
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/cut/
 *   OI-wiki        https://oi-wiki.org/graph/bcc/
 *   cp-algorithms  https://cp-algorithms.com/graph/cutpoints.html
 *   cp-algorithms  https://cp-algorithms.com/graph/bridge-searching.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3388  P3388 【模板】割点（割顶）
 *   https://www.luogu.com.cn/problem/P8436  P8436 【模板】边双连通分量
 *   https://www.luogu.com.cn/problem/P8435  P8435 【模板】点双连通分量
 *   https://judge.yosupo.jp/problem/two_edge_connected_components  （Library Checker）
 *   https://judge.yosupo.jp/problem/biconnected_components  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3225  提高  P3225 [ICPC 2011 WF / HNOI2012] 矿场搭建  考点：深度优先搜索 DFS、Tarjan、双连通分量
 *   https://www.luogu.com.cn/problem/P3469  提高  P3469 [POI 2008] BLO-Blockade  考点：Tarjan、双连通分量、圆方树
 *   https://www.luogu.com.cn/problem/P4129  提高  P4129 [NEERC 2005 / SHOI2006] 仙人掌  考点：高精度、仙人掌、组合数学
 *   https://codeforces.com/problemset/problem/1927/F  CF1900  CF1927F Microcycle  考点：数据结构、搜索、并查集
 *   https://codeforces.com/problemset/problem/1986/F  CF1900  CF1986F Non-academic Problem  考点：搜索、图论、树
 *   https://codeforces.com/problemset/problem/118/E  CF2000  CF118E Bertown roads  考点：搜索、图论
 *   https://www.luogu.com.cn/problem/P4630  提高+/省选−  P4630 [APIO2018] 铁人两项  考点：双连通分量、圆方树
 *   https://codeforces.com/problemset/problem/1000/E  CF2100  CF1000E We Need More Bosses  考点：搜索、图论、树
 *   https://codeforces.com/problemset/problem/160/D  CF2300  CF160D Edges in MST  考点：搜索、并查集、图论
 *   https://codeforces.com/problemset/problem/732/F  CF2300  CF732F Tourist Reform  考点：搜索、图论
 *   https://www.luogu.com.cn/problem/P4244  省选/NOI−  P4244 [SHOI2008] 仙人掌图 II  考点：动态规划 DP、单调队列、深度优先搜索 DFS
 *   https://www.luogu.com.cn/problem/P4606  省选/NOI−  P4606 [SDOI2018] 战略游戏  考点：深度优先搜索 DFS、双连通分量、虚树
 *   https://www.luogu.com.cn/problem/P5236  省选/NOI−  P5236 【模板】静态仙人掌  考点：图论、Tarjan、双连通分量
 *   https://www.luogu.com.cn/problem/P8456  省选/NOI−  P8456 「SWTR-8」地地铁铁  考点：圆方树
 *   https://codeforces.com/problemset/problem/1325/F  CF2500  CF1325F Ehab's Last Theorem  考点：构造、搜索、图论
 *
 */

// 无向图的割点、桥、边双连通分量、点双连通分量（Tarjan，O(n + m)）
// dfn[u]：DFS 时间戳；low[u]：u 的子树经过至多一条非树边能到达的最小时间戳。
//   树边 u -> v 中，low[v] >  dfn[u]  ⇔ 这条边是桥
//                  low[v] >= dfn[u]  ⇔ u 是割点（根节点要求至少两个儿子），且 v 的子树和 u 组成一个点双
// 用边的编号判断"是不是来时的那条边"，所以重边也能正确处理。点编号 0..n-1
struct BCC {
    int n, timer = 0;
    vector<vector<pair<int, int>>> g;   // (邻点, 边编号)
    vector<pair<int, int>> edges;
    vector<int> dfn, low, stk;
    vector<bool> is_cut, is_bridge;
    vector<vector<int>> blocks;   // 点双连通分量（每个是点集）；孤立点单独成一个
    BCC(int n) : n(n), g(n) {}
    void add_edge(int u, int v) {
        g[u].push_back({v, (int)edges.size()}), g[v].push_back({u, (int)edges.size()});
        edges.push_back({u, v});
    }
    void dfs(int u, int pe) {
        dfn[u] = low[u] = ++timer;
        stk.push_back(u);
        int child = 0;
        for (auto [v, id] : g[u]) {
            if (id == pe) continue;
            if (!dfn[v]) {
                child++;
                dfs(v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) is_bridge[id] = true;
                if (low[v] >= dfn[u]) {
                    if (pe != -1 || child > 1) is_cut[u] = true;
                    vector<int> blk{u};   // 栈中 v 及其上方的点，加上 u，构成一个点双
                    while (true) {
                        int w = stk.back();
                        stk.pop_back();
                        blk.push_back(w);
                        if (w == v) break;
                    }
                    blocks.push_back(blk);
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    void run() {
        dfn.assign(n, 0), low.assign(n, 0), is_cut.assign(n, false), is_bridge.assign(edges.size(), false);
        for (int u = 0; u < n; u++) {
            if (dfn[u]) continue;
            size_t before = blocks.size();
            dfs(u, -1);
            if (blocks.size() == before) blocks.push_back({u});   // 孤立点（或只有自环）
            stk.clear();
        }
    }
    // 边双连通分量：删掉所有桥后的连通块。返回每个点所在边双的编号（需先 run）
    vector<int> two_edge_components(int &cnt) const {
        vector<int> comp(n, -1);
        cnt = 0;
        for (int s = 0; s < n; s++) {
            if (comp[s] != -1) continue;
            vector<int> st{s};
            comp[s] = cnt;
            while (!st.empty()) {
                int u = st.back();
                st.pop_back();
                for (auto [v, id] : g[u])
                    if (!is_bridge[id] && comp[v] == -1) comp[v] = cnt, st.push_back(v);
            }
            cnt++;
        }
        return comp;
    }
    // 圆方树：原图的点 0..n-1 为圆点，第 k 个点双为方点 n + k，方点与点双中的每个点连边（需先 run）
    vector<vector<int>> block_cut_tree() const {
        vector<vector<int>> t(n + blocks.size());
        for (size_t k = 0; k < blocks.size(); k++)
            for (int v : blocks[k]) t[n + k].push_back(v), t[v].push_back(n + k);
        return t;
    }
};
