/**
 * 03_graph/18 最小树形图（朱刘算法 / Edmonds）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：03_graph/05 最小生成树
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 有向图最小生成树定义：固定根，每个非根点选一条入边，权值和最小且无环
 *   2. 朱刘算法：每点选最小入边 → 无环则结束；有环则缩点、调整入边权值、递归
 *   3. 复杂度：O(nm)，缩点最多 n 次
 *   4. 进阶：Tarjan 优化实现、不定根问题（虚拟根）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/dmst/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4716  P4716 【模板】最小树形图
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2792  省选/NOI−  P2792 [JSOI2008] 小店购物  考点：朱刘算法：先把每种商品的最低价买一件，再求最小树形图
 *   https://www.luogu.com.cn/problem/UVA11183  省选/NOI−  UVA11183 Teen Girl Squad  考点：最小树形图模板
 *   https://www.luogu.com.cn/problem/P10790  NOI/NOI+/CTS  P10790 [NOI2024] 树形图  考点：最小树形图的结构性质
 *
 */

// 最小树形图（朱刘算法）：有向图中以 root 为根、能到达所有点的边权和最小的外向生成树。O(nm)。
// 点 0..n-1，边 {u, v, w}。返回最小边权和；有点从 root 不可达时返回 -1。
// 不定根时：新建虚根向每个点连一条权值很大的边 M（M > 所有边权之和），答案减 M；
// 实际的根就是虚根那条边连到的点（记录被选中的那条虚边编号即可）。
ll directed_mst(int n, vector<array<ll, 3>> edges, int root) {
    const ll INF = LLONG_MAX / 4;
    ll res = 0;
    while (true) {
        // 1. 每个点选最小入边
        vector<ll> in(n, INF);
        vector<int> pre(n, -1);
        for (auto &[u, v, w] : edges)
            if (u != v && w < in[v]) in[v] = w, pre[v] = u;
        for (int v = 0; v < n; v++)
            if (v != root && in[v] == INF) return -1;
        // 2. 找环并缩点
        int cnt = 0;
        vector<int> id(n, -1), vis(n, -1);
        in[root] = 0;
        for (int v = 0; v < n; v++) {
            res += in[v];
            int x = v;
            while (vis[x] != v && id[x] == -1 && x != root) vis[x] = v, x = pre[x];
            if (x != root && id[x] == -1) {   // 找到一个新环
                for (int y = pre[x]; y != x; y = pre[y]) id[y] = cnt;
                id[x] = cnt++;
            }
        }
        if (cnt == 0) return res;
        for (int v = 0; v < n; v++)
            if (id[v] == -1) id[v] = cnt++;
        // 3. 重新建图：进入环的边减去环上那个点的最小入边
        for (auto &[u, v, w] : edges) {
            ll nv = v;
            w -= in[nv];
            u = id[u], v = id[nv];
        }
        n = cnt, root = id[root];
    }
}
