/**
 * 06_dp/16 WQS 二分与 Slope Trick
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：06_dp/10 斜率优化与凸包技巧
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. WQS 二分：限制选 k 个 → 每选一个附带 λ 惩罚，二分 λ 使最优解恰好选 k 个
 *   2. 要求：f(k)（选 k 个的最优值）关于 k 是凸/凹函数
 *   3. 内层 DP 需同时维护"值"和"选的个数"，平局取个数多/少
 *   4. Slope Trick：维护分段线性凸函数（拐点多重集合），支持平移、取 min、合并
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/opt/wqs-binary-search/
 *   OI-wiki        https://oi-wiki.org/dp/opt/slope-trick/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2619  P2619 [国家集训队] Tree I
 *   https://www.luogu.com.cn/problem/P4597  P4597 序列 sequence
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1484  提高  P1484 种树  考点：凸完全单调性（wqs 二分）、动态规划 DP、贪心
 *   https://www.luogu.com.cn/problem/P1792  提高  P1792 [国家集训队] 种树  考点：凸完全单调性（wqs 二分）、动态规划 DP、贪心
 *   https://www.luogu.com.cn/problem/P2893  提高  P2893 [USACO08FEB] Making the Grade G  考点：斜率维护技巧 slope trick、动态规划 DP、贪心
 *   https://www.luogu.com.cn/problem/P3620  提高+/省选−  P3620 [APIO/CTSC2007] 数据备份  考点：凸完全单调性（wqs 二分）、贪心、线段树
 *   https://www.luogu.com.cn/problem/P4072  提高+/省选−  P4072 [SDOI2016] 征途  考点：凸完全单调性（wqs 二分）、单调队列、斜率优化
 *   https://codeforces.com/problemset/problem/713/C  CF2300  CF713C Sonya and Problem Wihtout a Legend  考点：严格递增：令 a_i −= i 后变成单调不降
 *   https://codeforces.com/problemset/problem/865/D  CF2400  CF865D Buy Low Sell High  考点：反悔贪心 / slope trick
 *   https://www.luogu.com.cn/problem/P4331  省选/NOI−  P4331 [BalticOI 2004] Sequence (Day1)  考点：斜率维护技巧 slope trick、动态规划 DP、贪心
 *   https://www.luogu.com.cn/problem/P4983  省选/NOI−  P4983 忘情  考点：凸完全单调性（wqs 二分）、斜率优化、四边形不等式
 *   https://www.luogu.com.cn/problem/P5633  省选/NOI−  P5633 最小度限制生成树  考点：凸完全单调性（wqs 二分）、图论、生成树
 *   https://www.luogu.com.cn/problem/P3642  NOI/NOI+/CTS  P3642 [APIO2016] 烟花表演  考点：斜率维护技巧 slope trick、动态规划 DP、动态规划优化
 *   https://www.luogu.com.cn/problem/P4383  NOI/NOI+/CTS  P4383 [八省联考 2018] 林克卡特树  考点：凸完全单调性（wqs 二分）、动态规划 DP、枚举
 *   https://www.luogu.com.cn/problem/P5896  NOI/NOI+/CTS  P5896 [IOI 2016] aliens  考点：凸完全单调性（wqs 二分）、动态规划 DP、斜率优化
 *   https://codeforces.com/problemset/problem/739/E  CF3000  CF739E Gosha is hunting  考点：两层 WQS 二分
 *
 */

// 1. WQS 二分（凸优化 / Aliens trick）：限制"恰好选 k 个"时，若最优值 F(k) 关于 k 是凹函数（求最大），
//    给每选一个附加代价 λ，不限个数求 max(F(k) − λk)，二分 λ 使最优解恰好选 k 个，答案 = 结果 + λk。
//    内层要同时返回"最优值"和"取到最优值时选的个数"（平局时取最多的个数），二分找最大的 λ 使个数 ≥ k（k 落在 F 的一段直线中间时也正确）。
//    下面的 wqs 是通用框架：solve(λ) 返回 {max(F(c) − λc), c}（平局取 c 最大），F 须为凹函数且 λ、F 都是整数；
//    [lo, hi] 要包住所有斜率 F(c+1) − F(c)，宁可开大一点。
template <class F>
ll wqs(ll lo, ll hi, int k, F solve) {
    while (lo < hi) {   // 找最大的 λ 使 c ≥ k（c 随 λ 增大而不增）
        ll mid = lo + (hi - lo + 1) / 2;
        if (solve(mid).second >= k) lo = mid;
        else hi = mid - 1;
    }
    return solve(lo).first + lo * k;
}
// 例：从序列中恰好选 k 个互不相邻的数，使和最大（选不出 k 个时请先判断 k ≤ ⌈n/2⌉）。
ll max_k_nonadjacent(const vector<ll> &a, int k) {
    auto solve = [&](ll lam) {   // 每选一个减 λ，不限个数
        pair<ll, int> f0 = {0, 0}, f1 = {LLONG_MIN / 4, 0};   // 上一个不选 / 选
        for (ll x : a) {
            pair<ll, int> n0 = max(f0, f1), n1 = {f0.first + x - lam, f0.second + 1};
            f0 = n0, f1 = n1;
        }
        return max(f0, f1);   // pair 比较：值相同时取个数多的
    };
    ll mx = 0;
    for (ll x : a) mx = max(mx, llabs(x));
    ll B = (ll)(a.size() + 1) * (2 * mx + 1);   // 斜率 F(k+1) − F(k) 的绝对值上界（换选法时可能远大于 max|a|）
    return wqs(-B, B, k, solve);
}

// 2. Slope Trick：DP 值是关于某个变量的分段线性凸函数时，只维护"拐点"的多重集合。
//    例：把序列改成单调不降，代价 Σ|a_i − b_i| 最小。用大根堆维护拐点：每读入 x 就压入；
//    若堆顶 > x，代价增加 堆顶 − x，弹出堆顶再压入 x。O(n log n)。（严格递增时先令 a_i −= i。）
ll min_cost_nondecreasing(const vector<ll> &a) {
    priority_queue<ll> pq;
    ll cost = 0;
    for (ll x : a) {
        pq.push(x);
        if (pq.top() > x) {
            cost += pq.top() - x;
            pq.pop(), pq.push(x);
        }
    }
    return cost;
}
