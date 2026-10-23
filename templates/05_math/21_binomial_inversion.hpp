/**
 * 05_math/21 二项式反演
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：05_math/05 组合数与计数原理、05_math/06 康托展开、错排与约瑟夫问题
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 形式一：g(n) = Σ_{i=0}^{n} C(n, i) f(i)  ⇔  f(n) = Σ_{i=0}^{n} (−1)^{n−i} C(n, i) g(i)
 *      例：错排。n! = Σ C(n, i) D(i)（先选哪些数不在原位），反演得到 D(n)
 *   2. 形式二（最常用，"至少 → 恰好"）：g(k) = Σ_{i≥k} C(i, k) f(i)  ⇔  f(k) = Σ_{i≥k} (−1)^{i−k} C(i, k) g(i)
 *      g(k) 是"钦定 k 个满足、其余随意"的方案数（好算），f(k) 是"恰好 k 个满足"（要求的）
 *   3. 套路：先 DP 出"钦定 k 个"的方案数（常再乘一个 (n−k)! 之类的随意部分），再反演
 *   4. 和容斥原理的关系：容斥就是 f(0)；反演一次给出所有 f(k)。需要时可以用卷积做到 O(n log n)
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/combinatorics/combination/
 *   OI-wiki        https://oi-wiki.org/math/combinatorics/inclusion-exclusion-principle/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P10596  P10596 BZOJ2839 集合计数
 *   https://www.luogu.com.cn/problem/P4859  P4859 已经没有什么好害怕的了
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4931  提高+/省选−  P4931 [MtOI2018] 情侣？给我烧了！（加强版）  考点：错排 + 组合计数
 *   https://codeforces.com/problemset/problem/1228/E  CF2300  CF1228E Another Filling the Grid  考点：每行每列至少一个 1：对行列容斥
 *   https://codeforces.com/problemset/problem/1342/E  CF2300  CF1342E Placing Rooks  考点：恰好 k 列被占用：二项式反演 / 第二类斯特林数
 *   https://www.luogu.com.cn/problem/P4491  省选/NOI−  P4491 [HAOI2018] 染色  考点：钦定 k 种颜色恰好出现 S 次，反演（NTT 加速）
 *   https://www.luogu.com.cn/problem/P5400  省选/NOI−  P5400 [CTS2019] 随机立方体  考点：钦定 k 个极大点，再二项式反演
 *   https://www.luogu.com.cn/problem/P6478  省选/NOI−  P6478 [NOI Online #2 提高组] 游戏  考点：树形背包求钦定 k 对，再二项式反演
 *
 */

// 组合数用杨辉三角逐行递推（模数不必是质数），时间 O(n^2)、额外空间 O(n)。
// 1. 形式一：已知 g(0..n)，g(x) = Σ_{i≤x} C(x, i) f(i)，求 f(0..n)。sign = -1 为反演，sign = +1 为正向变换
vector<ll> binom_transform_lower(const vector<ll> &g, ll m, int sign = -1) {
    int n = g.size();
    vector<ll> f(n, 0), row = {1 % m};   // row = 第 x 行的 C(x, 0..x)
    for (int x = 0; x < n; x++) {
        if (x) {
            row.push_back(0);
            for (int i = x; i > 0; i--) row[i] = (row[i] + row[i - 1]) % m;
        }
        ll s = 0;
        for (int i = 0; i <= x; i++) {
            ll t = row[i] * (g[i] % m) % m;
            s += (sign < 0 && (x - i) % 2) ? m - t : t;
        }
        f[x] = s % m;
    }
    return f;
}

// 2. 形式二（至少 → 恰好）：已知 g(0..n)，g(k) = Σ_{i≥k} C(i, k) f(i)，求 f(0..n)。sign = -1 为反演，+1 为正向变换
vector<ll> binom_transform_upper(const vector<ll> &g, ll m, int sign = -1) {
    int n = g.size();
    vector<ll> f(n, 0), row = {1 % m};   // 第 i 行贡献给 f(0..i)
    for (int i = 0; i < n; i++) {
        if (i) {
            row.push_back(0);
            for (int k = i; k > 0; k--) row[k] = (row[k] + row[k - 1]) % m;
        }
        for (int k = 0; k <= i; k++) {
            ll t = row[k] * (g[i] % m) % m;
            f[k] = (f[k] + ((sign < 0 && (i - k) % 2) ? m - t : t)) % m;
        }
    }
    return f;
}

// 例：长度为 n 的排列中"恰好 k 个不动点"的个数（k = 0 就是错排数）。
// 钦定 k 个不动点、其余随意：g(k) = C(n, k)·(n − k)!，再用形式二反演
vector<ll> fixed_point_counts(int n, ll m) {
    vector<ll> g(n + 1), fact(n + 1, 1 % m);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % m;
    vector<ll> row = {1 % m};
    for (int i = 1; i <= n; i++) {
        row.push_back(0);
        for (int k = i; k > 0; k--) row[k] = (row[k] + row[k - 1]) % m;
    }
    for (int k = 0; k <= n; k++) g[k] = row[k] * fact[n - k] % m;
    return binom_transform_upper(g, m);
}
