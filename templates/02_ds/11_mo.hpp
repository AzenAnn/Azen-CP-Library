/**
 * 02_ds/11 莫队
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/10 分块与根号分治
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 普通莫队（奇偶排序优化）
 *   2. 带修莫队
 *   3. 回滚莫队
 *   4. 树上莫队
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/misc/mo-algo/
 *   cp-algorithms  https://cp-algorithms.com/data_structures/sqrt_decomposition.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/mo.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1494  P1494 [国家集训队] 小 Z 的袜子
 *   https://www.luogu.com.cn/problem/P1903  P1903 【模板】带修莫队 / [国家集训队] 数颜色 / 维护队列
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2709  提高  P2709 【模板】莫队 / 小 B 的询问  考点：莫队
 *   https://www.luogu.com.cn/problem/P4462  提高  P4462 [CQOI2018] 异或序列  考点：莫队、前缀和
 *   https://www.luogu.com.cn/problem/P5673  提高  P5673 「SWTR-2」Picking Gifts  考点：树状数组
 *   https://www.luogu.com.cn/problem/P7764  提高  P7764 [COCI 2016/2017 #5] Poklon  考点：莫队、线段树、树状数组
 *   https://codeforces.com/problemset/problem/220/B  CF1800  CF220B Little Elephant and Array  考点：构造、数据结构
 *   https://www.luogu.com.cn/problem/P2590  提高+/省选−  P2590 [ZJOI2008] 树的统计  考点：莫队、线段树、树链剖分
 *   https://www.luogu.com.cn/problem/P5906  提高+/省选−  P5906 【模板】回滚莫队&不删除莫队  考点：莫队
 *   https://codeforces.com/problemset/problem/617/E  CF2200  CF617E XOR and Favorite Number  考点：数据结构
 *   https://codeforces.com/problemset/problem/86/D  CF2200  CF86D Powerful array  考点：数据结构、实现、数学
 *   https://codeforces.com/problemset/problem/877/F  CF2300  CF877F Ann and Books  考点：数据结构、网络流、哈希
 *   https://codeforces.com/problemset/problem/375/D  CF2400  CF375D Tree and Queries  考点：数据结构、搜索、树
 *   https://www.luogu.com.cn/problem/P4074  省选/NOI−  P4074 [WC2013] 糖果公园  考点：莫队、最近公共祖先 LCA、分块
 *   https://www.luogu.com.cn/problem/P4887  省选/NOI−  P4887 【模板】莫队二次离线 / 第十四分块(前体)  考点：递推、莫队、前缀和
 *   https://www.luogu.com.cn/problem/P5047  省选/NOI−  P5047 [Ynoi2019 模拟赛] Yuno loves sqrt technology II  考点：莫队、分块
 *   https://codeforces.com/problemset/problem/940/F  CF2600  CF940F Machine Learning  考点：暴力、数据结构
 *
 */

// 莫队：离线处理区间询问。把询问按 (l 所在的块, r) 排序，相邻询问之间移动左右端点，
// 每移动一步调用一次 add / remove。块长取 n / √q 左右，总复杂度 O(n√q)。
// 区间均为左闭右开 [l, r)，下标从 0 开始

// 1. 普通莫队：add(i) 把位置 i 加入窗口，remove(i) 移出，get() 返回当前窗口的答案
//    奇偶排序：奇数块 r 升序、偶数块 r 降序，r 指针来回扫，常数约减半
template <class Add, class Remove, class Get>
auto mo(int n, const vector<pair<int, int>> &qs, Add add, Remove remove, Get get) {
    int q = qs.size(), B = max(1, (int)(n / sqrt(max(q, 1))));
    vector<int> ord(q);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        int ba = qs[a].first / B, bb = qs[b].first / B;
        if (ba != bb) return ba < bb;
        return (ba & 1) ? qs[a].second > qs[b].second : qs[a].second < qs[b].second;
    });
    vector<decltype(get())> ans(q);
    int L = 0, R = 0;   // 当前窗口 [L, R)
    for (int id : ord) {
        auto [l, r] = qs[id];
        while (L > l) add(--L);   // 先扩张再收缩，保证窗口始终合法
        while (R < r) add(R++);
        while (L < l) remove(L++);
        while (R > r) remove(--R);
        ans[id] = get();
    }
    return ans;
}

// 2. 带修莫队：询问多一维"时间" t（表示前 t 个修改已经生效）。块长取 n^(2/3)，复杂度 O(n^(5/3))
//    修改 i 为"把 a[pos] 改成 val"。apply 时与数组中的值交换，再执行一次就是撤销
//    qs[i] = {l, r, t}；a 会被修改，结束时恢复原样
template <class T, class Add, class Remove, class Get>
auto mo_with_updates(vector<T> &a, const vector<array<int, 3>> &qs, vector<pair<int, T>> ups,
                     Add add, Remove remove, Get get) {
    int n = a.size(), q = qs.size();
    int B = max(1, (int)cbrt((double)n * n));
    vector<int> ord(q);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y) {
        auto &A = qs[x], &C = qs[y];
        if (A[0] / B != C[0] / B) return A[0] / B < C[0] / B;
        if (A[1] / B != C[1] / B) return A[1] / B < C[1] / B;
        return A[2] < C[2];
    });
    vector<decltype(get())> ans(q);
    int L = 0, R = 0, t = 0;
    auto apply = [&](int k) {   // 执行或撤销第 k 个修改
        int pos = ups[k].first;
        bool inside = L <= pos && pos < R;
        if (inside) remove(pos);
        swap(a[pos], ups[k].second);
        if (inside) add(pos);
    };
    for (int id : ord) {
        auto [l, r, tt] = qs[id];
        while (L > l) add(--L);
        while (R < r) add(R++);
        while (L < l) remove(L++);
        while (R > r) remove(--R);
        while (t < tt) apply(t++);
        while (t > tt) apply(--t);
        ans[id] = get();
    }
    while (t > 0) apply(--t);
    return ans;
}

// 3. 回滚莫队（只加不删）：适用于"加入容易、删除困难"的信息（如区间众数的出现次数、最大值）。
//    对 l 在同一块的询问，右端点从块尾开始单调右移；左端点每次从块尾向左加入，求完答案后回滚。
//    需要提供：reset() 清空状态，add(i) 加入，snapshot() 记录当前状态，rollback() 回到记录的状态
template <class Reset, class Add, class Snap, class Rollback, class Get>
auto mo_rollback(int n, const vector<pair<int, int>> &qs, Reset reset, Add add, Snap snapshot,
                 Rollback rollback, Get get) {
    int q = qs.size(), B = max(1, (int)(n / sqrt(max(q, 1))));
    vector<int> ord(q);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (qs[a].first / B != qs[b].first / B) return qs[a].first / B < qs[b].first / B;
        return qs[a].second < qs[b].second;
    });
    vector<decltype(get())> ans(q);
    int cur_block = -1, R = 0, block_end = 0;
    for (int id : ord) {
        auto [l, r] = qs[id];
        int b = l / B;
        if (r - l <= B) {   // 区间很短：直接暴力
            reset();
            for (int i = l; i < r; i++) add(i);
            ans[id] = get();
            cur_block = -1;
            continue;
        }
        if (b != cur_block) {   // 进入新的块：状态清空，右端点从块尾开始
            reset();
            cur_block = b, block_end = min(n, (b + 1) * B), R = block_end;
        }
        while (R < r) add(R++);
        snapshot();
        for (int i = block_end - 1; i >= l; i--) add(i);
        ans[id] = get();
        rollback();
    }
    return ans;
}

// 4. 树上莫队：把树上路径询问转成括号序（每个点进出各记一次，长 2n）上的区间询问。
//    路径上的点恰好在区间中出现奇数次，所以 add / remove 统一改成 toggle（出现一次加、两次减）。
//    in/out：括号序中第一次、第二次出现的位置。返回 {l, r, extra}：括号序区间 [l, r)，
//    extra 为需要额外 toggle 的 LCA（u、v 不是祖先关系时 LCA 不在区间内），否则为 -1
//    用法：对每个询问 toggle 区间里的点，若 extra != -1 再临时 toggle(extra)，取答案后撤销
struct TreeMoRanges {
    vector<int> euler, in, out, dep, par;
    vector<vector<int>> up;
    TreeMoRanges(const vector<vector<int>> &g, int root = 0) {
        int n = g.size(), LOG = __lg(max(n, 1)) + 1;
        in.assign(n, 0), out.assign(n, 0), dep.assign(n, 0), par.assign(n, root);
        vector<int> it(n, 0), st{root};
        vector<bool> vis(n, false);
        vis[root] = true, in[root] = 0, euler.push_back(root);
        while (!st.empty()) {   // 迭代 DFS 生成括号序
            int u = st.back();
            if (it[u] < (int)g[u].size()) {
                int v = g[u][it[u]++];
                if (vis[v]) continue;
                vis[v] = true, par[v] = u, dep[v] = dep[u] + 1;
                in[v] = euler.size(), euler.push_back(v), st.push_back(v);
            } else {
                out[u] = euler.size(), euler.push_back(u), st.pop_back();
            }
        }
        up.assign(LOG, par);
        for (int k = 1; k < LOG; k++)
            for (int u = 0; u < n; u++) up[k][u] = up[k - 1][up[k - 1][u]];
    }
    int lca(int a, int b) const {
        if (dep[a] < dep[b]) swap(a, b);
        for (int k = up.size() - 1; k >= 0; k--)
            if (dep[a] - (1 << k) >= dep[b]) a = up[k][a];
        if (a == b) return a;
        for (int k = up.size() - 1; k >= 0; k--)
            if (up[k][a] != up[k][b]) a = up[k][a], b = up[k][b];
        return par[a];
    }
    array<int, 3> range(int u, int v) const {
        if (in[u] > in[v]) swap(u, v);
        int w = lca(u, v);
        if (w == u) return {in[u], in[v] + 1, -1};
        return {out[u], in[v] + 1, w};
    }
};
