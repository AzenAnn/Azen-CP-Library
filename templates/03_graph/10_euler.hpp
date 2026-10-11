/**
 * 03_graph/10 欧拉路径与欧拉回路
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：03_graph/01 存图与图的遍历
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 存在条件（有向 / 无向）
 *   2. Hierholzer 算法
 *   3. 字典序最小的欧拉路径
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/euler/
 *   cp-algorithms  https://cp-algorithms.com/graph/euler_path.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P7771  P7771 【模板】欧拉路径
 *   https://www.luogu.com.cn/problem/P2731  P2731 [USACO3.3] 骑马修栅栏 Riding the Fences
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P7796  提高  P7796 [COCI 2014/2015 #7] POLICE  考点：欧拉回路
 *   https://www.luogu.com.cn/problem/P11762  提高+/省选−  P11762 [IAMOI R1] 走亲访友  考点：图论、生成树、欧拉回路
 *   https://codeforces.com/problemset/problem/723/E  CF2200  CF723E One-Way Reform  考点：构造、搜索、网络流
 *   https://codeforces.com/problemset/problem/1038/E  CF2400  CF1038E Maximum Matching  考点：位运算、暴力、搜索
 *   https://codeforces.com/problemset/problem/1186/F  CF2400  CF1186F Vus the Cossack and a Graph  考点：搜索、图论、贪心
 *   https://codeforces.com/problemset/problem/1981/D  CF2400  CF1981D Turtle and Multiplication  考点：构造、搜索、图论
 *   https://codeforces.com/problemset/problem/209/C  CF2400  CF209C Trails and Glades  考点：构造、并查集、图论
 *   https://codeforces.com/problemset/problem/21/D  CF2400  CF21D Traveling Graph  考点：位运算、图匹配、图论
 *   https://www.luogu.com.cn/problem/P3511  省选/NOI−  P3511 [POI 2010] MOS-Bridges  考点：二分、网络流、欧拉回路
 *   https://www.luogu.com.cn/problem/P5807  省选/NOI−  P5807 【模板】BEST 定理 / Which Dreamed It  考点：矩阵树定理、线性代数、行列式
 *   https://www.luogu.com.cn/problem/P9731  省选/NOI−  P9731 [CEOI 2023] Balance  考点：欧拉回路、构造
 *   https://codeforces.com/problemset/problem/1361/C  CF2500  CF1361C Johnny and Megan's Necklace  考点：二分、位运算、构造
 *   https://codeforces.com/problemset/problem/1994/F  CF2500  CF1994F Stardew Valley  考点：构造、搜索、图论
 *   https://codeforces.com/problemset/problem/36/E  CF2600  CF36E Two Paths  考点：构造、并查集、图论
 *   https://codeforces.com/problemset/problem/527/E  CF2600  CF527E Data Center Drama  考点：搜索、图论
 *
 */

// 欧拉路径：经过每条边恰好一次的路径。Hierholzer 算法：从起点出发一直走未用过的边，
// 走不动时把当前点加入答案并回退；最后把答案反转。每次都走编号最小的邻点，得到字典序最小的路径。
// 存在条件：
//   有向图：所有点入度 = 出度（欧拉回路），或恰好一个点出度 - 入度 = 1（起点）、一个点入度 - 出度 = 1；
//   无向图：奇度点个数为 0（欧拉回路）或 2（从其中较小的出发）；
//   并且所有有边的点连通（代码中通过"路径是否用完了所有边"来检查）。
// 返回经过的点序列（长度 m + 1）；不存在或没有边时返回空。点编号 0..n-1

// 1. 有向图（洛谷 P7771）
vector<int> euler_path_directed(int n, const vector<pair<int, int>> &edges) {
    int m = edges.size();
    if (m == 0) return {};
    vector<vector<int>> adj(n);
    vector<int> deg(n, 0);   // 出度 - 入度
    for (auto [u, v] : edges) adj[u].push_back(v), deg[u]++, deg[v]--;
    int start = -1, plus = 0, minus = 0;
    for (int u = 0; u < n; u++) {
        if (deg[u] == 1) plus++, start = u;
        else if (deg[u] == -1) minus++;
        else if (deg[u] != 0) return {};
    }
    if (!(plus == 0 && minus == 0) && !(plus == 1 && minus == 1)) return {};
    if (start == -1)
        for (int u = 0; u < n; u++)
            if (!adj[u].empty()) { start = u; break; }
    for (auto &a : adj) sort(a.begin(), a.end());
    vector<int> it(n, 0), st{start}, path;
    while (!st.empty()) {   // 迭代写法，边很多时也不会爆栈
        int u = st.back();
        if (it[u] < (int)adj[u].size()) st.push_back(adj[u][it[u]++]);
        else path.push_back(u), st.pop_back();
    }
    if ((int)path.size() != m + 1) return {};   // 有边没走到：图不连通
    reverse(path.begin(), path.end());
    return path;
}

// 2. 无向图（洛谷 P2731）：用边编号标记"这条边已经走过"
vector<int> euler_path_undirected(int n, const vector<pair<int, int>> &edges) {
    int m = edges.size();
    if (m == 0) return {};
    vector<vector<pair<int, int>>> adj(n);   // (邻点, 边编号)
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        adj[u].push_back({v, i});
        if (u != v) adj[v].push_back({u, i});
        else adj[u].push_back({u, i});   // 自环使度数加 2
    }
    int start = -1, odd = 0;
    for (int u = 0; u < n; u++)
        if (adj[u].size() % 2) {
            odd++;
            if (start == -1) start = u;
        }
    if (odd != 0 && odd != 2) return {};
    if (start == -1)
        for (int u = 0; u < n; u++)
            if (!adj[u].empty()) { start = u; break; }
    for (auto &a : adj) sort(a.begin(), a.end());
    vector<bool> used(m, false);
    vector<int> it(n, 0), st{start}, path;
    while (!st.empty()) {
        int u = st.back();
        while (it[u] < (int)adj[u].size() && used[adj[u][it[u]].second]) it[u]++;
        if (it[u] < (int)adj[u].size()) {
            auto [v, id] = adj[u][it[u]++];
            used[id] = true, st.push_back(v);
        } else {
            path.push_back(u), st.pop_back();
        }
    }
    if ((int)path.size() != m + 1) return {};
    reverse(path.begin(), path.end());
    return path;
}
