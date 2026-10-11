/**
 * 04_tree/06 树哈希与树同构
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：04_tree/01 树的基础：直径、重心、DFS 序
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 有根树哈希
 *   2. 无根树：以重心为根
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/tree-hash/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5043  P5043 【模板】树同构 / [BJOI2015] 树的同构
 *   https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P11618  提高  P11618 [PumpkinOI Round 1] 造树据  考点：树形 DP、哈希 hashing
 *   https://www.luogu.com.cn/problem/P6204  提高  P6204 [USACO07CHN] Treasure G  考点：哈希 hashing、基环树
 *   https://www.luogu.com.cn/problem/P3237  提高+/省选−  P3237 [HNOI2014] 米特运输  考点：数学、树形 DP、哈希 hashing
 *   https://www.luogu.com.cn/problem/P4323  提高+/省选−  P4323 [JSOI2016] 独特的树叶  考点：深度优先搜索 DFS、哈希 hashing
 *   https://codeforces.com/problemset/problem/1800/G  CF2200  CF1800G Symmetree  考点：搜索、哈希、实现
 *   https://codeforces.com/problemset/problem/1252/F  CF2400  CF1252F Regular Forestation  考点：哈希、树
 *   https://www.luogu.com.cn/problem/P11360  省选/NOI−  P11360 [CEOI 2015] 管道  考点：图论、并查集、树上启发式合并
 *   https://www.luogu.com.cn/problem/P13266  省选/NOI−  P13266 [GCJ 2014 Finals] Symmetric Trees  考点：模拟、树形 DP、哈希 hashing
 *   https://www.luogu.com.cn/problem/P15877  省选/NOI−  P15877 [ICPC 2026 NAC] Cable Pruning  考点：哈希 hashing、基环树
 *   https://www.luogu.com.cn/problem/P16691  省选/NOI−  P16691 怅惘 Plus  考点：树链剖分、哈希 hashing、虚树
 *   https://www.luogu.com.cn/problem/P17559  省选/NOI−  P17559 「FAOI-R15」青ノ栞歌  考点：模拟、哈希 hashing、构造
 *   https://www.luogu.com.cn/problem/P6653  省选/NOI−  P6653 [YsOI2020] 造林  考点：树形数据结构、树形 DP、哈希 hashing
 *   https://www.luogu.com.cn/problem/P8819  省选/NOI−  P8819 [CSP-S 2022] 星战  考点：图论、哈希 hashing、随机化
 *   https://www.luogu.com.cn/problem/P9399  省选/NOI−  P9399 「DBOI」Round 1 人生如树  考点：倍增、二分、树链剖分
 *   https://codeforces.com/problemset/problem/763/D  CF2900  CF763D Timofey and a flat tree  考点：数据结构、图论、哈希
 *
 */

// 树哈希：判断两棵树是否同构（洛谷 P5043）。
// 有根树：f(u) = 1 + Σ shift(f(v))（v 为 u 的儿子），shift 是一个"打乱"函数，结果对 2^64 自然溢出。
//   儿子的顺序不影响求和，所以同构的子树哈希值相同；shift 让不同的结构几乎不会碰撞。
//   MASK 在运行时随机生成，防止被特意构造的数据卡掉。
// 无根树：以重心为根求有根哈希；重心可能有两个，取两者中较小的哈希值。点编号 0..n-1
struct TreeHash {
    using ull = unsigned long long;
    static ull mask() {
        static const ull M = mt19937_64(chrono::steady_clock::now().time_since_epoch().count())();
        return M;
    }
    static ull shift(ull x) {
        x ^= mask();
        x ^= x << 13, x ^= x >> 7, x ^= x << 17;
        return x ^ mask();
    }
    // 以 root 为根时每个点的子树哈希值
    static vector<ull> rooted(const vector<vector<int>> &g, int root) {
        int n = g.size();
        vector<int> fa(n, -1), order{root};
        for (size_t i = 0; i < order.size(); i++)
            for (int v : g[order[i]])
                if (v != fa[order[i]]) fa[v] = order[i], order.push_back(v);
        vector<ull> f(n, 1);
        for (int i = n - 1; i > 0; i--) f[fa[order[i]]] += shift(f[order[i]]);
        return f;
    }
    static vector<int> centroids(const vector<vector<int>> &g) {
        int n = g.size();
        vector<int> fa(n, -1), sz(n, 1), order{0}, res;
        for (size_t i = 0; i < order.size(); i++)
            for (int v : g[order[i]])
                if (v != fa[order[i]]) fa[v] = order[i], order.push_back(v);
        for (int i = n - 1; i > 0; i--) sz[fa[order[i]]] += sz[order[i]];
        for (int u = 0; u < n; u++) {
            int mx = n - sz[u];
            for (int v : g[u])
                if (v != fa[u]) mx = max(mx, sz[v]);
            if (mx <= n / 2) res.push_back(u);
        }
        return res;
    }
    static ull unrooted(const vector<vector<int>> &g) {
        ull best = ULLONG_MAX;
        for (int c : centroids(g)) best = min(best, rooted(g, c)[c]);
        return best;
    }
};
