/**
 * 03_graph/22 支配树
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：03_graph/02 拓扑排序、04_tree/02 最近公共祖先（LCA）
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 定义：从起点 s 出发，到 v 的每条路径都经过 u，则 u 支配 v；离 v 最近的支配点叫 idom(v)，连边得到支配树
 *   2. 树：idom 就是父亲；DAG：按拓扑序处理，idom(v) = v 的所有前驱在支配树上的 LCA（P2597 灾难）
 *   3. 一般有向图：Lengauer-Tarjan 算法。DFS 序 + 半支配点 sdom，带权并查集求路径上 sdom 最小的点，O(m α)
 *   4. 应用：删掉哪些点会让 v 不可达（支配树上 v 的祖先）、必经点计数、最短路图上的必经点（CF757F）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/dominator-tree/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5180  P5180 【模板】支配树
 *   https://www.luogu.com.cn/problem/P2597  P2597 [ZJOI2012] 灾难
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P17459  普及  P17459 [GESP202609 七级] 必经之路  考点：加超级源点、超级汇点，汇点在支配树上的全部祖先就是必经点
 *   https://www.luogu.com.cn/problem/P7520  省选/NOI−  P7520 [省选联考 2021 A 卷] 支配  考点：支配树上的祖先关系 + 加边后哪些点的支配集合改变
 *   https://codeforces.com/problemset/problem/757/F  CF2800  CF757F Team Rocket Rises Again  考点：最短路 DAG 上建支配树，求子树大小最大值
 *
 */

// Lengauer-Tarjan 求支配树。有向图 g（点 0..n-1），起点 s。
// 返回 idom：idom[s] = s，从 s 不可达的点为 -1。O(m log n)（并查集只做路径压缩）
vector<int> dominator_tree(const vector<vector<int>> &g, int s) {
    int n = g.size();
    vector<vector<int>> rg(n), bucket(n);
    vector<int> dfn(n, -1), ord, fa(n, -1), sdom(n), idom(n, -1), dsu(n), best(n);
    // 1. 迭代 DFS 求 DFS 序（dfn 从 0 开始），同时建反图
    for (int u = 0; u < n; u++)
        for (int v : g[u]) rg[v].push_back(u);
    {
        vector<pair<int, int>> st = {{s, 0}};
        dfn[s] = 0, ord.push_back(s);
        while (!st.empty()) {
            auto &[u, i] = st.back();
            if (i < (int)g[u].size()) {
                int v = g[u][i++];
                if (dfn[v] == -1) dfn[v] = ord.size(), ord.push_back(v), fa[v] = u, st.push_back({v, 0});
            } else st.pop_back();
        }
    }
    int k = ord.size();
    for (int i = 0; i < n; i++) sdom[i] = dsu[i] = best[i] = i;
    // 带权并查集：find(v) 返回 v 到其已处理祖先路径上 sdom 的 dfn 最小的点
    auto find = [&](int v) {
        vector<int> path;
        while (dsu[v] != dsu[dsu[v]]) path.push_back(v), v = dsu[v];
        for (int i = path.size() - 1; i >= 0; i--) {
            int x = path[i];
            if (dfn[sdom[best[dsu[x]]]] < dfn[sdom[best[x]]]) best[x] = best[dsu[x]];
            dsu[x] = dsu[dsu[x]];
        }
        return best[path.empty() ? v : path[0]];
    };
    // 2. 按 dfn 倒序求半支配点，并用 bucket 求出"临时 idom"
    for (int i = k - 1; i > 0; i--) {
        int w = ord[i];
        for (int v : rg[w]) {
            if (dfn[v] == -1) continue;   // 不可达的前驱忽略
            int u = dfn[v] < dfn[w] ? v : find(v);
            if (dfn[sdom[u]] < dfn[sdom[w]]) sdom[w] = sdom[u];
        }
        bucket[sdom[w]].push_back(w);
        dsu[w] = fa[w];
        for (int v : bucket[fa[w]]) {
            int u = find(v);
            idom[v] = sdom[u] == sdom[v] ? fa[w] : u;
        }
        bucket[fa[w]].clear();
    }
    // 3. 按 dfn 正序修正
    for (int i = 1; i < k; i++) {
        int w = ord[i];
        if (idom[w] != sdom[w]) idom[w] = idom[idom[w]];
    }
    idom[s] = s;
    return idom;
}
