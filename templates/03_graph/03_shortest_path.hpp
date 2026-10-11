/**
 * 03_graph/03 最短路
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：03_graph/01 存图与图的遍历、02_ds/03 堆与优先队列
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Dijkstra（堆优化）
 *   2. 0-1 BFS
 *   3. Bellman-Ford / SPFA 与判负环
 *   4. Floyd 与传递闭包
 *   5. 最短路计数
 *   6. 分层图最短路
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/shortest-path/
 *   cp-algorithms  https://cp-algorithms.com/graph/dijkstra.html
 *   cp-algorithms  https://cp-algorithms.com/graph/01_bfs.html
 *   cp-algorithms  https://cp-algorithms.com/graph/bellman_ford.html
 *   cp-algorithms  https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html
 *   cp-algorithms  https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4779  P4779 【模板】单源最短路径（标准版）
 *   https://www.luogu.com.cn/problem/P3385  P3385 【模板】负环
 *   https://www.luogu.com.cn/problem/B3647  B3647 【模板】Floyd
 *   https://www.luogu.com.cn/problem/P1144  P1144 最短路计数
 *   https://www.luogu.com.cn/problem/P4568  P4568 [JLOI2011] 飞行路线
 *   https://judge.yosupo.jp/problem/shortest_path  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/B3611  普及  B3611 【模板】传递闭包  考点：图论、bitset、Floyd 算法
 *   https://www.luogu.com.cn/problem/P1135  普及  P1135 奇怪的电梯  考点：模拟、广度优先搜索 BFS、深度优先搜索 DFS
 *   https://www.luogu.com.cn/problem/P1364  普及  P1364 医院设置  考点：动态规划 DP、树形数据结构、广度优先搜索 BFS
 *   https://www.luogu.com.cn/problem/P3371  普及  P3371 【模板】单源最短路径（弱化版）  考点：图论、最短路
 *   https://www.luogu.com.cn/problem/P1073  普及+/提高−  P1073 [NOIP 2009 提高组] 最优贸易  考点：动态规划 DP、搜索、图论
 *   https://www.luogu.com.cn/problem/P1119  普及+/提高−  P1119 灾后重建  考点：图论、枚举、最短路
 *   https://www.luogu.com.cn/problem/P1608  普及+/提高−  P1608 路径统计  考点：图论、最短路
 *   https://www.luogu.com.cn/problem/P3956  普及+/提高−  P3956 [NOIP 2017 普及组] 棋盘  考点：搜索、广度优先搜索 BFS、深度优先搜索 DFS
 *   https://codeforces.com/problemset/problem/295/B  CF1700  CF295B Greg and Graph  考点：DP、图论、最短路
 *   https://codeforces.com/problemset/problem/1063/B  CF1800  CF1063B Labyrinth  考点：图论、最短路
 *   https://codeforces.com/problemset/problem/1915/G  CF1800  CF1915G Bicycles  考点：图论、贪心、实现
 *   https://codeforces.com/problemset/problem/20/C  CF1900  CF20C Dijkstra?  考点：图论、最短路
 *   https://codeforces.com/problemset/problem/449/B  CF2000  CF449B Jzzhu and Cities  考点：图论、贪心、最短路
 *   https://codeforces.com/problemset/problem/545/E  CF2000  CF545E Paths and Trees  考点：图论、贪心、最短路
 *   https://codeforces.com/problemset/problem/938/D  CF2000  CF938D Buy a Ticket  考点：数据结构、图论、最短路
 *
 */

// 带权图：g[u] = {(v, w), ...}，点编号 0..n-1；不可达的距离为 DIST_INF
using WGraph = vector<vector<pair<int, ll>>>;
const ll DIST_INF = LLONG_MAX / 4;

// 1. Dijkstra（堆优化）：边权非负，O(m log m)
vector<ll> dijkstra(const WGraph &g, int s) {
    vector<ll> dist(g.size(), DIST_INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    dist[s] = 0, pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;   // 过期的堆元素，跳过
        for (auto [v, w] : g[u])
            if (d + w < dist[v]) dist[v] = d + w, pq.push({dist[v], v});
    }
    return dist;
}

// 2. 0-1 BFS：边权只有 0 和 1，用双端队列，权 0 的边放队头、权 1 的边放队尾，O(n + m)
vector<ll> bfs01(const WGraph &g, int s) {
    vector<ll> dist(g.size(), DIST_INF);
    deque<int> q;
    dist[s] = 0, q.push_back(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (auto [v, w] : g[u]) {
            if (dist[u] + w >= dist[v]) continue;
            dist[v] = dist[u] + w;
            if (w == 0) q.push_front(v);
            else q.push_back(v);
        }
    }
    return dist;
}

// 3. SPFA（队列优化的 Bellman-Ford）：允许负权边，最坏 O(nm)。
//    若从 s 出发能到达负环，返回空 vector。只判负环时，可以把所有点都作为起点（加超级源点）
vector<ll> spfa(const WGraph &g, int s) {
    int n = g.size();
    vector<ll> dist(n, DIST_INF);
    vector<int> cnt(n, 0);   // 到该点的最短路经过的边数，>= n 说明有负环
    vector<bool> inq(n, false);
    queue<int> q;
    dist[s] = 0, q.push(s), inq[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop(), inq[u] = false;
        for (auto [v, w] : g[u]) {
            if (dist[u] + w >= dist[v]) continue;
            dist[v] = dist[u] + w, cnt[v] = cnt[u] + 1;
            if (cnt[v] >= n) return {};
            if (!inq[v]) q.push(v), inq[v] = true;
        }
    }
    return dist;
}

// 4. Floyd：多源最短路，O(n^3)。d[i][j] 初始为边权（无边为 DIST_INF，d[i][i] = 0）
//    做完后 d[i][i] < 0 说明 i 在负环上。传递闭包：把 min / + 换成 |= / &
void floyd(vector<vector<ll>> &d) {
    int n = d.size();
    for (int k = 0; k < n; k++)   // k 必须在最外层
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][k] < DIST_INF && d[k][j] < DIST_INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

// 5. 最短路计数：返回 (dist, ways)，ways[v] = s 到 v 的最短路条数 mod mod（边权为正）
pair<vector<ll>, vector<ll>> dijkstra_count(const WGraph &g, int s, ll mod) {
    int n = g.size();
    vector<ll> dist(n, DIST_INF), ways(n, 0);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    dist[s] = 0, ways[s] = 1 % mod, pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (d + w < dist[v]) dist[v] = d + w, ways[v] = ways[u], pq.push({dist[v], v});
            else if (d + w == dist[v]) ways[v] = (ways[v] + ways[u]) % mod;
        }
    }
    return {dist, ways};
}

// 6. 分层图：可以免费走 k 条边时，把每个点拆成 k + 1 层，点 (u, j) 编号为 j * n + u。
//    原图的边在每一层内连一份；免费边从第 j 层连到第 j + 1 层、权为 0。然后跑 Dijkstra。
