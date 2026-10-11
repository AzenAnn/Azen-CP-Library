/**
 * 03_graph/07 二分图
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：03_graph/01 存图与图的遍历
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 染色法判定二分图
 *   2. 匈牙利算法求最大匹配
 *   3. König 定理：最小点覆盖 = 最大匹配
 *   4. Hopcroft-Karp
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/bi-graph/
 *   OI-wiki        https://oi-wiki.org/graph/graph-matching/bigraph-match/
 *   cp-algorithms  https://cp-algorithms.com/graph/bipartite-check.html
 *   cp-algorithms  https://cp-algorithms.com/graph/kuhn_maximum_bipartite_matching.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3386  P3386 【模板】二分图最大匹配
 *   https://judge.yosupo.jp/problem/bipartitematching  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1559  提高  P1559 运动员最佳匹配问题  考点：搜索、剪枝、模拟退火
 *   https://www.luogu.com.cn/problem/P2055  提高  P2055 [ZJOI2009] 假期的宿舍  考点：网络流、图论建模、二分图
 *   https://www.luogu.com.cn/problem/P2825  提高  P2825 [HEOI2016/TJOI2016] 游戏  考点：图论、网络流、连通块
 *   https://www.luogu.com.cn/problem/P6185  提高  P6185 [NOI Online #1 提高组] 序列  考点：并查集、二分图
 *   https://codeforces.com/problemset/problem/1437/C  CF1800  CF1437C Chef Monocarp  考点：DP、网络流、图匹配
 *   https://codeforces.com/problemset/problem/1198/C  CF2000  CF1198C Matching vs  Independent Set  考点：构造、图论、贪心
 *   https://www.luogu.com.cn/problem/P1129  提高+/省选−  P1129 [ZJOI2007] 矩阵游戏  考点：递归、网络流、图论建模
 *   https://www.luogu.com.cn/problem/P3355  提高+/省选−  P3355 骑士共存问题  考点：网络流、二分图、最小割
 *   https://codeforces.com/problemset/problem/1354/E  CF2100  CF1354E Graph Coloring  考点：搜索、DP、图论
 *   https://codeforces.com/problemset/problem/1470/D  CF2200  CF1470D Strange Housing  考点：构造、搜索、图匹配
 *   https://codeforces.com/problemset/problem/1139/E  CF2400  CF1139E Maximize Mex  考点：网络流、图匹配、图论
 *   https://www.luogu.com.cn/problem/P2764  省选/NOI−  P2764 最小路径覆盖问题  考点：网络流、二分图、上下界网络流
 *   https://www.luogu.com.cn/problem/P2774  省选/NOI−  P2774 方格取数问题  考点：网络流、深度优先搜索 DFS、二分图
 *   https://codeforces.com/problemset/problem/547/D  CF2600  CF547D Mike and Fish  考点：构造、搜索、图论
 *   https://codeforces.com/problemset/problem/741/C  CF2600  CF741C Arpa’s overnight party and Mehrdad’s silent entering  考点：构造、搜索、图论
 *
 */

// 1. 染色法判定二分图：返回每个点的颜色（0 / 1）；不是二分图（有奇环）时返回空
vector<int> bipartite_color(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> color(n, -1);
    for (int s = 0; s < n; s++) {
        if (color[s] != -1) continue;
        queue<int> q;
        q.push(s), color[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (color[v] == -1) color[v] = color[u] ^ 1, q.push(v);
                else if (color[v] == color[u]) return {};
            }
        }
    }
    return color;
}

// 2. 匈牙利算法（Kuhn）：二分图最大匹配，O(n1 * m)。左部 0..n1-1，右部 0..n2-1，g[u] 为左点 u 能连的右点
//    对每个左点找增广路：若右点 v 空闲，或 v 的匹配对象能换一个右点，就把 v 给 u
struct Kuhn {
    int n1, n2, stamp = 0;
    vector<vector<int>> g;
    vector<int> ml, mr, vis;   // ml[u]：左点 u 匹配的右点；mr[v]：右点 v 匹配的左点；-1 表示未匹配
    Kuhn(int n1, int n2) : n1(n1), n2(n2), g(n1), ml(n1, -1), mr(n2, -1), vis(n2, 0) {}
    void add_edge(int u, int v) { g[u].push_back(v); }
    bool dfs(int u) {
        for (int v : g[u]) {
            if (vis[v] == stamp) continue;
            vis[v] = stamp;
            if (mr[v] == -1 || dfs(mr[v])) { ml[u] = v, mr[v] = u; return true; }
        }
        return false;
    }
    int run() {
        int res = 0;
        for (int u = 0; u < n1; u++) stamp++, res += dfs(u);
        return res;
    }
};

// 3. Hopcroft-Karp：每轮先 BFS 分层，再沿层次 DFS 找多条不相交的最短增广路，O(m√n)
struct HopcroftKarp {
    int n1, n2;
    vector<vector<int>> g;
    vector<int> ml, mr, dist, it;
    HopcroftKarp(int n1, int n2) : n1(n1), n2(n2), g(n1), ml(n1, -1), mr(n2, -1) {}
    void add_edge(int u, int v) { g[u].push_back(v); }
    bool bfs() {
        queue<int> q;
        dist.assign(n1, -1);
        for (int u = 0; u < n1; u++)
            if (ml[u] == -1) dist[u] = 0, q.push(u);
        bool found = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                int w = mr[v];
                if (w == -1) found = true;
                else if (dist[w] == -1) dist[w] = dist[u] + 1, q.push(w);
            }
        }
        return found;
    }
    bool dfs(int u) {
        for (int &i = it[u]; i < (int)g[u].size(); i++) {
            int v = g[u][i], w = mr[v];
            if (w == -1 || (dist[w] == dist[u] + 1 && dfs(w))) { ml[u] = v, mr[v] = u; return true; }
        }
        dist[u] = -1;
        return false;
    }
    int run() {
        int res = 0;
        while (bfs()) {
            it.assign(n1, 0);
            for (int u = 0; u < n1; u++)
                if (ml[u] == -1 && dfs(u)) res++;
        }
        return res;
    }
};

// 4. König 定理：二分图中 最小点覆盖 = 最大匹配；最大独立集 = 总点数 - 最大匹配。
//    构造最小点覆盖：从所有未匹配的左点出发走交错路（左→右走非匹配边，右→左走匹配边），
//    覆盖 = 没访问到的左点 + 访问到的右点。ml / mr 为任意一种最大匹配的结果
pair<vector<int>, vector<int>> min_vertex_cover(const vector<vector<int>> &g, int n2, const vector<int> &ml, const vector<int> &mr) {
    int n1 = g.size();
    vector<bool> visL(n1, false), visR(n2, false);
    queue<int> q;
    for (int u = 0; u < n1; u++)
        if (ml[u] == -1) visL[u] = true, q.push(u);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (visR[v] || ml[u] == v) continue;
            visR[v] = true;
            int w = mr[v];
            if (w != -1 && !visL[w]) visL[w] = true, q.push(w);
        }
    }
    vector<int> cl, cr;
    for (int u = 0; u < n1; u++)
        if (!visL[u]) cl.push_back(u);
    for (int v = 0; v < n2; v++)
        if (visR[v]) cr.push_back(v);
    return {cl, cr};
}
