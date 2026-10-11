/**
 * 05_math/03 素数、筛法与分解质因数
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 试除法判断素数
 *   2. 埃氏筛
 *   3. 线性筛（同时求最小质因子）
 *   4. 分解质因数
 *   5. 枚举约数 / 约数个数与约数和
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/prime/
 *   OI-wiki        https://oi-wiki.org/math/number-theory/sieve/
 *   cp-algorithms  https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
 *   cp-algorithms  https://cp-algorithms.com/algebra/prime-sieve-linear.html
 *   cp-algorithms  https://cp-algorithms.com/algebra/divisors.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3383  P3383 【模板】线性筛素数
 *   https://www.luogu.com.cn/problem/P1075  P1075 [NOIP 2012 普及组] 质因数分解
 *   https://judge.yosupo.jp/problem/enumerate_primes  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1304  入门  P1304 哥德巴赫猜想  考点：搜索、数学、素数判断
 *   https://www.luogu.com.cn/problem/P15894  入门  P15894 [TOPC 2025] Twin Guardians  考点：数学、素数判断
 *   https://www.luogu.com.cn/problem/P1036  普及−  P1036 [NOIP 2002 普及组] 选数  考点：搜索、深度优先搜索 DFS、剪枝
 *   https://www.luogu.com.cn/problem/P1125  普及−  P1125 [NOIP 2008 提高组] 笨小猴  考点：模拟、字符串、素数判断
 *   https://www.luogu.com.cn/problem/P1217  普及−  P1217 [USACO1.5] 回文质数 Prime Palindromes  考点：枚举、素数判断
 *   https://www.luogu.com.cn/problem/P5723  普及−  P5723 【深基4.例13】质数口袋  考点：枚举、素数判断
 *   https://codeforces.com/problemset/problem/1916/B  CF1000  CF1916B Two Divisors  考点：构造、数学、数论
 *   https://www.luogu.com.cn/problem/P1835  普及  P1835 素数密度  考点：数学、枚举、素数判断
 *   https://codeforces.com/problemset/problem/1076/B  CF1200  CF1076B Divisor Subtraction  考点：实现、数学、数论
 *   https://codeforces.com/problemset/problem/1372/B  CF1300  CF1372B Omkar and Last Class of Math  考点：贪心、数学、数论
 *   https://codeforces.com/problemset/problem/1881/D  CF1300  CF1881D Divide and Equalize  考点：数学、数论
 *   https://codeforces.com/problemset/problem/762/A  CF1400  CF762A k-th divisor  考点：数学、数论
 *   https://www.luogu.com.cn/problem/P1593  普及+/提高−  P1593 因子和  考点：数学、分治、逆元
 *   https://codeforces.com/problemset/problem/576/A  CF1500  CF576A Vasya and Petya's Game  考点：数学、数论
 *   https://codeforces.com/problemset/problem/735/D  CF1600  CF735D Taxes  考点：数学、数论
 *
 */

// 1. 试除法判断素数，O(√n)
bool is_prime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

// 2. 埃氏筛：is_p[i] 表示 i 是否为素数（0 <= i <= n），O(n log log n)
vector<bool> sieve_eratosthenes(int n) {
    vector<bool> is_p(n + 1, true);
    is_p[0] = false;
    if (n >= 1) is_p[1] = false;
    for (ll i = 2; i * i <= n; i++)
        if (is_p[i])
            for (ll j = i * i; j <= n; j += i) is_p[j] = false;
    return is_p;
}

// 3. 线性筛（欧拉筛）：每个合数只被它的最小质因子筛一次，O(n)
//    primes 为 [2, n] 内的全部质数，minp[x] 为 x 的最小质因子（x >= 2）
struct LinearSieve {
    vector<int> primes, minp;
    LinearSieve(int n) : minp(n + 1, 0) {
        for (int i = 2; i <= n; i++) {
            if (!minp[i]) minp[i] = i, primes.push_back(i);
            for (int p : primes) {
                if (p > minp[i] || (ll)i * p > n) break;
                minp[i * p] = p;
            }
        }
    }
    bool is_prime(int x) const { return x >= 2 && minp[x] == x; }
    // 借助最小质因子 O(log x) 分解 x（2 <= x <= n），返回 (质因子, 指数)
    vector<pair<int, int>> factorize(int x) const {
        vector<pair<int, int>> res;
        while (x > 1) {
            int p = minp[x], c = 0;
            while (x % p == 0) x /= p, c++;
            res.push_back({p, c});
        }
        return res;
    }
};

// 4. 试除法分解质因数，O(√n)，返回 (质因子, 指数)，质因子从小到大
vector<pair<ll, int>> factorize(ll n) {
    vector<pair<ll, int>> res;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p) continue;
        int c = 0;
        while (n % p == 0) n /= p, c++;
        res.push_back({p, c});
    }
    if (n > 1) res.push_back({n, 1});
    return res;
}

// 5. 枚举 n 的所有约数（从小到大），O(√n)
//    约数个数 = Π(e_i + 1)；约数和 = Π(1 + p_i + ... + p_i^e_i)
vector<ll> divisors(ll n) {
    vector<ll> small, large;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i) continue;
        small.push_back(i);
        if (i != n / i) large.push_back(n / i);
    }
    small.insert(small.end(), large.rbegin(), large.rend());
    return small;
}
