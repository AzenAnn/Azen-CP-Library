/**
 * 02_ds/19 可并堆（左偏树）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：02_ds/03 堆与优先队列
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 左偏树的合并操作
 *   2. 配合并查集维护堆所属集合
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/leftist-tree/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/leftist_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3377  P3377 【模板】可并堆 1
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10759  省选/NOI−  P10759 [BalticOI 2024] Jobs  考点：贪心、可并堆、启发式合并
 *   https://www.luogu.com.cn/problem/P11820  省选/NOI−  P11820 [PA 2015] 健身房 / Siłownia  考点：贪心、线段树、可并堆
 *   https://www.luogu.com.cn/problem/P3261  省选/NOI−  P3261 [JLOI2015] 城池攻占  考点：倍增、可并堆、栈
 *   https://www.luogu.com.cn/problem/P3273  省选/NOI−  P3273 [SCOI2011] 棘手的操作  考点：线段树、并查集、深度优先搜索 DFS
 *   https://www.luogu.com.cn/problem/P4331  省选/NOI−  P4331 [BalticOI 2004] Sequence (Day1)  考点：动态规划 DP、贪心、线段树
 *   https://www.luogu.com.cn/problem/P4359  省选/NOI−  P4359 [CQOI2016] 伪光滑数  考点：搜索、可并堆、素数判断
 *   https://www.luogu.com.cn/problem/P8316  省选/NOI−  P8316 [CQOI2016] 伪光滑数 加强版  考点：动态规划 DP、优先队列、可并堆
 *   https://www.luogu.com.cn/problem/P1753  NOI/NOI+/CTS  P1753 矩阵链排序问题  考点：动态规划 DP、图论、区间 DP
 *   https://www.luogu.com.cn/problem/P2483  NOI/NOI+/CTS  P2483 【模板】k 短路 / [SDOI2010] 魔法猪学院  考点：最短路、可并堆、可持久化
 *   https://www.luogu.com.cn/problem/P3642  NOI/NOI+/CTS  P3642 [APIO2016] 烟花表演  考点：动态规划 DP、动态规划优化、树形 DP
 *   https://www.luogu.com.cn/problem/P6943  NOI/NOI+/CTS  P6943 [ICPC 2018 WF] Conquer The World  考点：平衡树、堆、可并堆
 *   https://www.luogu.com.cn/problem/P9962  NOI/NOI+/CTS  P9962 [THUPC 2024 初赛] 一棵树  考点：平衡树、可并堆、凸包
 *
 */

// 左偏树（可并堆）：支持 O(log n) 合并两个堆的小根堆（洛谷 P3377）
// dist[x] 为 x 到最近的"缺儿子的节点"的距离；保持 dist[左] >= dist[右]，右链长度 O(log n)。
// 合并时沿右链递归。再用并查集 rt 找到每个元素所在堆的堆顶。元素编号 0..n-1
struct LeftistHeap {
    vector<ll> val;
    vector<int> l, r, dist, rt;
    vector<bool> del;
    LeftistHeap(const vector<ll> &a) : val(a), l(a.size(), -1), r(a.size(), -1), dist(a.size(), 0), rt(a.size()), del(a.size(), false) {
        iota(rt.begin(), rt.end(), 0);
    }
    int d(int x) const { return x < 0 ? -1 : dist[x]; }
    bool less_than(int x, int y) const { return val[x] < val[y] || (val[x] == val[y] && x < y); }
    int merge(int x, int y) {   // 合并以 x、y 为根的堆，返回新根
        if (x < 0 || y < 0) return x < 0 ? y : x;
        if (less_than(y, x)) swap(x, y);
        r[x] = merge(r[x], y);
        if (d(l[x]) < d(r[x])) swap(l[x], r[x]);
        dist[x] = d(r[x]) + 1;
        return x;
    }
    int find(int x) {   // x 所在堆的堆顶（路径压缩）
        int root = x;
        while (rt[root] != root) root = rt[root];
        while (rt[x] != root) { int nx = rt[x]; rt[x] = root; x = nx; }
        return root;
    }
    void unite(int x, int y) {   // 合并 x 和 y 所在的堆；有一个已被删除或已在同一个堆时忽略
        if (del[x] || del[y]) return;
        x = find(x), y = find(y);
        if (x == y) return;
        rt[x] = rt[y] = merge(x, y);
    }
    ll pop(int x) {   // 删除 x 所在堆的最小值并返回；x 已被删除时返回 LLONG_MIN
        if (del[x]) return LLONG_MIN;
        x = find(x);
        del[x] = true;
        int z = merge(l[x], r[x]);
        if (z >= 0) rt[z] = z;
        rt[x] = z >= 0 ? z : x;   // 原来指向 x 的元素，通过 x 找到新堆顶
        return val[x];
    }
};
