/**
 * 05_math/07 欧拉函数与欧拉定理
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：05_math/03 素数、筛法与分解质因数
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. φ(n) 的单点计算
 *   2. 线性筛求 φ
 *   3. 欧拉定理与扩展欧拉定理降幂
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/euler-totient/
 *   OI-wiki        https://oi-wiki.org/math/number-theory/fermat/
 *   cp-algorithms  https://cp-algorithms.com/algebra/phi-function.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2158  P2158 [SDOI2008] 仪仗队
 *   https://www.luogu.com.cn/problem/P5091  P5091 【模板】扩展欧拉定理
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P14640  普及  P14640 【OIMO Round 1】校验  考点：数学、欧拉函数
 *   https://www.luogu.com.cn/problem/P16634  普及  P16634 [GKS 2017 #G] Huge Numbers  考点：数学、数论、欧拉降幂
 *   https://www.luogu.com.cn/problem/P10414  普及+/提高−  P10414 [蓝桥杯 2023 国 A] 2023 次方  考点：欧拉降幂
 *   https://www.luogu.com.cn/problem/P12216  普及+/提高−  P12216 [蓝桥杯 2023 国 Java B] 互质  考点：数学、数论、欧拉函数
 *   https://www.luogu.com.cn/problem/P13880  普及+/提高−  P13880 [蓝桥杯 2023 省 Java A] 互质数的个数  考点：数论、欧拉函数
 *   https://www.luogu.com.cn/problem/P5746  普及+/提高−  P5746 [NOI2002] 机器人M号  考点：动态规划 DP、数学、欧拉函数
 *   https://codeforces.com/problemset/problem/1009/D  CF1700  CF1009D Relatively Prime Graph  考点：暴力、构造、图论
 *   https://www.luogu.com.cn/problem/P1390  提高  P1390 公约数的和  考点：数学、数论、莫比乌斯反演
 *   https://www.luogu.com.cn/problem/P2303  提高  P2303 [SDOI2012] Longge 的问题  考点：数学、欧拉函数
 *   https://www.luogu.com.cn/problem/P2398  提高  P2398 GCD SUM  考点：素数判断、莫比乌斯反演、容斥原理
 *   https://www.luogu.com.cn/problem/P2568  提高  P2568 GCD  考点：素数判断、前缀和、欧拉函数
 *   https://codeforces.com/problemset/problem/615/D  CF2000  CF615D Multipliers  考点：数学、数论
 *   https://www.luogu.com.cn/problem/P1891  提高+/省选−  P1891 疯狂 LCM  考点：数学、欧拉函数
 *   https://www.luogu.com.cn/problem/P3747  提高+/省选−  P3747 [六省联考 2017] 相逢是问候  考点：数学、线段树、并查集
 *   https://www.luogu.com.cn/problem/P4139  提高+/省选−  P4139 上帝与集合的正确用法  考点：数学、递归、数论
 *
 */

// 欧拉函数 φ(n)：1..n 中与 n 互质的数的个数。n = Π p^k 时，φ(n) = n · Π (1 - 1/p)

// 1. 单个 φ(n)：试除分解质因数，O(√n)
ll phi(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p) continue;
        while (n % p == 0) n /= p;
        res -= res / p;
    }
    if (n > 1) res -= res / n;
    return res;
}

// 2. 线性筛求 1..n 的 φ，O(n)
//    i % p == 0 时 φ(i·p) = φ(i)·p；否则 φ(i·p) = φ(i)·(p - 1)
vector<int> phi_sieve(int n) {
    vector<int> ph(n + 1), primes;
    vector<bool> comp(n + 1, false);
    if (n >= 1) ph[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!comp[i]) primes.push_back(i), ph[i] = i - 1;
        for (int p : primes) {
            if ((ll)i * p > n) break;
            comp[i * p] = true;
            if (i % p == 0) { ph[i * p] = ph[i] * p; break; }
            ph[i * p] = ph[i] * (p - 1);
        }
    }
    return ph;
}

// 3. 欧拉定理：gcd(a, m) = 1 时 a^φ(m) ≡ 1 (mod m)，所以 a^b ≡ a^(b mod φ(m))。
//    扩展欧拉定理（不要求互质）：b >= φ(m) 时 a^b ≡ a^(b mod φ(m) + φ(m)) (mod m)；b < φ(m) 时直接算。
//    用于指数 b 非常大（以字符串给出）的情况（洛谷 P5091）
ll pow_big_exponent(ll a, const string &b, ll m) {
    ll ph = phi(m), e = 0;
    bool big = false;   // b 是否 >= φ(m)
    for (char c : b) {
        e = e * 10 + (c - '0');
        if (e >= ph) big = true, e %= ph;
    }
    if (big) e += ph;
    ll r = 1 % m;
    a %= m;
    for (; e; e >>= 1, a = (__int128)a * a % m)
        if (e & 1) r = (__int128)r * a % m;
    return r;
}
