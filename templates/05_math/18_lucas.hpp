/**
 * 05_math/18 Lucas 定理与扩展 Lucas
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：05_math/05 组合数与计数原理
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Lucas 定理：C(n, m) mod p = Π C(ni, mi) mod p（p 为素数，n, m 按 p 进制展开）
 *   2. 预处理 p 以内的阶乘与逆元，O(p + log_p n) 查询
 *   3. 扩展 Lucas：模数为合数 → CRT 分解为素数幂，分别计算后合并
 *   4. 素数幂模组合数：去除 p 因子后计算
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/lucas/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3807  P3807 【模板】卢卡斯定理 / Lucas 定理
 *   https://www.luogu.com.cn/problem/P4720  P4720 【模板】扩展卢卡斯定理 / exLucas
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2606  提高  P2606 [ZJOI2010] 排列计数  考点：Lucas 定理、动态规划 DP、数学
 *   https://www.luogu.com.cn/problem/P2675  提高  P2675 《瞿葩的数字游戏》T3-三角圣地  考点：Lucas 定理、数学、贪心
 *   https://www.luogu.com.cn/problem/P3773  提高+/省选−  P3773 [CTSC2017] 吉夫特  考点：Lucas 定理、递归、枚举
 *   https://www.luogu.com.cn/problem/P2183  省选/NOI−  P2183 [国家集训队] 礼物  考点：Lucas 定理、数学、中国剩余定理 CRT
 *   https://www.luogu.com.cn/problem/P2480  省选/NOI−  P2480 [SDOI2010] 古代猪文  考点：Lucas 定理、数学、素数判断
 *   https://www.luogu.com.cn/problem/P4345  省选/NOI−  P4345 [SHOI2015] 超能粒子炮·改  考点：Lucas 定理、数学、数位 DP
 *   https://www.luogu.com.cn/problem/P5376  省选/NOI−  P5376 [THUPC 2019] 过河卒二  考点：Lucas 定理、组合数学、排列组合
 *   https://www.luogu.com.cn/problem/P6669  省选/NOI−  P6669 [清华集训 2016] 组合数问题  考点：Lucas 定理、数位 DP
 *   https://www.luogu.com.cn/problem/P8688  省选/NOI−  P8688 [蓝桥杯 2019 省 A] 组合数问题  考点：Lucas 定理、数位 DP
 *
 */

// Lucas 定理与扩展 Lucas。用 struct 的静态函数包起来，避免与其他模板重名。
// 1. lucas(n, m, p)：p 为质数（p ≤ 1e6 左右，每次调用 O(p) 预处理阶乘；多次询问时可把阶乘表提出来复用）。
//    C(n, m) mod p = C(n mod p, m mod p) · C(n / p, m / p) mod p
// 2. exlucas(n, m, M)：M 任意（不必是质数），把 M 分解成质数幂 p^k，分别求 C(n, m) mod p^k 再用 CRT 合并。
//    对 p^k：n! = p^{cnt} · (去掉 p 因子后的部分)，后者按 p^k 为周期递归计算。复杂度约 O(Σ p^k + log n)
struct ExLucas {
    static ll pw(ll a, ll e, ll m) {
        ll r = 1 % m;
        for (a %= m; e; e >>= 1, a = (__int128)a * a % m)
            if (e & 1) r = (__int128)r * a % m;
        return r;
    }
    static ll exgcd(ll a, ll b, ll &x, ll &y) {
        if (!b) return x = 1, y = 0, a;
        ll d = exgcd(b, a % b, y, x);
        y -= a / b * x;
        return d;
    }
    static ll inv(ll a, ll m) {   // a 与 m 互质
        ll x, y;
        exgcd(a % m, m, x, y);
        return (x % m + m) % m;
    }
    static ll lucas(ll n, ll m, ll p) {
        if (m < 0 || m > n) return 0;
        vector<ll> f(p, 1);
        for (ll i = 1; i < p; i++) f[i] = f[i - 1] * i % p;
        ll r = 1 % p;
        while (m > 0 || n > 0) {
            ll a = n % p, b = m % p;
            if (b > a) return 0;
            r = r * f[a] % p * pw(f[b] * f[a - b] % p, p - 2, p) % p;
            n /= p, m /= p;
        }
        return r;
    }
    // n! 去掉所有 p 因子后 mod pk（pk = p^k），table 为 [0, pk) 内不含因子 p 的数的前缀积
    static ll fac_no_p(ll n, ll p, ll pk, const vector<ll> &table) {
        if (n == 0) return 1 % pk;
        ll r = pw(table[pk - 1], n / pk, pk) * table[n % pk] % pk;   // 每个完整周期贡献相同
        return r * fac_no_p(n / p, p, pk, table) % pk;               // p 的倍数提出 p 后递归
    }
    static ll comb_mod_pk(ll n, ll m, ll p, ll pk) {
        vector<ll> table(pk, 1);
        for (ll i = 1; i < pk; i++) table[i] = table[i - 1] * (i % p ? i : 1) % pk;
        ll cnt = 0;   // C(n, m) 中 p 的次数
        for (ll x = n; x; x /= p) cnt += x / p;
        for (ll x = m; x; x /= p) cnt -= x / p;
        for (ll x = n - m; x; x /= p) cnt -= x / p;
        ll a = fac_no_p(n, p, pk, table), b = fac_no_p(m, p, pk, table), c = fac_no_p(n - m, p, pk, table);
        return a * inv(b, pk) % pk * inv(c, pk) % pk * pw(p, cnt, pk) % pk;
    }
    static ll exlucas(ll n, ll m, ll M) {
        if (m < 0 || m > n) return 0;
        ll res = 0, mod = 1, x = M;   // CRT 逐个合并
        for (ll p = 2; p * p <= x || x > 1; p++) {
            if (p * p > x) p = x;   // 剩下的 x 是质数
            if (x % p) continue;
            ll pk = 1;
            while (x % p == 0) x /= p, pk *= p;
            ll r = comb_mod_pk(n, m, p, pk);
            // 合并 res (mod mod) 与 r (mod pk)：两模数互质
            ll t = (__int128)((r - res) % pk + pk) % pk * inv(mod % pk, pk) % pk;
            res += mod * t, mod *= pk;
            res %= mod;
        }
        return res % M;
    }
};
