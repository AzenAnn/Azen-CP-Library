/**
 * 05_math/25 多项式进阶（牛顿迭代、逆元/开方/ln/exp）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：05_math/17 FFT / NTT 多项式乘法
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 多项式求逆：牛顿迭代 G_{2n} = G_n(2 − F·G_n) mod x^{2n}
 *   2. 多项式除法 / 取模：翻转系数转求逆
 *   3. 多项式开方、ln、exp：求导积分 + 牛顿迭代
 *   4. 应用：生成函数卷积计数、分治 NTT、多点求值/插值
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/poly/elementary-func/
 *   OI-wiki        https://oi-wiki.org/math/poly/newton/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4238  P4238 【模板】多项式乘法逆
 *   https://www.luogu.com.cn/problem/P4725  P4725 【模板】多项式对数函数（多项式 ln）
 *   https://www.luogu.com.cn/problem/P4726  P4726 【模板】多项式指数函数（多项式 exp）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4245  省选/NOI−  P4245 【模板】任意模数多项式乘法  考点：任意模数：三模 NTT 或拆系数 FFT
 *   https://www.luogu.com.cn/problem/P4512  省选/NOI−  P4512 【模板】多项式除法  考点：多项式带余除法
 *   https://www.luogu.com.cn/problem/P4721  省选/NOI−  P4721 【模板】分治 FFT  考点：分治 FFT（或用多项式求逆）
 *   https://www.luogu.com.cn/problem/P5205  省选/NOI−  P5205 【模板】多项式开根  考点：多项式开根
 *   https://www.luogu.com.cn/problem/P5245  省选/NOI−  P5245 【模板】多项式快速幂  考点：多项式快速幂
 *   https://www.luogu.com.cn/problem/P4723  NOI/NOI+/CTS  P4723 【模板】常系数齐次线性递推  考点：常系数齐次线性递推：多项式取模
 *   https://www.luogu.com.cn/problem/P5050  NOI/NOI+/CTS  P5050 【模板】多项式多点求值  考点：多点求值：分治 + 多项式取模
 *   https://www.luogu.com.cn/problem/P5158  NOI/NOI+/CTS  P5158 【模板】多项式快速插值  考点：快速插值
 *
 */

// 多项式全家桶（模 998244353，原根 3）：乘法、求逆、除法与取模、求导积分、ln、exp、开根、快速幂。
// 全部放在 namespace poly 里，避免与 05_math/17 的 ntt 重名。多项式用 vector<ll> 表示，a[i] 为 x^i 的系数。
// 牛顿迭代：每次把精度从 x^k 翻倍到 x^{2k}，总复杂度 O(n log n)（exp、开根的常数较大）。
namespace poly {
const ll MOD = 998244353, G = 3;
ll pw(ll a, ll e) {
    ll r = 1;
    for (a %= MOD; e; e >>= 1, a = a * a % MOD)
        if (e & 1) r = r * a % MOD;
    return r;
}
void ntt(vector<ll> &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll w = pw(invert ? pw(G, MOD - 2) : G, (MOD - 1) / len);
        for (int i = 0; i < n; i += len) {
            ll wn = 1;
            for (int j = 0; j < len / 2; j++, wn = wn * w % MOD) {
                ll u = a[i + j], v = a[i + j + len / 2] * wn % MOD;
                a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
            }
        }
    }
    if (invert) {
        ll inv_n = pw(n, MOD - 2);
        for (ll &x : a) x = x * inv_n % MOD;
    }
}
vector<ll> mul(vector<ll> a, vector<ll> b) {
    if (a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1, n = 1;
    while (n < need) n <<= 1;
    if ((ll)a.size() * b.size() <= 4096) {   // 小规模直接算
        vector<ll> c(need, 0);
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < b.size(); j++) c[i + j] = (c[i + j] + a[i] * b[j]) % MOD;
        return c;
    }
    a.resize(n), b.resize(n);
    ntt(a, false), ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(need);
    return a;
}
vector<ll> trunc(vector<ll> a, int n) { return a.resize(n), a; }
// 1. 求逆：A·B ≡ 1 (mod x^n)，要求 a[0] ≠ 0。B ← B(2 − AB)
vector<ll> inv(const vector<ll> &a, int n) {
    vector<ll> b = {pw(a[0], MOD - 2)};
    for (int k = 1; k < n; k <<= 1) {
        vector<ll> t = mul(trunc(a, 2 * k), b);
        t = trunc(t, 2 * k);
        for (ll &x : t) x = (MOD - x) % MOD;
        t[0] = (t[0] + 2) % MOD;
        b = trunc(mul(b, t), 2 * k);
    }
    return trunc(b, n);
}
// 2. 带余除法：a = q·b + r，deg r < deg b（b 的最高次系数非零）。返回 {q, r}
pair<vector<ll>, vector<ll>> divmod(vector<ll> a, vector<ll> b) {
    int n = a.size(), m = b.size();
    if (n < m) return {{0}, a};
    vector<ll> ra(a.rbegin(), a.rend()), rb(b.rbegin(), b.rend());
    vector<ll> q = trunc(mul(trunc(ra, n - m + 1), inv(rb, n - m + 1)), n - m + 1);
    reverse(q.begin(), q.end());
    vector<ll> r = trunc(mul(q, b), m - 1);
    for (int i = 0; i < m - 1; i++) r[i] = (a[i] - r[i] + MOD) % MOD;
    if (r.empty()) r = {0};
    return {q, r};
}
vector<ll> deriv(const vector<ll> &a) {
    vector<ll> r(max<int>(1, a.size() - 1), 0);
    for (size_t i = 1; i < a.size(); i++) r[i - 1] = a[i] * (ll)i % MOD;
    return r;
}
vector<ll> integ(const vector<ll> &a) {
    vector<ll> r(a.size() + 1, 0);
    for (size_t i = 0; i < a.size(); i++) r[i + 1] = a[i] * pw(i + 1, MOD - 2) % MOD;
    return r;
}
// 3. ln：要求 a[0] = 1。ln A = ∫ A' / A
vector<ll> ln(const vector<ll> &a, int n) { return trunc(integ(trunc(mul(deriv(trunc(a, n)), inv(a, n)), n - 1)), n); }
// 4. exp：要求 a[0] = 0。B ← B(1 − ln B + A)
vector<ll> exp(const vector<ll> &a, int n) {
    vector<ll> b = {1};
    for (int k = 1; k < n; k <<= 1) {
        vector<ll> t = ln(b, 2 * k);
        for (int i = 0; i < 2 * k; i++) t[i] = ((i < (int)a.size() ? a[i] : 0) - t[i] + MOD) % MOD;
        t[0] = (t[0] + 1) % MOD;
        b = trunc(mul(b, t), 2 * k);
    }
    return trunc(b, n);
}
// 5. 开根：要求 a[0] = 1（否则需要二次剩余）。B ← (B + A/B) / 2
vector<ll> sqrt(const vector<ll> &a, int n) {
    vector<ll> b = {1};
    ll inv2 = (MOD + 1) / 2;
    for (int k = 1; k < n; k <<= 1) {
        vector<ll> t = trunc(mul(trunc(a, 2 * k), inv(b, 2 * k)), 2 * k);
        b.resize(2 * k);
        for (int i = 0; i < 2 * k; i++) b[i] = (b[i] + t[i]) * inv2 % MOD;
    }
    return trunc(b, n);
}
// 6. 快速幂：A^k mod x^n，要求 a[0] = 1（一般情况先提出最低次项）。A^k = exp(k ln A)
vector<ll> pow(const vector<ll> &a, ll k, int n) {
    vector<ll> l = ln(a, n);
    for (ll &x : l) x = x * (k % MOD) % MOD;
    return exp(l, n);
}
}   // namespace poly
