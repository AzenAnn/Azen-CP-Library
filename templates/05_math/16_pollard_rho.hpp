/**
 * 05_math/16 Miller-Rabin 与 Pollard-Rho
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：05_math/03 素数、筛法与分解质因数
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Miller-Rabin 素性测试
 *   2. Pollard-Rho 分解大数
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/pollard-rho/
 *   cp-algorithms  https://cp-algorithms.com/algebra/primality_tests.html
 *   cp-algorithms  https://cp-algorithms.com/algebra/factorization.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4718  P4718 【模板】Pollard-Rho
 *   https://judge.yosupo.jp/problem/factorize  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1075  普及−  P1075 [NOIP 2012 普及组] 质因数分解  热身：试除法分解质因数
 *   https://codeforces.com/problemset/problem/1033/D  CF2000  CF1033D Divisors  大数分解：开方判断 + 两两 gcd
 *   https://www.luogu.com.cn/problem/P4358  省选/NOI−  P4358 [CQOI2016] 密钥破解  RSA：用 Pollard-Rho 分解 N
 *   https://www.luogu.com.cn/problem/P4714  省选/NOI−  P4714 「数学」约数个数和  分解 n 后按各质因子指数计数
 *   https://www.luogu.com.cn/problem/P4464  NOI/NOI+/CTS  P4464 [国家集训队] JZPKIL  大数分解 + 积性函数
 *   https://www.luogu.com.cn/problem/P4607  NOI/NOI+/CTS  P4607 [SDOI2018] 反回文串  Pollard-Rho 分解 + 莫比乌斯反演
 *   https://www.luogu.com.cn/problem/P5285  NOI/NOI+/CTS  P5285 [十二省联考 2019] 骗分过样例  部分子任务要 Miller-Rabin / Pollard-Rho
 *   https://codeforces.com/problemset/problem/1091/G  CF3200  CF1091G New Year and the Factorisation Collaboration  交互：借助模平方根分解大数
 *
 */

// 64 位整数的素性测试与质因数分解。乘法用 __int128 防止溢出
using u64 = unsigned long long;
u64 mul_mod(u64 a, u64 b, u64 m) { return (__uint128_t)a * b % m; }
u64 pow_mod(u64 a, u64 e, u64 m) {
    u64 r = 1;
    for (a %= m; e; e >>= 1, a = mul_mod(a, a, m))
        if (e & 1) r = mul_mod(r, a, m);
    return r;
}

// 1. Miller-Rabin：把 n - 1 写成 d · 2^s，对底数 a 检查 a^d ≡ 1，或某个 a^(d·2^r) ≡ -1。
//    用前 12 个质数作底数，对所有 64 位整数都是确定性的（不会误判）
bool is_prime_mr(u64 n) {
    if (n < 2) return false;
    static const u64 bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (u64 p : bases)
        if (n % p == 0) return n == p;
    u64 d = n - 1;
    int s = 0;
    while (d % 2 == 0) d /= 2, s++;
    for (u64 a : bases) {
        u64 x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (int r = 1; r < s && !ok; r++) {
            x = mul_mod(x, x, n);
            ok = x == n - 1;
        }
        if (!ok) return false;
    }
    return true;
}

// 2. Pollard-Rho：用伪随机序列 x -> x^2 + c (mod n) 找环，期望 O(n^(1/4)) 找到 n 的一个非平凡因子。
//    Brent 判环，并把 128 次 |x - y| 乘起来再求一次 gcd，减少 gcd 的次数
u64 pollard_rho(u64 n) {
    if (n % 2 == 0) return 2;
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        u64 c = rng() % (n - 1) + 1, y = rng() % n, x = y, g = 1, q = 1, ys = y;
        auto f = [&](u64 v) { return (mul_mod(v, v, n) + c) % n; };
        for (u64 r = 1; g == 1; r <<= 1) {
            x = y;
            for (u64 i = 0; i < r; i++) y = f(y);
            for (u64 k = 0; k < r && g == 1; k += 128) {
                ys = y;
                for (u64 i = 0; i < 128 && i < r - k; i++) y = f(y), q = mul_mod(q, x > y ? x - y : y - x, n);
                g = __gcd(q, n);
            }
        }
        if (g == n) {   // 乘积把因子"乘没了"，退回去逐个求 gcd
            g = 1;
            while (g == 1) ys = f(ys), g = __gcd(x > ys ? x - ys : ys - x, n);
        }
        if (g != n) return g;
    }
}

// 3. 质因数分解：返回所有质因子（有重复，从小到大）
void factor_rec(u64 n, vector<u64> &res) {
    if (n == 1) return;
    if (is_prime_mr(n)) { res.push_back(n); return; }
    u64 d = pollard_rho(n);
    factor_rec(d, res), factor_rec(n / d, res);
}
vector<u64> factorize_big(u64 n) {
    vector<u64> res;
    for (u64 p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})   // 先除掉小因子
        while (n % p == 0) res.push_back(p), n /= p;
    factor_rec(n, res);
    sort(res.begin(), res.end());
    return res;
}
