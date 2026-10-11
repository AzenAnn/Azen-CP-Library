/**
 * 05_math/05 组合数与计数原理
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：05_math/04 乘法逆元
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 预处理阶乘求 C(n,k)
 *   2. 杨辉三角递推
 *   3. Lucas 定理
 *   4. 隔板法与卡特兰数
 *   5. 容斥原理
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/combinatorics/combination/
 *   OI-wiki        https://oi-wiki.org/math/number-theory/lucas/
 *   OI-wiki        https://oi-wiki.org/math/combinatorics/catalan/
 *   OI-wiki        https://oi-wiki.org/math/combinatorics/inclusion-exclusion-principle/
 *   cp-algorithms  https://cp-algorithms.com/combinatorics/binomial-coefficients.html
 *   cp-algorithms  https://cp-algorithms.com/combinatorics/inclusion-exclusion.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math_comb.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3807  P3807 【模板】卢卡斯定理 / Lucas 定理
 *   https://www.luogu.com.cn/problem/P1350  P1350 车的放置
 *   https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/B3717  普及  B3717 组合数问题  考点：逆元
 *   https://www.luogu.com.cn/problem/P5520  普及  P5520 [yLOI2019] 青原樱  考点：动态规划 DP、数学、组合数学
 *   https://codeforces.com/problemset/problem/1879/C  CF1300  CF1879C Make it Alternating  考点：组合数学、DP、贪心
 *   https://codeforces.com/problemset/problem/617/B  CF1300  CF617B Chocolate  考点：组合数学
 *   https://codeforces.com/problemset/problem/1368/B  CF1500  CF1368B Codeforces Subsequences  考点：暴力、构造、贪心
 *   https://codeforces.com/problemset/problem/1391/C  CF1500  CF1391C Cyclic Permutations   考点：组合数学、DP、图论
 *   https://codeforces.com/problemset/problem/1288/C  CF1600  CF1288C Two Arrays  考点：组合数学、DP
 *   https://codeforces.com/problemset/problem/1475/E  CF1600  CF1475E Advertising Agency  考点：组合数学、数学、排序
 *   https://www.luogu.com.cn/problem/P1450  提高  P1450 [HAOI2008] 硬币购物  考点：动态规划 DP、背包 DP、前缀和
 *   https://www.luogu.com.cn/problem/P2567  提高  P2567 [SCOI2010] 幸运数字  考点：深度优先搜索 DFS、剪枝、容斥原理
 *   https://www.luogu.com.cn/problem/P5505  提高  P5505 [JSOI2011] 分特产  考点：组合数学、容斥原理
 *   https://codeforces.com/problemset/problem/300/C  CF1800  CF300C Beautiful Numbers  考点：暴力、组合数学
 *   https://codeforces.com/problemset/problem/1359/E  CF2000  CF1359E Modular Stability  考点：组合数学、数学、数论
 *   https://codeforces.com/problemset/problem/1696/E  CF2000  CF1696E Placing Jinas  考点：组合数学、数学
 *   https://codeforces.com/problemset/problem/559/C  CF2200  CF559C Gerald and Giant Chess  考点：组合数学、DP、数学
 *
 */

// 1. 预处理阶乘和阶乘逆元：C(n, k) 每次 O(1)。要求 mod 为质数且 n < mod
struct Comb {
    ll mod;
    vector<ll> f, inv_f;
    Comb(int n, ll mod) : mod(mod), f(n + 1), inv_f(n + 1) {
        f[0] = 1;
        for (int i = 1; i <= n; i++) f[i] = f[i - 1] * i % mod;
        inv_f[n] = power(f[n], mod - 2);
        for (int i = n; i > 0; i--) inv_f[i - 1] = inv_f[i] * i % mod;
    }
    ll power(ll a, ll e) const {
        ll r = 1;
        for (a %= mod; e; e >>= 1, a = a * a % mod)
            if (e & 1) r = r * a % mod;
        return r;
    }
    ll C(int n, int k) const {   // 组合数，k < 0 或 k > n 时为 0
        if (k < 0 || k > n || n < 0) return 0;
        return f[n] * inv_f[k] % mod * inv_f[n - k] % mod;
    }
    ll A(int n, int k) const {   // 排列数
        if (k < 0 || k > n || n < 0) return 0;
        return f[n] * inv_f[n - k] % mod;
    }
    ll catalan(int n) const { return (C(2 * n, n) - C(2 * n, n + 1) + mod) % mod; }   // 需要 2n 以内的阶乘
};

// 2. 杨辉三角：C[i][j] = C[i-1][j-1] + C[i-1][j]，O(n^2)。n 较小或模数不是质数时用
vector<vector<ll>> pascal(int n, ll mod) {
    vector<vector<ll>> c(n + 1, vector<ll>(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        c[i][0] = 1 % mod;
        for (int j = 1; j <= i; j++) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }
    return c;
}

// 3. Lucas 定理：p 为较小的质数（预处理 O(p)），n、k 可以到 1e18
//    C(n, k) ≡ C(n % p, k % p) * C(n / p, k / p) (mod p)
struct Lucas {
    ll p;
    vector<ll> f, inv_f;
    Lucas(ll p) : p(p), f(p), inv_f(p) {
        f[0] = 1;
        for (ll i = 1; i < p; i++) f[i] = f[i - 1] * i % p;
        inv_f[p - 1] = p - 1;   // 威尔逊定理：(p-1)! ≡ -1，它的逆元也是 -1
        for (ll i = p - 1; i > 0; i--) inv_f[i - 1] = inv_f[i] * i % p;
    }
    ll small(ll n, ll k) const { return k > n ? 0 : f[n] * inv_f[k] % p * inv_f[n - k] % p; }
    ll C(ll n, ll k) const {
        if (k < 0 || k > n) return 0;
        ll res = 1;
        for (; k && res; n /= p, k /= p) res = res * small(n % p, k % p) % p;
        return res;
    }
};

// 4. 常用计数公式
//    隔板法：n 个相同的球放进 k 个盒子，每盒非空 C(n-1, k-1)，允许空盒 C(n+k-1, k-1)
//    卡特兰数 Cat(n) = C(2n, n) / (n+1) = C(2n, n) - C(2n, n+1)：括号序列、出栈序列、二叉树形态
// 5. 容斥原理：|A1 ∪ ... ∪ An| = Σ|Ai| - Σ|Ai ∩ Aj| + ...，常配合二进制枚举子集
