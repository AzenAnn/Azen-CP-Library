/**
 * 05_math/16 FFT / NTT 多项式乘法
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：05_math/01 取模运算与快速幂
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. FFT（复数）
 *   2. NTT（模 998244353）
 *   3. 卷积的应用
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/poly/fft/
 *   OI-wiki        https://oi-wiki.org/math/poly/ntt/
 *   cp-algorithms  https://cp-algorithms.com/algebra/fft.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math_fft.go
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math_ntt.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3803  P3803 【模板】多项式乘法（FFT）
 *   https://judge.yosupo.jp/problem/convolution_mod  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/1342/E  CF2300  CF1342E Placing Rooks  考点：组合数学、FFT、数学
 *   https://codeforces.com/problemset/problem/2021/E1  CF2300  CF2021E1 Digital Village (Easy Version)  考点：暴力、数据结构、搜索
 *   https://codeforces.com/problemset/problem/2077/C  CF2300  CF2077C Binary Subsequence Value Sum  考点：组合数学、数据结构、DP
 *   https://codeforces.com/problemset/problem/300/D  CF2300  CF300D Painting Square  考点：DP、FFT
 *   https://codeforces.com/problemset/problem/993/E  CF2300  CF993E Nikita and Order Statistics  考点：中国剩余定理、FFT、数学
 *   https://www.luogu.com.cn/problem/P1919  省选/NOI−  P1919 【模板】高精度乘法 / A*B Problem 升级版  考点：高精度、分治、快速傅里叶变换 FFT
 *   https://www.luogu.com.cn/problem/P3338  省选/NOI−  P3338 [ZJOI2014] 力  考点：数学、快速傅里叶变换 FFT
 *   https://www.luogu.com.cn/problem/P4238  省选/NOI−  P4238 【模板】多项式乘法逆  考点：数学、递推、倍增
 *   https://www.luogu.com.cn/problem/P4721  省选/NOI−  P4721 【模板】分治 FFT  考点：多项式、分治、生成函数
 *   https://www.luogu.com.cn/problem/P4726  省选/NOI−  P4726 【模板】多项式指数函数（多项式 exp）  考点：数学、倍增、递归
 *   https://www.luogu.com.cn/problem/P4723  NOI/NOI+/CTS  P4723 【模板】常系数齐次线性递推  考点：递推、多项式、线性递推
 *   https://www.luogu.com.cn/problem/P5282  NOI/NOI+/CTS  P5282 【模板】快速阶乘算法  考点：数学、倍增、快速傅里叶变换 FFT
 *   https://www.luogu.com.cn/problem/P5828  NOI/NOI+/CTS  P5828 边双连通图计数  考点：数学、组合数学、容斥原理
 *   https://codeforces.com/problemset/problem/891/E  CF3000  CF891E Lust  考点：组合数学、数学、矩阵
 *   https://codeforces.com/problemset/problem/438/E  CF3100  CF438E The Child and Binary Tree  考点：组合数学、分治、FFT
 *
 */

// 多项式乘法（卷积）：c[k] = Σ_{i+j=k} a[i] · b[j]。朴素 O(n^2)，FFT / NTT 为 O(n log n)。
// 思路：多项式在 n 个点处的取值可以唯一确定它；把 a、b 变到"点值表示"后逐点相乘，再变回系数。
// 选单位根作取值点，就可以用分治在 O(n log n) 内完成变换。

// 1. FFT（复数）：适合结果不取模、且结果不超过约 1e15 的整数卷积（否则精度不够）
using cd = complex<double>;
void fft(vector<cd> &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {   // 位逆序置换
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * acos(-1.0) / len * (invert ? -1 : 1);
        cd wl(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v, a[i + j + len / 2] = u - v;
                w *= wl;
            }
        }
    }
    if (invert)
        for (cd &x : a) x /= n;
}
vector<ll> multiply_fft(const vector<ll> &a, const vector<ll> &b) {
    if (a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1, n = 1;
    while (n < need) n <<= 1;
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n), fb.resize(n);
    fft(fa, false), fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    vector<ll> c(need);
    for (int i = 0; i < need; i++) c[i] = llround(fa[i].real());
    return c;
}

// 2. NTT（模 998244353 = 119 · 2^23 + 1，原根 3）：用模意义下的单位根代替复数，没有精度问题。
//    结果对 998244353 取模，长度不超过 2^23
const ll NTT_MOD = 998244353, NTT_G = 3;
ll ntt_pow(ll a, ll e) {
    ll r = 1;
    for (a %= NTT_MOD; e; e >>= 1, a = a * a % NTT_MOD)
        if (e & 1) r = r * a % NTT_MOD;
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
        ll wl = ntt_pow(NTT_G, (NTT_MOD - 1) / len);
        if (invert) wl = ntt_pow(wl, NTT_MOD - 2);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i + j], v = a[i + j + len / 2] * w % NTT_MOD;
                a[i + j] = u + v < NTT_MOD ? u + v : u + v - NTT_MOD;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + NTT_MOD;
                w = w * wl % NTT_MOD;
            }
        }
    }
    if (invert) {
        ll inv_n = ntt_pow(n, NTT_MOD - 2);
        for (ll &x : a) x = x * inv_n % NTT_MOD;
    }
}
vector<ll> multiply_ntt(vector<ll> a, vector<ll> b) {
    if (a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1, n = 1;
    while (n < need) n <<= 1;
    for (ll &x : a) x = (x % NTT_MOD + NTT_MOD) % NTT_MOD;
    for (ll &x : b) x = (x % NTT_MOD + NTT_MOD) % NTT_MOD;
    a.resize(n), b.resize(n);
    ntt(a, false), ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % NTT_MOD;
    ntt(a, true);
    a.resize(need);
    return a;
}

// 3. 常见应用：大整数乘法（每一位作为系数，乘完再进位）；计数问题中的卷积（如两组数的和为 k 的方案数）
