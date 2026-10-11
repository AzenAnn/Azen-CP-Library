/**
 * 02_ds/15 CDQ 分治与整体二分
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：01_basic/10 分治、02_ds/06 树状数组
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. CDQ 分治：三维偏序
 *   2. 整体二分
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/misc/cdq-divide/
 *   OI-wiki        https://oi-wiki.org/misc/parallel-binsearch/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/cdq.go
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/offline.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3810  P3810 【模板】三维偏序 / 陌上花开
 *   https://www.luogu.com.cn/problem/P3527  P3527 [POI 2011] MET-Meteors
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/1093/E  CF2400  CF1093E Intersection of Permutations  考点：数据结构
 *   https://www.luogu.com.cn/problem/P1527  省选/NOI−  P1527 [国家集训队] 矩阵乘法  考点：整体二分
 *   https://www.luogu.com.cn/problem/P2487  省选/NOI−  P2487 [SDOI2011] 拦截导弹  考点：动态规划 DP、树状数组、cdq 分治
 *   https://www.luogu.com.cn/problem/P3250  省选/NOI−  P3250 [HNOI2016] 网络  考点：线段树、最近公共祖先 LCA、树链剖分
 *   https://www.luogu.com.cn/problem/P3364  省选/NOI−  P3364 Cool loves touli  考点：动态规划 DP、cdq 分治
 *   https://www.luogu.com.cn/problem/P4093  省选/NOI−  P4093 [HEOI2016/TJOI2016] 序列  考点：动态规划 DP、线段树、cdq 分治
 *   https://www.luogu.com.cn/problem/P7560  省选/NOI−  P7560 [JOISC 2021] フードコート (Day1)
 *   https://codeforces.com/problemset/problem/868/F  CF2500  CF868F Yet Another Minimization Problem  考点：分治、DP
 *   https://codeforces.com/problemset/problem/1386/C  CF2800  CF1386C Joker  考点：位运算、数据结构、分治
 *   https://codeforces.com/problemset/problem/1028/H  CF2900  CF1028H Make Square  考点：数学
 *   https://www.luogu.com.cn/problem/P13508  NOI/NOI+/CTS  P13508 [OOI 2024] Burenka and Pether  考点：线段树、倍增、分块
 *   https://codeforces.com/problemset/problem/1175/G  CF3000  CF1175G Yet Another Partiton Problem  考点：数据结构、分治、DP
 *   https://codeforces.com/problemset/problem/1920/F2  CF3000  CF1920F2 Smooth Sailing (Hard Version)  考点：二分、数据结构、并查集
 *   https://codeforces.com/problemset/problem/1989/F  CF3000  CF1989F Simultaneous Coloring  考点：搜索、分治、图论
 *   https://codeforces.com/problemset/problem/603/E  CF3000  CF603E Pastoral Oddities  考点：数据结构、分治、并查集
 *
 */

// 1. CDQ 分治：三维偏序（洛谷 P3810）
//    对每个点 i，求满足 a_j <= a_i、b_j <= b_i、c_j <= c_i 的 j（j != i）的个数。
//    第一维排序；分治 [l, m)、[m, r) 后，只统计"左半对右半"的贡献：两半各按 b 排序，
//    双指针把左半中 b 不超过当前点的加入树状数组（以 c 为下标），再查询 c 的前缀和。O(n log^2 n)
vector<int> partial_order_3d(const vector<array<int, 3>> &pts) {
    struct E { int a, b, c, cnt, res; };
    int n = pts.size();
    vector<array<int, 3>> s(pts);
    sort(s.begin(), s.end());
    vector<E> e;
    for (int i = 0; i < n; i++) {   // 合并完全相同的点
        if (!e.empty() && e.back().a == s[i][0] && e.back().b == s[i][1] && e.back().c == s[i][2]) e.back().cnt++;
        else e.push_back({s[i][0], s[i][1], s[i][2], 1, 0});
    }
    vector<int> cs;
    for (auto &x : e) cs.push_back(x.c);
    sort(cs.begin(), cs.end());
    cs.erase(unique(cs.begin(), cs.end()), cs.end());
    int K = cs.size();
    vector<int> bit(K + 1, 0);
    auto add = [&](int i, int v) { for (i++; i <= K; i += i & -i) bit[i] += v; };
    auto sum = [&](int i) { int r = 0; for (i++; i > 0; i -= i & -i) r += bit[i]; return r; };
    auto cid = [&](int c) { return int(lower_bound(cs.begin(), cs.end(), c) - cs.begin()); };
    auto by_b = [](const E &x, const E &y) { return x.b < y.b; };
    function<void(int, int)> cdq = [&](int l, int r) {
        if (r - l <= 1) return;
        int m = (l + r) / 2;
        cdq(l, m), cdq(m, r);   // 返回后两半都已按 b 排好序
        int i = l;
        for (int j = m; j < r; j++) {
            while (i < m && e[i].b <= e[j].b) add(cid(e[i].c), e[i].cnt), i++;
            e[j].res += sum(cid(e[j].c));
        }
        for (int k = l; k < i; k++) add(cid(e[k].c), -e[k].cnt);   // 撤销
        inplace_merge(e.begin() + l, e.begin() + m, e.begin() + r, by_b);
    };
    cdq(0, e.size());
    map<array<int, 3>, int> ans;   // 相同的点之间也互相满足条件：再加上 cnt - 1
    for (auto &x : e) ans[{x.a, x.b, x.c}] = x.res + x.cnt - 1;
    vector<int> res(n);
    for (int i = 0; i < n; i++) res[i] = ans[pts[i]];
    return res;
}

// 2. 整体二分：静态区间第 k 小。把所有询问放在一起二分答案：
//    对值域 [lo, hi) 取中点 mid，把值 < mid 的位置加入树状数组；
//    区间内个数 >= k 的询问答案在左半，否则 k 减去个数，去右半。O((n + q) log n log V)
//    qs[i] = {l, r, k}：区间 [l, r) 中第 k 小（k 从 1 开始）
vector<ll> parallel_kth(const vector<ll> &a, const vector<array<int, 3>> &qs) {
    int n = a.size(), q = qs.size();
    vector<ll> vals(a);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    vector<int> vid(n), need(q);
    for (int i = 0; i < n; i++) vid[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
    for (int i = 0; i < q; i++) need[i] = qs[i][2];
    vector<int> bit(n + 1, 0);
    auto add = [&](int i, int v) { for (i++; i <= n; i += i & -i) bit[i] += v; };
    auto pre = [&](int i) { int r = 0; for (; i > 0; i -= i & -i) r += bit[i]; return r; };   // [0, i)
    vector<ll> ans(q);
    function<void(int, int, vector<int> &, vector<int> &)> solve = [&](int lo, int hi, vector<int> &qids, vector<int> &items) {
        if (qids.empty()) return;
        if (hi - lo == 1) {
            for (int id : qids) ans[id] = vals[lo];
            return;
        }
        int mid = (lo + hi) / 2;
        vector<int> li, ri, lq, rq;
        for (int p : items) (vid[p] < mid ? li : ri).push_back(p);
        for (int p : li) add(p, 1);
        for (int id : qids) {
            int c = pre(qs[id][1]) - pre(qs[id][0]);
            if (need[id] <= c) lq.push_back(id);
            else need[id] -= c, rq.push_back(id);
        }
        for (int p : li) add(p, -1);
        solve(lo, mid, lq, li), solve(mid, hi, rq, ri);
    };
    vector<int> all_q(q), all_items(n);
    iota(all_q.begin(), all_q.end(), 0), iota(all_items.begin(), all_items.end(), 0);
    if (n) solve(0, vals.size(), all_q, all_items);
    return ans;
}
