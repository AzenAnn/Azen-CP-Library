/**
 * 05_math/24 FWT（快速沃尔什变换）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：05_math/17 FFT / NTT 多项式乘法
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 位运算卷积：C[k] = Σ_{i⊕j=k} A[i]·B[j]，⊕ 为 or / and / xor
 *   2. xor 卷积：FWT(A)[i] = Σ (−1)^{popcount(i&j)} A[j]；正逆变换同构，逆变换除以 n
 *   3. or / and 卷积：子集/超集和变换，逆变换做差分
 *   4. 高维前缀和视角、子集卷积（SOS DP 关联）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/poly/fwt/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4717  P4717 【模板】快速莫比乌斯 / 沃尔什变换 (FMT / FWT)
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10242  提高  P10242 [THUSC 2021] Emiya 家明天的饭  考点：快速沃尔什变换 FWT、动态规划 DP、状压 DP
 *   https://codeforces.com/problemset/problem/449/D  CF2400  CF449D Jzzhu and Numbers  考点：高维前缀和（FMT）+ 容斥
 *   https://www.luogu.com.cn/problem/P3175  省选/NOI−  P3175 [HAOI2015] 按位或  考点：快速沃尔什变换 FWT、容斥原理、快速莫比乌斯变换 FMT
 *   https://www.luogu.com.cn/problem/P3349  省选/NOI−  P3349 [ZJOI2016] 小星星  考点：快速沃尔什变换 FWT、动态规划 DP、枚举
 *   https://www.luogu.com.cn/problem/P5933  省选/NOI−  P5933 [清华集训 2012] 串珠子  考点：快速莫比乌斯变换 FMT、快速沃尔什变换 FWT、集合幂级数，子集卷积
 *   https://www.luogu.com.cn/problem/P6097  省选/NOI−  P6097 【模板】子集卷积  考点：子集卷积：按 popcount 分层的 FMT
 *   https://www.luogu.com.cn/problem/P8292  省选/NOI−  P8292 [省选联考 2022] 卡牌  考点：快速沃尔什变换 FWT、容斥原理
 *   https://codeforces.com/problemset/problem/662/C  CF2600  CF662C Binary Table  考点：按列状态计数 + xor 卷积
 *   https://codeforces.com/problemset/problem/914/G  CF2600  CF914G Sum the Fibonacci  考点：or / and / xor 卷积与子集卷积综合
 *
 */

// 快速沃尔什变换（FWT / FMT）：位运算卷积 C[k] = Σ_{i op j = k} A[i]·B[j]，op 为 or / and / xor。
// 长度须为 2 的幂。变换、逐点相乘、逆变换，O(n log n)。结果对 p 取模（xor 的逆变换要除以 2，p 须为奇数）。
// or 变换 = 子集和（高维前缀和）；and 变换 = 超集和；xor 变换：FWT(A)[i] = Σ_j (−1)^{popcount(i & j)} A[j]。
void fwt_or(vector<ll> &a, ll p, bool inv) {
    int n = a.size();
    for (int len = 1; len < n; len <<= 1)
        for (int i = 0; i < n; i += 2 * len)
            for (int j = i; j < i + len; j++) a[j + len] = (a[j + len] + (inv ? p - a[j] : a[j])) % p;
}
void fwt_and(vector<ll> &a, ll p, bool inv) {
    int n = a.size();
    for (int len = 1; len < n; len <<= 1)
        for (int i = 0; i < n; i += 2 * len)
            for (int j = i; j < i + len; j++) a[j] = (a[j] + (inv ? p - a[j + len] : a[j + len])) % p;
}
void fwt_xor(vector<ll> &a, ll p, bool inv) {
    int n = a.size();
    for (int len = 1; len < n; len <<= 1)
        for (int i = 0; i < n; i += 2 * len)
            for (int j = i; j < i + len; j++) {
                ll x = a[j], y = a[j + len];
                a[j] = (x + y) % p, a[j + len] = (x - y + p) % p;
            }
    if (inv) {   // 逆变换 = 正变换后除以 n
        ll r = 1, b = (p + 1) / 2, e = __lg(max(n, 1));   // 1/2 的 e 次方（p 为奇数时 (p+1)/2 是 2 的逆元）
        while (e--) r = r * b % p;
        for (ll &x : a) x = x * r % p;
    }
}
// op：'|'、'&'、'^'。a、b 长度相同且为 2 的幂，元素在 [0, p) 内
vector<ll> fwt_convolve(vector<ll> a, vector<ll> b, char op, ll p) {
    auto tr = [&](vector<ll> &v, bool inv) {
        if (op == '|') fwt_or(v, p, inv);
        else if (op == '&') fwt_and(v, p, inv);
        else fwt_xor(v, p, inv);
    };
    tr(a, false), tr(b, false);
    for (size_t i = 0; i < a.size(); i++) a[i] = a[i] * b[i] % p;
    tr(a, true);
    return a;
}
