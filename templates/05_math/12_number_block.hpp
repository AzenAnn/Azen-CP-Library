/**
 * 05_math/12 数论分块（整除分块）
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. n/i 只有 O(√n) 种取值
 *   2. 枚举每一段 [l, r]
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/sqrt-decomposition/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2261  P2261 [CQOI2007] 余数求和
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1447  提高  P1447 [NOI2010] 能量采集  考点：数学、最大公约数 gcd、莫比乌斯反演
 *   https://www.luogu.com.cn/problem/P3911  提高+/省选−  P3911 最小公倍数之和  考点：数学、莫比乌斯反演
 *   https://www.luogu.com.cn/problem/P3935  提高  P3935 Calculating  考点：数学、整除分块
 *   https://www.luogu.com.cn/problem/P4450  提高  P4450 双亲数  考点：数学、莫比乌斯反演、容斥原理
 *   https://www.luogu.com.cn/problem/P6583  提高  P6583 回首过去  考点：数论、整除分块
 *   https://codeforces.com/problemset/problem/1900/D  CF2000  CF1900D Small GCD  考点：位运算、暴力、DP
 *   https://codeforces.com/problemset/problem/803/F  CF2000  CF803F Coprime Subsequences  考点：位运算、组合数学、数论
 *   https://codeforces.com/problemset/problem/900/D  CF2000  CF900D Unusual Sequences  考点：位运算、组合数学、DP
 *   https://codeforces.com/problemset/problem/616/E  CF2200  CF616E Sum of Remainders  考点：实现、数学、数论
 *   https://codeforces.com/problemset/problem/547/C  CF2300  CF547C Mike and Foam  考点：位运算、组合数学、DP
 *   https://codeforces.com/problemset/problem/1780/E  CF2400  CF1780E Josuke and Complete Graph  考点：二分、暴力、数据结构
 *   https://codeforces.com/problemset/problem/226/C  CF2400  CF226C Anniversary  考点：数据结构、实现、数学
 *   https://www.luogu.com.cn/problem/P3327  省选/NOI−  P3327 [SDOI2015] 约数个数和  考点：数学、数论、最大公约数 gcd
 *   https://www.luogu.com.cn/problem/P3768  省选/NOI−  P3768 简单的数学题  考点：数论、莫比乌斯反演、整除分块
 *   https://codeforces.com/problemset/problem/792/E  CF2500  CF792E Colored Balls  考点：贪心、数学、数论
 *
 */

// 数论分块（整除分块）：floor(n / i)（i = 1..n）只有 O(√n) 种不同的取值，
// 而且取值相同的 i 构成连续的一段 [l, r]，其中 r = n / (n / l)。逐段处理即可 O(√n)。

// 1. 枚举每一段：f(l, r, q) 表示对 i ∈ [l, r]，n / i 都等于 q
template <class F>
void for_each_block(ll n, F f) {
    for (ll l = 1, r; l <= n; l = r + 1) {
        ll q = n / l;
        r = n / q;
        f(l, r, q);
    }
}

//    例：Σ_{i=1}^{n} floor(n / i)
ll sum_floor(ll n) {
    ll s = 0;
    for_each_block(n, [&](ll l, ll r, ll q) { s += (r - l + 1) * q; });
    return s;
}

// 2. 例（洛谷 P2261）：Σ_{i=1}^{n} (k mod i)。k mod i = k - i · floor(k / i)，
//    对 i <= min(n, k) 按 floor(k / i) 分块，每段内是等差数列求和
ll sum_mod(ll n, ll k) {
    ll s = n * k, lim = min(n, k);
    for (ll l = 1, r; l <= lim; l = r + 1) {
        ll q = k / l;
        r = min(k / q, lim);
        s -= q * (l + r) * (r - l + 1) / 2;
    }
    return s;
}

// 3. 二维分块：同时对 floor(n / i) 和 floor(m / i) 分块，段的右端点取两者的较小值
template <class F>
void for_each_block2(ll n, ll m, F f) {
    for (ll l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        f(l, r, n / l, m / l);
    }
}
