/**
 * 02_ds/09 笛卡尔树
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/01 栈与单调栈、02_ds/05 ST 表
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 定义：下标满足二叉搜索树（中序遍历是 0..n-1），值满足堆（父亲比儿子小）
 *   2. 单调栈 O(n) 建树：新元素把栈里比它大的都弹出，最后弹出的成为它的左儿子，它成为栈顶的右儿子
 *   3. 子树 = 一段区间 [L, R]，并且 a[u] 是这段区间的最小值：枚举每个点作为最小值时的贡献（和单调栈的贡献法相同）
 *   4. 区间最值分治：在笛卡尔树上做 DP / 启发式合并（每次在较短的一侧枚举）
 *   5. 区间最小值 = 两点在笛卡尔树上的 LCA；Treap 就是用随机优先级建的笛卡尔树
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/cartesian-tree/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5854  P5854 【模板】笛卡尔树
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2659  普及  P2659 美丽的序列  考点：笛卡尔树、线段树、二分
 *   https://www.luogu.com.cn/problem/P2171  普及+/提高−  P2171 Hz 吐泡泡  考点：笛卡尔树、单调栈
 *   https://www.luogu.com.cn/problem/P6503  普及+/提高−  P6503 [COCI 2010/2011 #3] DIFERENCIJA  考点：笛卡尔树、单调栈
 *   https://www.luogu.com.cn/problem/P1377  提高  P1377 [TJOI2011] 树的序  考点：笛卡尔树
 *   https://www.luogu.com.cn/problem/P7988  提高  P7988 [USACO21DEC] HILO G  考点：笛卡尔树
 *   https://www.luogu.com.cn/problem/P4755  提高+/省选−  P4755 Beautiful Pair  考点：笛卡尔树、树状数组、枚举
 *   https://www.luogu.com.cn/problem/P9352  提高+/省选−  P9352 [JOI 2023 Final] 训猫 / Cat Exercise  考点：笛卡尔树、动态规划 DP、并查集
 *   https://www.luogu.com.cn/problem/P6453  省选/NOI−  P6453 [COCI 2008/2009 #4] PERIODNI  考点：笛卡尔树、动态规划 DP、背包 DP
 *   https://www.luogu.com.cn/problem/P7219  省选/NOI−  P7219 [JOISC 2020] 星座 3  考点：笛卡尔树、动态规划 DP、线段树
 *
 */

// 笛卡尔树（小根）：O(n) 单调栈建树，下标 0..n-1。相等的值：靠左的在上面（作为祖先）。
// 求大根笛卡尔树时传入 greater<T>()。
// lc / rc / fa 为 -1 表示没有；[L[u], R[u]] 是 u 的子树对应的区间，a[u] 是这段区间的最小值。
template <class T, class Cmp = less<T>>
struct CartesianTree {
    int n, root;
    vector<int> lc, rc, fa, L, R;
    CartesianTree(const vector<T> &a, Cmp cmp = Cmp()) : n(a.size()), root(-1), lc(n, -1), rc(n, -1), fa(n, -1), L(n), R(n) {
        vector<int> st;
        for (int i = 0; i < n; i++) {
            int last = -1;
            while (!st.empty() && cmp(a[i], a[st.back()])) last = st.back(), st.pop_back();
            if (last != -1) lc[i] = last, fa[last] = i;
            if (!st.empty()) rc[st.back()] = i, fa[i] = st.back();
            st.push_back(i);
        }
        if (n) root = st[0];
        // 子树区间：按父亲在前的顺序（BFS）推出，避免递归爆栈
        if (n) {
            vector<int> q = {root};
            L[root] = 0, R[root] = n - 1;
            for (size_t h = 0; h < q.size(); h++) {
                int u = q[h];
                if (lc[u] != -1) L[lc[u]] = L[u], R[lc[u]] = u - 1, q.push_back(lc[u]);
                if (rc[u] != -1) L[rc[u]] = u + 1, R[rc[u]] = R[u], q.push_back(rc[u]);
            }
        }
    }
};

// 例：所有子数组最小值之和 = Σ a[u] · (u − L[u] + 1) · (R[u] − u + 1)
template <class T>
ll sum_of_subarray_min(const vector<T> &a) {
    CartesianTree<T> ct(a);
    ll s = 0;
    for (int u = 0; u < ct.n; u++) s += (ll)a[u] * (u - ct.L[u] + 1) * (ct.R[u] - u + 1);
    return s;
}
