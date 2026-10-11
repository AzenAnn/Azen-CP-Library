/**
 * 03_graph/01 存图与图的遍历
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 邻接表 / 邻接矩阵 / 边集
 *   2. DFS：连通块计数
 *   3. BFS：无权图最短路
 *   4. 网格图 BFS / DFS
 *   5. 多源 BFS
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/save/
 *   OI-wiki        https://oi-wiki.org/graph/dfs/
 *   OI-wiki        https://oi-wiki.org/graph/bfs/
 *   cp-algorithms  https://cp-algorithms.com/graph/breadth-first-search.html
 *   cp-algorithms  https://cp-algorithms.com/graph/depth-first-search.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph.go
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph_grid.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5318  P5318 【深基18.例3】查找文献
 *   https://www.luogu.com.cn/problem/P1443  P1443 马的遍历
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/1549/B  CF800  CF1549B Gregor and the Pawn Game  考点：搜索、DP、网络流
 *   https://codeforces.com/problemset/problem/115/A  CF900  CF115A Party  考点：搜索、图论、树
 *   https://codeforces.com/problemset/problem/948/A  CF900  CF948A Protect Sheep  考点：暴力、搜索、图论
 *   https://www.luogu.com.cn/problem/P1162  普及−  P1162 填涂颜色  考点：搜索、广度优先搜索 BFS、深度优先搜索 DFS
 *   https://www.luogu.com.cn/problem/P1451  普及−  P1451 求细胞数量  考点：搜索、广度优先搜索 BFS、深度优先搜索 DFS
 *   https://www.luogu.com.cn/problem/P1596  普及−  P1596 [USACO10OCT] Lake Counting S  考点：搜索、图论、广度优先搜索 BFS
 *   https://www.luogu.com.cn/problem/P4913  普及−  P4913 【深基16.例3】二叉树深度  考点：搜索、广度优先搜索 BFS、深度优先搜索 DFS
 *   https://www.luogu.com.cn/problem/P1546  普及  P1546 [USACO3.1] 最短网络 Agri-Net  考点：图论、贪心、并查集
 *   https://www.luogu.com.cn/problem/P1547  普及  P1547 [USACO05MAR] Out of Hay S  考点：图论、贪心、并查集
 *   https://www.luogu.com.cn/problem/P1821  普及  P1821 [USACO07FEB] Cow Party S  考点：图论、最短路
 *   https://codeforces.com/problemset/problem/1948/C  CF1300  CF1948C Arrow Path  考点：暴力、构造、搜索
 *   https://www.luogu.com.cn/problem/P4878  普及+/提高−  P4878 [USACO05DEC] Layout G  考点：最短路、差分约束、差分
 *   https://codeforces.com/problemset/problem/2027/C  CF1500  CF2027C Add Zeros  考点：暴力、数据结构、搜索
 *   https://codeforces.com/problemset/problem/2115/A  CF1500  CF2115A Gellyfish and Flaming Peony  考点：构造、DP、数学
 *   https://codeforces.com/problemset/problem/601/A  CF1600  CF601A The Two Routes  考点：图论、最短路
 *
 */

// 1. 存图（点编号 0..n-1）
//    无权图：vector<vector<int>> g(n);  g[u].push_back(v);  无向图再加 g[v].push_back(u);
//    带权图：vector<vector<pair<int, ll>>> g(n);  g[u].push_back({v, w});
//    只需要遍历所有边（如 Kruskal）时用边集：vector<array<ll, 3>> edges;  {w, u, v}

// 2. BFS：无权图最短路（边数），dist = -1 表示不可达。传入多个起点就是多源 BFS
vector<int> bfs(const vector<vector<int>> &g, const vector<int> &sources) {
    vector<int> dist(g.size(), -1);
    queue<int> q;
    for (int s : sources) dist[s] = 0, q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u])
            if (dist[v] == -1) dist[v] = dist[u] + 1, q.push(v);
    }
    return dist;
}

// 3. 连通块：返回 (每个点所属的连通块编号, 连通块个数)。用显式栈做 DFS，深图也不会爆栈
pair<vector<int>, int> components(const vector<vector<int>> &g) {
    int n = g.size(), cnt = 0;
    vector<int> comp(n, -1), st;
    for (int s = 0; s < n; s++) {
        if (comp[s] != -1) continue;
        comp[s] = cnt, st.push_back(s);
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int v : g[u])
                if (comp[v] == -1) comp[v] = cnt, st.push_back(v);
        }
        cnt++;
    }
    return {comp, cnt};
}

// 4. 网格图 BFS：'#' 是障碍，上下左右四个方向；返回每个格子到 (sx, sy) 的步数，不可达为 -1
//    八方向时把 DX/DY 换成 8 个方向
const int DX[4] = {-1, 1, 0, 0}, DY[4] = {0, 0, -1, 1};
vector<vector<int>> grid_bfs(const vector<string> &grid, int sx, int sy) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    dist[sx][sy] = 0, q.push({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + DX[d], ny = y + DY[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || grid[nx][ny] == '#' || dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1, q.push({nx, ny});
        }
    }
    return dist;
}
