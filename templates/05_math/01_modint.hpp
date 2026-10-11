/**
 * 05_math/01 取模运算与快速幂
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 取模的运算规则与负数处理
 *   2. 快速幂
 *   3. modint 封装
 *   4. __int128 防溢出乘法
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/binary-exponentiation/
 *   cp-algorithms  https://cp-algorithms.com/algebra/binary-exp.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math_basic.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1226  P1226 【模板】快速幂
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/913/A  CF900  CF913A Modular Exponentiation  注意是 m mod 2^n，别真的去算 2^n
 *   https://www.luogu.com.cn/problem/P10446  普及−  P10446 64位整数乘法  龟速乘或 __int128 防溢出
 *   https://www.luogu.com.cn/problem/P1965  普及−  P1965 [NOIP 2013 提高组] 转圈游戏  10^k 次方取模，快速幂
 *   https://codeforces.com/problemset/problem/2025/B  CF1100  CF2025B Binomial Coefficients, Kind Of  找规律后答案是 2 的幂
 *   https://www.luogu.com.cn/problem/P1313  普及  P1313 [NOIP 2011 提高组] 计算系数  二项式系数 + 快速幂
 *   https://www.luogu.com.cn/problem/P1630  普及  P1630 求和  按模的周期分组 + 快速幂
 *   https://www.luogu.com.cn/problem/P3197  普及  P3197 [HNOI2008] 越狱  补集计数 + 快速幂
 *   https://codeforces.com/problemset/problem/1514/B  CF1200  CF1514B AND 0, Sum Big  答案是 n^k 取模
 *   https://www.luogu.com.cn/problem/P2044  普及+/提高−  P2044 [NOI2012] 随机数生成器  矩阵快速幂 + 龟速乘
 *   https://codeforces.com/problemset/problem/1236/B  CF1500  CF1236B Alice and the List of Presents  (2^m - 1)^n 取模
 *   https://codeforces.com/problemset/problem/630/I  CF1700  CF630I Parking Lot  计数后用快速幂
 *
 */

// 1. 取模规则：加法、乘法可以边算边取模；减法后要 (x % m + m) % m 防止出现负数；
//    除法不能直接取模，要乘逆元（见 05_math/04）。两个 1e9 级别的数相乘要先转 ll。

// 2. 快速幂：a^e mod m，O(log e)。用 __int128 做乘法，m 接近 1e18 也不会溢出
ll qpow(ll a, ll e, ll m) {
    ll r = 1 % m;
    a %= m;
    if (a < 0) a += m;
    for (; e; e >>= 1, a = (__int128)a * a % m)
        if (e & 1) r = (__int128)r * a % m;
    return r;
}

// 3. modint：模数为编译期常量的取模整数，写起来和普通整数一样
//    using mint = ModInt<998244353>;   mint x = 5;  x = x * 3 - 1;  x.inv();  cout << x;
//    要求 MOD < 2^30 左右，除法要求 MOD 为质数
template <int MOD>
struct ModInt {
    int v;
    ModInt(ll x = 0) {
        x %= MOD;
        if (x < 0) x += MOD;
        v = x;
    }
    ModInt &operator+=(ModInt o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
    ModInt &operator-=(ModInt o) { v -= o.v; if (v < 0) v += MOD; return *this; }
    ModInt &operator*=(ModInt o) { v = (ll)v * o.v % MOD; return *this; }
    ModInt &operator/=(ModInt o) { return *this *= o.inv(); }
    ModInt pow(ll e) const {
        ModInt r = 1, a = *this;
        for (; e; e >>= 1, a *= a)
            if (e & 1) r *= a;
        return r;
    }
    ModInt inv() const { return pow(MOD - 2); }   // 费马小定理
    ModInt operator-() const { return ModInt(0) - *this; }
    friend ModInt operator+(ModInt a, ModInt b) { return a += b; }
    friend ModInt operator-(ModInt a, ModInt b) { return a -= b; }
    friend ModInt operator*(ModInt a, ModInt b) { return a *= b; }
    friend ModInt operator/(ModInt a, ModInt b) { return a /= b; }
    friend bool operator==(ModInt a, ModInt b) { return a.v == b.v; }
    friend bool operator!=(ModInt a, ModInt b) { return a.v != b.v; }
    friend ostream &operator<<(ostream &os, ModInt a) { return os << a.v; }
    friend istream &operator>>(istream &is, ModInt &a) { ll x; is >> x; a = ModInt(x); return is; }
};
using mint = ModInt<998244353>;   // 或 ModInt<1000000007>
