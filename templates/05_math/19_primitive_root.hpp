/**
 * 05_math/19 阶与原根
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：05_math/07 欧拉函数与欧拉定理、05_math/01 取模运算与快速幂
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 阶的定义：使 a^d ≡ 1 (mod p) 的最小正整数 d，记 ord_p(a)，d | φ(p)
 *   2. 原根：ord_p(g) = φ(p) 的 g；p, 2p, p^k, 2p^k（p 奇素数）存在原根
 *   3. 求原根：找最小原根（试除 + 检验 φ(p) 的素因子）
 *   4. 应用：离散对数、指标法（原根将乘法化为加法）、NTT 模数
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/primitive-root/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P6091  P6091 【模板】原根
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P11961  提高  P11961 [GESP202503 五级] 原根判断  考点：原根、数论
 *   https://www.luogu.com.cn/problem/P10664  省选/NOI−  P10664 BZOJ3328 PYXFIB  考点：原根、数论、矩阵乘法
 *   https://www.luogu.com.cn/problem/P11175  省选/NOI−  P11175 【模板】基于值域预处理的快速离散对数  考点：原根、数学、数论
 *   https://www.luogu.com.cn/problem/P12694  省选/NOI−  P12694 BZOJ2219 数论之神  考点：原根、中国剩余定理 CRT、大步小步算法 BSGS
 *   https://www.luogu.com.cn/problem/P3599  省选/NOI−  P3599 Koishi Loves Construction  考点：原根、数学、逆元
 *   https://www.luogu.com.cn/problem/P5605  省选/NOI−  P5605 小 A 与两位神仙  考点：原根、数论
 *   https://www.luogu.com.cn/problem/P5668  NOI/NOI+/CTS  P5668 【模板】N 次剩余  考点：原根、数学、数论
 *
 */

// 阶与原根。ord_m(a)：使 a^d ≡ 1 (mod m) 的最小正整数 d（要求 gcd(a, m) = 1），一定整除 φ(m)。
// 原根 g：ord_m(g) = φ(m)。只有 m = 1, 2, 4, p^k, 2p^k（p 为奇质数）有原根，个数为 φ(φ(m))。
// 判定：g 是原根 ⇔ 对 φ(m) 的每个质因子 q，g^{φ(m)/q} ≠ 1。最小原根通常很小，直接从 1 往上试。
struct PrimRoot {
    static ll pw(ll a, ll e, ll m) {
        ll r = 1 % m;
        for (a %= m; e; e >>= 1, a = (__int128)a * a % m)
            if (e & 1) r = (__int128)r * a % m;
        return r;
    }
    static vector<ll> prime_factors(ll x) {
        vector<ll> f;
        for (ll i = 2; i * i <= x; i++)
            if (x % i == 0) {
                f.push_back(i);
                while (x % i == 0) x /= i;
            }
        if (x > 1) f.push_back(x);
        return f;
    }
    static ll euler_phi(ll m) {
        ll r = m;
        for (ll p : prime_factors(m)) r = r / p * (p - 1);
        return r;
    }
    // 1. a 模 m 的阶（gcd(a, m) ≠ 1 时返回 -1）。O(√m + log² m)
    static ll order(ll a, ll m) {
        if (__gcd(((a % m) + m) % m, m) != 1) return -1;
        ll d = euler_phi(m);
        for (ll q : prime_factors(d))
            while (d % q == 0 && pw(a, d / q, m) == 1) d /= q;
        return d;
    }
    static bool has_root(ll m) {
        if (m == 1 || m == 2 || m == 4) return true;
        if (m % 4 == 0) return false;
        if (m % 2 == 0) m /= 2;
        return prime_factors(m).size() == 1 && m % 2 == 1;
    }
    // 2. 最小原根，没有原根返回 -1
    static ll min_root(ll m) {
        if (!has_root(m)) return -1;
        if (m <= 2) return m - 1 == 0 ? 0 : 1;   // m = 1 时约定为 0，m = 2 时为 1
        ll ph = euler_phi(m);
        auto qs = prime_factors(ph);
        for (ll g = 1;; g++) {
            if (__gcd(g, m) != 1) continue;
            bool ok = true;
            for (ll q : qs)
                if (pw(g, ph / q, m) == 1) { ok = false; break; }
            if (ok) return g;
        }
    }
    // 3. 全部原根（升序）：g^k 是原根 ⇔ gcd(k, φ(m)) = 1
    static vector<ll> all_roots(ll m) {
        ll g = min_root(m);
        if (g < 0) return {};
        if (m <= 2) return {g};
        ll ph = euler_phi(m);
        vector<ll> r;
        ll cur = 1;
        for (ll k = 1; k <= ph; k++) {
            cur = (__int128)cur * g % m;
            if (__gcd(k, ph) == 1) r.push_back(cur);
        }
        sort(r.begin(), r.end());
        return r;
    }
};
