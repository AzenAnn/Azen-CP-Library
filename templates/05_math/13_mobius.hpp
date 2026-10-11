/**
 * 05_math/13 莫比乌斯反演
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：05_math/11 数论分块（整除分块）、05_math/06 欧拉函数与欧拉定理
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 莫比乌斯函数与线性筛
 *   2. 反演公式
 *   3. gcd 求和类问题
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/mobius/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3455  P3455 [POI 2007] ZAP-Queries
 *   https://www.luogu.com.cn/problem/P2522  P2522 [HAOI2011] Problem b
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3172  省选/NOI−  P3172 [CQOI2015] 选数  考点：递推、最大公约数 gcd、莫比乌斯反演
 *   https://www.luogu.com.cn/problem/P3312  省选/NOI−  P3312 [SDOI2014] 数表  考点：树状数组、最大公约数 gcd、莫比乌斯反演
 *   https://www.luogu.com.cn/problem/P4213  省选/NOI−  P4213 【模板】杜教筛  考点：数学、数论、杜教筛
 *   https://www.luogu.com.cn/problem/P4318  省选/NOI−  P4318 完全平方数  考点：二分、素数判断、莫比乌斯反演
 *   https://www.luogu.com.cn/problem/P4449  省选/NOI−  P4449 于神之怒加强版  考点：数学、素数判断、莫比乌斯反演
 *   https://www.luogu.com.cn/problem/P6156  省选/NOI−  P6156 简单题  考点：莫比乌斯反演、分块、差分
 *   https://www.luogu.com.cn/problem/P6624  省选/NOI−  P6624 [省选联考 2020 A 卷] 作业题  考点：数学、矩阵树定理、多项式
 *   https://codeforces.com/problemset/problem/1043/F  CF2500  CF1043F Make It One  考点：位运算、组合数学、DP
 *   https://www.luogu.com.cn/problem/P1587  NOI/NOI+/CTS  P1587 [NOI2016] 循环之美  考点：数学、莫比乌斯反演、整除分块
 *   https://www.luogu.com.cn/problem/P3784  NOI/NOI+/CTS  P3784 [SDOI2017] 遗忘的集合  考点：莫比乌斯反演、生成函数、快速傅里叶变换 FFT
 *   https://www.luogu.com.cn/problem/P4240  NOI/NOI+/CTS  P4240 毒瘤之神的考验  考点：数学、莫队、数论
 *   https://www.luogu.com.cn/problem/P4619  NOI/NOI+/CTS  P4619 [SDOI2018] 旧试题  考点：数学、图论、枚举
 *   https://www.luogu.com.cn/problem/P4916  NOI/NOI+/CTS  P4916 [MtOI2018] 魔力环  考点：枚举、Pólya 定理、莫比乌斯反演
 *   https://www.luogu.com.cn/problem/P5572  NOI/NOI+/CTS  P5572 [CmdOI2019] 简单的数论题  考点：数学、数论、莫比乌斯反演
 *   https://www.luogu.com.cn/problem/P8570  NOI/NOI+/CTS  P8570 [JRKSJ R6] 牵连的世界  考点：素数判断、莫比乌斯反演
 *
 */

// 莫比乌斯函数 μ(n)：n 有平方因子时为 0；否则 n 是 k 个不同质数之积时为 (-1)^k。
// 核心性质：Σ_{d | n} μ(d) = [n == 1]。于是 [gcd(x, y) == 1] = Σ_{d | gcd(x, y)} μ(d)，
// 把"互质"的条件换成对 d 的求和，交换求和顺序后用数论分块计算。

// 1. 线性筛求 μ 和前缀和 pre[i] = μ(1) + ... + μ(i)
struct Mobius {
    vector<int> mu, primes;
    vector<ll> pre;
    Mobius(int n) : mu(n + 1, 0), pre(n + 1, 0) {
        vector<bool> comp(n + 1, false);
        if (n >= 1) mu[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (!comp[i]) primes.push_back(i), mu[i] = -1;
            for (int p : primes) {
                if ((ll)i * p > n) break;
                comp[i * p] = true;
                if (i % p == 0) { mu[i * p] = 0; break; }
                mu[i * p] = -mu[i];
            }
        }
        for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + mu[i];
    }
};

// 2. 满足 1 <= x <= a、1 <= y <= b、gcd(x, y) == k 的数对个数（洛谷 P3455）
//    令 x = kx'、y = ky'，变成 gcd(x', y') == 1，答案 = Σ_d μ(d) · floor(a'/d) · floor(b'/d)，用二维分块。
//    需要 mo 的范围 >= min(a, b) / k
ll count_gcd_eq(const Mobius &mo, ll a, ll b, ll k) {
    a /= k, b /= k;
    ll res = 0;
    for (ll l = 1, r; l <= min(a, b); l = r + 1) {
        r = min(a / (a / l), b / (b / l));
        res += (mo.pre[r] - mo.pre[l - 1]) * (a / l) * (b / l);
    }
    return res;
}

// 3. x 在 [a, b]、y 在 [c, d] 的版本（洛谷 P2522）用容斥：
//    f(b, d) - f(a - 1, d) - f(b, c - 1) + f(a - 1, c - 1)，其中 f(n, m) = count_gcd_eq(mo, n, m, k)
