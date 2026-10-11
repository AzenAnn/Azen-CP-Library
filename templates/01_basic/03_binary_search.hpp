/**
 * 01_basic/03 二分查找、二分答案与三分
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. lower_bound / upper_bound
 *   2. 手写二分（开区间写法，不易死循环）
 *   3. 二分答案：最小化最大值 / 最大化最小值
 *   4. 实数二分
 *   5. 三分法求单峰函数极值
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/basic/binary/
 *   cp-algorithms  https://cp-algorithms.com/num_methods/binary_search.html
 *   cp-algorithms  https://cp-algorithms.com/num_methods/ternary_search.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/sort.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2249  P2249 【深基13.例1】查找
 *   https://www.luogu.com.cn/problem/P1873  P1873 [COCI 2011/2012 #5] EKO / 砍树
 *   https://www.luogu.com.cn/problem/P2678  P2678 [NOIP 2015 提高组] 跳石头
 *   https://www.luogu.com.cn/problem/P3382  P3382 三分
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/1915/C  CF800  CF1915C Can I Square?  考点：二分、实现
 *   https://codeforces.com/problemset/problem/1996/A  CF800  CF1996A Legs  考点：二分、数学、三分
 *   https://codeforces.com/problemset/problem/2114/A  CF800  CF2114A Square Year  考点：二分、暴力、数学
 *   https://codeforces.com/problemset/problem/750/A  CF800  CF750A New Year and Hurry  考点：二分、暴力、实现
 *   https://www.luogu.com.cn/problem/P1024  普及−  P1024 [NOIP 2001 提高组] 一元三次方程求解  考点：数学、二分、枚举
 *   https://www.luogu.com.cn/problem/P1147  普及−  P1147 连续正整数和  考点：数学、二分、枚举
 *   https://www.luogu.com.cn/problem/P1678  普及−  P1678 烦恼的高考志愿  考点：模拟、贪心、二分
 *   https://www.luogu.com.cn/problem/P1824  普及−  P1824 [USACO05FEB] 进击的奶牛 Aggressive Cows G  考点：贪心、二分
 *   https://www.luogu.com.cn/problem/P1314  普及  P1314 [NOIP 2011 提高组] 聪明的质监员  考点：数学、二分、前缀和
 *   https://www.luogu.com.cn/problem/P2440  普及  P2440 木材加工  考点：贪心、二分
 *   https://codeforces.com/problemset/problem/1538/C  CF1300  CF1538C Number of Pairs  考点：二分、数据结构、数学
 *   https://codeforces.com/problemset/problem/600/B  CF1300  CF600B Queries about less or equal elements  考点：二分、数据结构、排序
 *   https://codeforces.com/problemset/problem/1201/C  CF1400  CF1201C Maximum Median  考点：二分、贪心、数学
 *   https://codeforces.com/problemset/problem/1701/C  CF1400  CF1701C Schedule Management  考点：二分、贪心、实现
 *   https://www.luogu.com.cn/problem/P5937  普及+/提高−  P5937 [CEOI 1999] Parity Game  考点：并查集、离散化
 *
 */

// 1. STL（数组有序）：
//    lower_bound(a.begin(), a.end(), x)   第一个 >= x 的位置
//    upper_bound(a.begin(), a.end(), x)   第一个 >  x 的位置
//    x 的出现次数 = upper_bound - lower_bound
//    最后一个 <= x 的位置 = upper_bound - 1；最后一个 < x 的位置 = lower_bound - 1

// 2. 手写二分（开区间写法）：check 单调，先 false 后 true。
//    lo 取"一定为 false"的值，hi 取"一定为 true"的值（可以是越界的哨兵，不会被调用 check）。
//    循环中始终保持 check(lo) = false、check(hi) = true，返回第一个为 true 的值。
template <class F>
ll first_true(ll lo, ll hi, F check) {
    while (lo + 1 < hi) {
        ll mid = lo + (hi - lo) / 2;
        (check(mid) ? hi : lo) = mid;
    }
    return hi;
}

//    check 先 true 后 false 时：lo 取一定为 true 的值，hi 取一定为 false 的值，返回最后一个为 true 的值。
template <class F>
ll last_true(ll lo, ll hi, F check) {
    while (lo + 1 < hi) {
        ll mid = lo + (hi - lo) / 2;
        (check(mid) ? lo : hi) = mid;
    }
    return lo;
}

// 3. 二分答案：
//    "最小化最大值"：答案越大越容易满足 → first_true(下界 - 1, 上界, check)
//    "最大化最小值"：答案越小越容易满足 → last_true(下界, 上界 + 1, check)

// 4. 实数二分：固定迭代次数，比 while (hi - lo > eps) 更不容易因精度死循环
template <class F>
double first_true_real(double lo, double hi, F check, int iters = 100) {
    while (iters--) {
        double mid = (lo + hi) / 2;
        (check(mid) ? hi : lo) = mid;
    }
    return hi;
}

// 5. 三分：求 [lo, hi] 上单峰函数 f 的最大值点（实数）。求最小值把 < 改成 >
template <class F>
double ternary_max(double lo, double hi, F f, int iters = 100) {
    while (iters--) {
        double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) lo = m1;
        else hi = m2;
    }
    return (lo + hi) / 2;
}

//    整数三分：f 在 [lo, hi] 上先严格增后严格减（峰顶处允许相等），返回最大值点。
//    转化为二分"第一个满足 f(m) >= f(m + 1) 的 m"。
template <class F>
ll ternary_max_int(ll lo, ll hi, F f) {
    return first_true(lo - 1, hi, [&](ll m) { return m == hi || f(m) >= f(m + 1); });
}
