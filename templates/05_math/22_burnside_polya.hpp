/**
 * 05_math/22 Burnside 引理与 Pólya 定理
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：05_math/07 欧拉函数与欧拉定理、05_math/04 乘法逆元
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 问题：旋转 / 翻转后相同的方案算一种，求本质不同的方案数
 *   2. Burnside 引理：本质不同的方案数 = 每个置换的不动点个数的平均值
 *   3. Pólya 定理：用 m 种颜色随意染色时，置换 g 的不动点数 = m^{c(g)}，c(g) 为 g 的循环个数
 *   4. 项链（只旋转）：旋转 i 格有 gcd(n, i) 个循环 → 答案 = (1/n)·Σ_{d|n} φ(n/d)·m^d，n 可达 1e9
 *      手镯（旋转 + 翻转）：再加上 n 种翻转，n 奇数时每种 (n+1)/2 个循环，n 偶数时一半 n/2+1、一半 n/2
 *   5. 染色有限制（每种颜色个数固定、相邻不同色）时，不能直接用 m^{c(g)}，要回到 Burnside 对每个置换单独计数
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/combinatorics/polya/
 *   cp-algorithms  https://cp-algorithms.com/combinatorics/burnside.html
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4980  P4980 【模板】Pólya（Polya）定理
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/UVA10294  提高+/省选−  UVA10294 Arif in Dhaka (First Love Part 2)  考点：项链与手镯的计数（旋转 / 旋转 + 翻转）
 *   https://www.luogu.com.cn/problem/P1446  省选/NOI−  P1446 [HNOI2008] Cards  考点：置换、动态规划 DP、数学
 *   https://www.luogu.com.cn/problem/P2561  省选/NOI−  P2561 [AHOI2002] 黑白瓷砖  考点：Pólya 定理、搜索、数学
 *   https://www.luogu.com.cn/problem/P5233  省选/NOI−  P5233 [JSOI2012] 爱之项链  考点：Pólya 定理、数学、数论
 *   https://www.luogu.com.cn/problem/P8633  省选/NOI−  P8633 [蓝桥杯 2015 国 B] 模型染色  考点：Pólya 定理、枚举
 *   https://www.luogu.com.cn/problem/P4128  NOI/NOI+/CTS  P4128 [SHOI2006] 有色图  考点：Pólya 定理、搜索、群论
 *   https://www.luogu.com.cn/problem/P4727  NOI/NOI+/CTS  P4727 [HNOI2009] 图的同构计数  考点：Pólya 定理、数学、群论
 *
 */

// 下面的 p 都要求是质数（要用到 n、2n 的逆元，p 不能整除 n）。
ll polya_pow(ll a, ll e, ll p) {
    ll r = 1 % p;
    for (a %= p; e; e >>= 1, a = (__int128)a * a % p)
        if (e & 1) r = (__int128)r * a % p;
    return r;
}

// 1. 项链：长度 n 的环用 m 种颜色染色，旋转相同算一种。O(√n · 因子个数)，n ≤ 1e12 也可以
ll count_necklaces(ll n, ll m, ll p) {
    vector<ll> pf;   // n 的质因子，用来求 φ(n / d)
    {
        ll x = n;
        for (ll i = 2; i * i <= x; i++)
            if (x % i == 0) {
                pf.push_back(i);
                while (x % i == 0) x /= i;
            }
        if (x > 1) pf.push_back(x);
    }
    auto phi = [&](ll x) {
        ll r = x;
        for (ll q : pf)
            if (x % q == 0) r = r / q * (q - 1);
        return r;
    };
    ll s = 0;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d) continue;
        s = (s + (__int128)(phi(n / d) % p) * polya_pow(m, d, p)) % p;
        if (d * d != n) s = (s + (__int128)(phi(d) % p) * polya_pow(m, n / d, p)) % p;
    }
    return (__int128)s * polya_pow(n % p, p - 2, p) % p;
}

// 2. 手镯：旋转、翻转相同都算一种（二面体群，共 2n 个置换）
ll count_bracelets(ll n, ll m, ll p) {
    ll rot = (__int128)count_necklaces(n, m, p) * (n % p) % p;   // 旋转部分的不动点总数
    ll ref;
    if (n % 2) ref = (__int128)(n % p) * polya_pow(m, (n + 1) / 2, p) % p;
    else ref = (__int128)(n / 2 % p) * ((polya_pow(m, n / 2 + 1, p) + polya_pow(m, n / 2, p)) % p) % p;
    return (__int128)((rot + ref) % p) * polya_pow(2 * n % p, p - 2, p) % p;
}

// 3. 一般的 Burnside / Pólya：给出置换群的全部置换（每个置换是 0..k-1 的排列），m 种颜色随意染色。
//    返回 (1/|G|)·Σ m^{c(g)} mod p
ll polya_general(const vector<vector<int>> &group, ll m, ll p) {
    ll s = 0;
    for (auto &g : group) {
        int k = g.size(), c = 0;
        vector<char> vis(k, 0);
        for (int i = 0; i < k; i++)
            if (!vis[i]) {
                c++;
                for (int j = i; !vis[j]; j = g[j]) vis[j] = 1;
            }
        s = (s + polya_pow(m, c, p)) % p;
    }
    return (__int128)s * polya_pow((ll)group.size() % p, p - 2, p) % p;
}
