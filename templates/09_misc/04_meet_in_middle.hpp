/**
 * 09_misc/04 折半搜索 / Meet in the Middle
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：01_basic/03 二分查找、二分答案与三分、01_basic/12 搜索：DFS、BFS、剪枝
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 核心思想：把规模为 n 的问题拆成两半各 n/2，分别枚举后合并
 *   2. 复杂度：O(2^{n/2} · poly(n))，n ≤ 40~45 可过
 *   3. 合并方式：排序 + 二分 / 哈希表 / 双指针
 *   4. 应用：子集和、精确覆盖、高维部分和
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/search/bidirectional/  （双向搜索）
 *   USACO Guide    https://usaco.guide/gold/meet-in-the-middle
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4799  P4799 [CEOI 2015] 世界冰球锦标赛 (Day2)
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10484  普及+/提高−  P10484 送礼物  考点：折半搜索 meet in the middle
 *   https://www.luogu.com.cn/problem/P5691  普及+/提高−  P5691 [NOI2001] 方程的解数  考点：折半搜索 meet in the middle、数学、双指针 two-pointer
 *   https://www.luogu.com.cn/problem/P9234  普及+/提高−  P9234 [蓝桥杯 2023 省 A] 买瓜  考点：折半搜索 meet in the middle
 *   https://www.luogu.com.cn/problem/P2962  提高  P2962 [USACO09NOV] Lights G  考点：折半搜索 meet in the middle、搜索、深度优先搜索 DFS
 *   https://www.luogu.com.cn/problem/P3067  提高  P3067 [USACO12OPEN] Balanced Cow Subsets G  考点：折半搜索 meet in the middle、搜索
 *   https://codeforces.com/problemset/problem/888/E  CF1800  CF888E Maximum Subsequence  考点：两半分别枚举模 m 的和，排序后双指针
 *   https://codeforces.com/problemset/problem/1006/F  CF2100  CF1006F Xor-Paths  考点：从起点和终点各走一半步数，在对角线上合并异或值
 *   https://www.luogu.com.cn/problem/P12371  省选/NOI−  P12371 【模板】最大团/最大独立集  考点：折半搜索 meet in the middle、搜索、深度优先搜索 DFS
 *
 */

// 折半搜索（meet in the middle）：n ≤ 40 时，把物品分成两半各自枚举 2^{n/2} 个子集和，
// 再用排序 + 二分 / 双指针合并，O(2^{n/2} · n)。
// 例 1：和 ≤ S 的子集个数（世界冰球锦标赛）；例 2：和 ≤ S 的最大子集和。
vector<ll> mitm_half_sums(const vector<ll> &a, int l, int r) {   // a[l..r) 的所有子集和（升序）
    vector<ll> s = {0};
    for (int i = l; i < r; i++) {   // 每加入一个数，把"加它"和"不加它"两个有序序列归并
        vector<ll> t(s.size());
        for (size_t j = 0; j < s.size(); j++) t[j] = s[j] + a[i];
        vector<ll> m(s.size() * 2);
        merge(s.begin(), s.end(), t.begin(), t.end(), m.begin());
        s.swap(m);
    }
    return s;
}
ll count_subsets_leq(const vector<ll> &a, ll S) {
    int n = a.size();
    auto L = mitm_half_sums(a, 0, n / 2), R = mitm_half_sums(a, n / 2, n);
    ll cnt = 0;
    int j = R.size();
    for (ll x : L) {   // L 升序，R 中满足 x + y ≤ S 的个数单调不增：双指针
        while (j > 0 && x + R[j - 1] > S) j--;
        cnt += j;
    }
    return cnt;
}
ll max_subset_leq(const vector<ll> &a, ll S) {   // 没有满足条件的子集时返回 LLONG_MIN（空集和为 0）
    int n = a.size();
    auto L = mitm_half_sums(a, 0, n / 2), R = mitm_half_sums(a, n / 2, n);
    ll best = LLONG_MIN;
    for (ll x : L) {
        auto it = upper_bound(R.begin(), R.end(), S - x);
        if (it != R.begin()) best = max(best, x + *prev(it));
    }
    return best;
}
