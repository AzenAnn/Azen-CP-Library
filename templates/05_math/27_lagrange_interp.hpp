/**
 * 05_math/27 拉格朗日插值
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：05_math/02 GCD 与扩展欧几里得、05_math/04 乘法逆元
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 插值公式：f(x) = Σ y_i · Π_{j≠i} (x − x_j)/(x_i − x_j)
 *   2. n 个点确定次数 < n 的多项式；单点求值 O(n²)
 *   3. 横坐标连续（x_i = i）时：前缀积/后缀积优化到 O(n)
 *   4. 应用：自然数幂和、DP 转多项式后单点求值
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/numerical/interp/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4781  P4781 【模板】拉格朗日插值
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P5553  普及+/提高−  P5553 电学实验  考点：拉格朗日插值法、数学
 *   https://www.luogu.com.cn/problem/P4463  省选/NOI−  P4463 [集训队互测 2012] calc  考点：DP 结果是多项式：插值求单点
 *   https://www.luogu.com.cn/problem/P4593  省选/NOI−  P4593 [TJOI2018] 教科书般的亵渎  考点：自然数幂和：拉格朗日插值
 *   https://www.luogu.com.cn/problem/P5667  省选/NOI−  P5667 拉格朗日插值2  考点：拉格朗日插值法、快速傅里叶变换 FFT、快速数论变换 NTT
 *   https://www.luogu.com.cn/problem/P7116  省选/NOI−  P7116 [NOIP2020] 微信步数  考点：拉格朗日插值法、动态规划 DP
 *   https://www.luogu.com.cn/problem/P8290  省选/NOI−  P8290 [省选联考 2022] 填树  考点：拉格朗日插值法、数学、树形 DP
 *   https://codeforces.com/problemset/problem/622/F  CF2600  CF622F The Sum of the k-th Powers  考点：自然数幂和 Σi^k：k+2 个点插值
 *
 */

// 拉格朗日插值（模质数 p）：n 个点唯一确定一个次数 < n 的多项式。
// 1. lagrange_eval：任意 n 个点（横坐标互不相同），求 f(x)，O(n²)
// 2. lagrange_consecutive：横坐标为 0, 1, …, n−1，用前缀积 / 后缀积 O(n) 求 f(x)（x 可以很大）
// 3. power_sum(n, k)：1^k + 2^k + … + n^k 是 n 的 k+1 次多项式，取 k+2 个点插值，O(k log p)
ll lag_pow(ll a, ll e, ll p) {
    ll r = 1 % p;
    for (a = (a % p + p) % p; e; e >>= 1, a = a * a % p)
        if (e & 1) r = r * a % p;
    return r;
}
ll lagrange_eval(const vector<ll> &xs, const vector<ll> &ys, ll x, ll p) {
    int n = xs.size();
    ll res = 0;
    x = (x % p + p) % p;
    for (int i = 0; i < n; i++) {
        ll num = 1, den = 1;
        for (int j = 0; j < n; j++)
            if (j != i) num = num * ((x - xs[j]) % p + p) % p, den = den * ((xs[i] - xs[j]) % p + p) % p;
        res = (res + ys[i] % p * num % p * lag_pow(den, p - 2, p)) % p;
    }
    return res;
}
ll lagrange_consecutive(const vector<ll> &ys, ll x, ll p) {
    int n = ys.size();
    if (x >= 0 && x < n) return ys[x] % p;
    x %= p;
    vector<ll> pre(n + 1, 1), suf(n + 1, 1), fac(n, 1);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] * ((x - i) % p + p) % p;
    for (int i = n - 1; i >= 0; i--) suf[i] = suf[i + 1] * ((x - i) % p + p) % p;
    for (int i = 1; i < n; i++) fac[i] = fac[i - 1] * i % p;
    ll res = 0;
    for (int i = 0; i < n; i++) {
        // 分母 = i! · (n−1−i)! · (−1)^{n−1−i}
        ll den = fac[i] * fac[n - 1 - i] % p;
        ll term = ys[i] % p * pre[i] % p * suf[i + 1] % p * lag_pow(den, p - 2, p) % p;
        res = ((n - 1 - i) % 2 ? res - term + p : res + term) % p;
    }
    return res;
}
ll power_sum(ll n, int k, ll p) {
    vector<ll> ys(k + 2, 0);
    for (int i = 1; i < k + 2; i++) ys[i] = (ys[i - 1] + lag_pow(i, k, p)) % p;
    return lagrange_consecutive(ys, n, p);
}
