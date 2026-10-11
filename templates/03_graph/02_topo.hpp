/**
 * 03_graph/02 拓扑排序
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：03_graph/01 存图与图的遍历
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Kahn 算法（入度为 0 入队）
 *   2. 判断有向图是否有环
 *   3. DAG 上 DP
 *   4. 字典序最小的拓扑序
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/topo/
 *   cp-algorithms  https://cp-algorithms.com/graph/topological-sort.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/B3644  B3644 【模板】拓扑排序 / 家谱树
 *   https://www.luogu.com.cn/problem/P4017  P4017 最大食物链计数
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1113  普及  P1113 [USACO02FEB] 杂务  考点：动态规划 DP、图论、递推
 *   https://www.luogu.com.cn/problem/P1137  普及  P1137 旅行计划  考点：动态规划 DP、图论、递推
 *   https://www.luogu.com.cn/problem/P1807  普及  P1807 最长路  考点：动态规划 DP、图论、广度优先搜索 BFS
 *   https://www.luogu.com.cn/problem/P2196  普及  P2196 [NOIP 1996 提高组] 挖地雷  考点：动态规划 DP、搜索、深度优先搜索 DFS
 *   https://www.luogu.com.cn/problem/P2419  普及  P2419 [USACO08JAN] Cow Contest S  考点：图论、深度优先搜索 DFS、拓扑排序
 *   https://www.luogu.com.cn/problem/P2712  普及  P2712 摄像头  考点：拓扑排序
 *   https://www.luogu.com.cn/problem/P3183  普及  P3183 [HAOI2016] 食物链  考点：动态规划 DP、搜索、图论
 *   https://www.luogu.com.cn/problem/P7113  普及  P7113 [NOIP2020] 排水系统  考点：图论、高精度、拓扑排序
 *   https://www.luogu.com.cn/problem/P1038  普及+/提高−  P1038 [NOIP 2003 提高组] 神经网络  考点：图论、拓扑排序
 *   https://www.luogu.com.cn/problem/P10723  普及+/提高−  P10723 [GESP202406 七级] 黑白翻转  考点：树形 DP、拓扑排序、树的遍历
 *   https://www.luogu.com.cn/problem/P1347  普及+/提高−  P1347 [ECNA 2001] 排序  考点：图论、并查集、拓扑排序
 *   https://www.luogu.com.cn/problem/P1983  普及+/提高−  P1983 [NOIP 2013 普及组] 车站分级  考点：图论、贪心、排序
 *   https://www.luogu.com.cn/problem/P2899  普及+/提高−  P2899 [USACO08JAN] Cell Phone Network G  考点：贪心、排序、树形 DP
 *   https://www.luogu.com.cn/problem/P3243  普及+/提高−  P3243 [HNOI2015] 菜肴制作  考点：贪心、排序、拓扑排序
 *   https://www.luogu.com.cn/problem/P3627  普及+/提高−  P3627 [APIO2009] 抢掠计划  考点：记忆化搜索、拓扑排序、强连通分量
 *
 */

// 1. Kahn 算法：不断取出入度为 0 的点。返回拓扑序；若有环，返回的序列长度 < n
vector<int> topo_sort(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> indeg(n), order;
    for (int u = 0; u < n; u++)
        for (int v : g[u]) indeg[v]++;
    for (int u = 0; u < n; u++)
        if (!indeg[u]) order.push_back(u);
    for (size_t i = 0; i < order.size(); i++)   // order 本身当队列用
        for (int v : g[order[i]])
            if (--indeg[v] == 0) order.push_back(v);
    return order;
}

// 2. 判环：(int)topo_sort(g).size() < n 说明有向图有环

// 3. 字典序最小的拓扑序：把队列换成小根堆
vector<int> topo_sort_min(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> indeg(n), order;
    for (int u = 0; u < n; u++)
        for (int v : g[u]) indeg[v]++;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int u = 0; u < n; u++)
        if (!indeg[u]) pq.push(u);
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        order.push_back(u);
        for (int v : g[u])
            if (--indeg[v] == 0) pq.push(v);
    }
    return order;
}

// 4. DAG 上 DP：按拓扑序转移，保证用到 f[u] 时它已经算完。例：以每个点结尾的最长路（边数）
vector<int> dag_longest_path(const vector<vector<int>> &g) {
    vector<int> f(g.size(), 0);
    for (int u : topo_sort(g))
        for (int v : g[u]) f[v] = max(f[v], f[u] + 1);
    return f;
}
