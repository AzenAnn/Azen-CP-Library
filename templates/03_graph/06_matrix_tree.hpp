/**
 * 03_graph/06 矩阵树定理（生成树计数）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：03_graph/05 最小生成树、05_math/10 高斯消元
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 行列式：高斯消元化成上三角，主对角线相乘；交换两行要变号。模数不是质数时用辗转相除消元
 *   2. 无向图：拉普拉斯矩阵 L = D − A（D 为度数矩阵，重边算多次，自环忽略），删去任意一行一列后的行列式 = 生成树个数
 *   3. 有向图：外向树（根指向叶子）用入度矩阵 L = D_in − A，内向树（叶子指向根）用出度矩阵 L = D_out − A，删去根所在的行列
 *   4. 带权：把"边数"换成"边权之和"，得到所有生成树边权乘积之和；边权和之和可以用 (1 + w·x) 的一次项技巧
 *   5. 拓展：BEST 定理（有向欧拉回路计数）、最小生成树计数（按边权分组）、LGV 引理
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/matrix-tree/
 *   OI-wiki        https://oi-wiki.org/math/linear-algebra/determinant/
 *   cp-algorithms  https://cp-algorithms.com/graph/kirchhoff-theorem.html
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P6178  P6178 【模板】Matrix-Tree 定理
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2144  提高+/省选−  P2144 [FJOI2007] 轮状病毒  考点：矩阵树定理推出递推式 + 高精度
 *   https://www.luogu.com.cn/problem/P2143  省选/NOI−  P2143 [JSOI2010] 巨额奖金  考点：矩阵树定理
 *   https://www.luogu.com.cn/problem/P3790  省选/NOI−  P3790 文艺数学题  考点：矩阵树定理、枚举、剪枝
 *   https://www.luogu.com.cn/problem/P4111  省选/NOI−  P4111 [HEOI2015] 小 Z 的房间  考点：矩阵树定理、生成树、素数判断
 *   https://www.luogu.com.cn/problem/P4208  省选/NOI−  P4208 [JSOI2008] 最小生成树计数  考点：矩阵树定理、枚举、生成树
 *   https://www.luogu.com.cn/problem/P4336  省选/NOI−  P4336 [SHOI2016] 黑暗前的幻想乡  考点：矩阵树定理、生成树、容斥原理
 *   https://www.luogu.com.cn/problem/P4455  省选/NOI−  P4455 [CQOI2018] 社交网络  考点：矩阵树定理、生成树、向量
 *   https://www.luogu.com.cn/problem/P5296  NOI/NOI+/CTS  P5296 [北京省选集训2019] 生成树计数  考点：矩阵树定理、数学、多项式
 *
 */

// 1. 行列式 mod m（m 不必是质数）：两行之间做辗转相除消元，O(n^3 log m)。元素需已在 [0, m) 内
ll det_mod(vector<vector<ll>> a, ll m) {
    int n = a.size();
    ll res = 1 % m;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            while (a[j][i]) {   // 用第 i 行和第 j 行辗转相除，直到 a[j][i] = 0
                ll t = a[i][i] / a[j][i];
                for (int k = i; k < n; k++) a[i][k] = ((a[i][k] - (__int128)t * a[j][k]) % m + m) % m;
                swap(a[i], a[j]), res = (m - res) % m;
            }
        }
        if (a[i][i] == 0) return 0;
        res = (__int128)res * a[i][i] % m;
    }
    return res;
}

// 2. 生成树计数。edges 中每条边为 {u, v, w}（点编号 0..n-1，w 为边权，只计数时 w = 1）。结果对 m 取模。
//    type = 0：无向图；type = 1：有向图的外向树（以 root 为根，边从父亲指向儿子）；type = 2：有向图的内向树（边从儿子指向父亲）
//    返回所有生成树"边权乘积"之和
ll count_spanning_trees(int n, const vector<array<ll, 3>> &edges, ll m, int type = 0, int root = 0) {
    vector<vector<ll>> L(n, vector<ll>(n, 0));
    auto add = [&](int i, int j, ll w) { L[i][j] = ((L[i][j] + w) % m + m) % m; };
    for (auto [u, v, w] : edges) {
        if (u == v) continue;   // 自环不影响生成树
        w %= m;
        if (type == 0) add(u, u, w), add(v, v, w), add(u, v, -w), add(v, u, -w);
        else if (type == 1) add(v, v, w), add(u, v, -w);   // 入度
        else add(u, u, w), add(u, v, -w);                  // 出度
    }
    vector<vector<ll>> M;   // 删去 root 所在的行和列
    for (int i = 0; i < n; i++) {
        if (i == root) continue;
        vector<ll> row;
        for (int j = 0; j < n; j++)
            if (j != root) row.push_back(L[i][j]);
        M.push_back(row);
    }
    return det_mod(M, m);
}
