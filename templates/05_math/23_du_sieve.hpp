/**
 * 05_math/23 杜教筛
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：05_math/14 莫比乌斯反演
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 目标：求积性函数前缀和 S(n) = Σ_{i≤n} f(i)，n ≤ 1e10
 *   2. 核心：构造 g 使 (f*g) 易求，S(n) = (Σ_{i≤n}(f*g)(i) − Σ_{d≥2} g(d)S(n/d)) / g(1)
 *   3. 数论分块 + 记忆化：不同 ⌊n/i⌋ 只有 O(√n) 个
 *   4. 预处理前 n^{2/3}，复杂度 O(n^{2/3})
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/hyperbola/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4213  P4213 【模板】杜教筛
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3768  省选/NOI−  P3768 简单的数学题  考点：杜教筛、数论、莫比乌斯反演
 *   https://www.luogu.com.cn/problem/P4318  省选/NOI−  P4318 完全平方数  考点：杜教筛、二分、素数判断
 *   https://www.luogu.com.cn/problem/P5218  省选/NOI−  P5218 无聊的水题 II  考点：杜教筛、莫比乌斯反演、整除分块
 *   https://www.luogu.com.cn/problem/P6055  省选/NOI−  P6055 [RC-02] GCD  考点：杜教筛、数学
 *   https://www.luogu.com.cn/problem/P6860  省选/NOI−  P6860 象棋与马  考点：杜教筛、莫比乌斯反演、Bézout 定理
 *   https://www.luogu.com.cn/problem/P1587  NOI/NOI+/CTS  P1587 [NOI2016] 循环之美  考点：杜教筛、数学、莫比乌斯反演
 *
 */

// 杜教筛：在 O(n^{2/3}) 内求积性函数前缀和。以 φ 和 μ 为例：
//   Σ_{d|n} φ(d) = n  ⇒  S_φ(n) = n(n+1)/2 − Σ_{i=2}^{n} S_φ(⌊n/i⌋)
//   Σ_{d|n} μ(d) = [n = 1]  ⇒  S_μ(n) = 1 − Σ_{i=2}^{n} S_μ(⌊n/i⌋)
// 小于等于 lim（约 n^{2/3}）的部分线性筛预处理，更大的用整除分块 + 记忆化。
// 结果用 long long：S_φ(n) ≈ 3n²/π²，n ≤ 3e9 时不会溢出（再大请改用 __int128）。
struct DuSieve {
    ll lim;
    vector<ll> sphi, smu;   // 前缀和
    unordered_map<ll, ll> mphi, mmu;
    DuSieve(ll max_n) {
        lim = max<ll>(10, (ll)pow((double)max_n, 2.0 / 3) + 1);
        vector<int> phi(lim + 1), mu(lim + 1), pr;
        vector<char> comp(lim + 1, 0);
        phi[1] = mu[1] = 1;
        for (ll i = 2; i <= lim; i++) {
            if (!comp[i]) pr.push_back(i), phi[i] = i - 1, mu[i] = -1;
            for (int p : pr) {
                if (i * p > lim) break;
                comp[i * p] = 1;
                if (i % p == 0) {
                    phi[i * p] = phi[i] * p, mu[i * p] = 0;
                    break;
                }
                phi[i * p] = phi[i] * (p - 1), mu[i * p] = -mu[i];
            }
        }
        sphi.assign(lim + 1, 0), smu.assign(lim + 1, 0);
        for (ll i = 1; i <= lim; i++) sphi[i] = sphi[i - 1] + phi[i], smu[i] = smu[i - 1] + mu[i];
    }
    ll sum_phi(ll n) {
        if (n <= lim) return sphi[n];
        auto it = mphi.find(n);
        if (it != mphi.end()) return it->second;
        ll r = (n % 2 == 0) ? (n / 2) * (n + 1) : n * ((n + 1) / 2);
        for (ll l = 2, rr; l <= n; l = rr + 1) {
            rr = n / (n / l);
            r -= (rr - l + 1) * sum_phi(n / l);
        }
        return mphi[n] = r;
    }
    ll sum_mu(ll n) {
        if (n <= lim) return smu[n];
        auto it = mmu.find(n);
        if (it != mmu.end()) return it->second;
        ll r = 1;
        for (ll l = 2, rr; l <= n; l = rr + 1) {
            rr = n / (n / l);
            r -= (rr - l + 1) * sum_mu(n / l);
        }
        return mmu[n] = r;
    }
};
