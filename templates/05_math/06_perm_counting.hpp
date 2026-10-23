/**
 * 05_math/06 康托展开、错排与约瑟夫问题
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：05_math/05 组合数与计数原理、02_ds/06 树状数组
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 康托展开：排列的字典序排名 = Σ (后面比 a_i 小的数的个数) · (n − i)!，树状数组 O(n log n)
 *   2. 逆康托展开：用阶乘进制把排名拆开，依次取第 k 小的未用数字（八数码、魔板的状态压缩）
 *   3. 错排：D(n) = (n − 1)(D(n − 1) + D(n − 2))，D(n) = n!·Σ(−1)^k/k!；"恰好 k 个在原位" = C(n, k)·D(n − k)
 *   4. 约瑟夫问题：J(n, k) = (J(n − 1, k) + k) mod n，O(n)；n 很大、k 较小时 O(k log n) 递推
 *   5. 输出出圈顺序：树状数组 / 线段树上找第 k 个还在的人，O(n log n)
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/permutation/
 *   OI-wiki        https://oi-wiki.org/math/combinatorics/derangement/
 *   OI-wiki        https://oi-wiki.org/misc/josephus/
 *   cp-algorithms  https://cp-algorithms.com/others/josephus_problem.html
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5367  P5367 【模板】康托展开
 *   https://www.luogu.com.cn/problem/P1595  P1595 信封问题
 *   https://www.luogu.com.cn/problem/P1996  P1996 约瑟夫问题
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2524  入门  P2524 Uim的情人节礼物·其之弐  考点：康托展开、模拟、数学
 *   https://www.luogu.com.cn/problem/P1088  普及−  P1088 [NOIP 2004 普及组] 火星人  考点：求下一个排列（康托展开或 next_permutation）
 *   https://www.luogu.com.cn/problem/P1145  普及−  P1145 [CERC 1995] 约瑟夫  考点：约瑟夫问题的模拟与枚举
 *   https://www.luogu.com.cn/problem/P2525  普及−  P2525 Uim的情人节礼物·其之壱  考点：康托展开、模拟、数学
 *   https://www.luogu.com.cn/problem/P2696  普及  P2696 慈善的约瑟夫  考点：约瑟夫问题
 *   https://www.luogu.com.cn/problem/P3182  普及  P3182 [HAOI2016] 放棋子  考点：错排数
 *   https://www.luogu.com.cn/problem/P8671  普及  P8671 [蓝桥杯 2018 国 AC] 约瑟夫环  考点：约瑟夫递推公式
 *   https://www.luogu.com.cn/problem/P2578  普及+/提高−  P2578 [ZJOI2005] 九数码游戏  考点：康托展开、广度优先搜索 BFS、哈希 hashing
 *   https://www.luogu.com.cn/problem/P2730  普及+/提高−  P2730 [IOI 1996 / USACO3.2] 魔板 Magic Squares  考点：康托展开、搜索、广度优先搜索 BFS
 *   https://www.luogu.com.cn/problem/P3014  普及+/提高−  P3014 [USACO11FEB] Cow Line S  考点：康托展开、贪心、枚举
 *
 */

// 1. 康托展开：p 是 0..n-1 的排列，返回它在全部排列中的字典序排名（从 0 开始）mod m。O(n log n)
ll cantor_rank(const vector<int> &p, ll m) {
    int n = p.size();
    vector<int> bit(n + 1, 0);   // 树状数组：统计已经出现过的数
    vector<ll> fact(n + 1, 1 % m);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % m;
    ll r = 0;
    for (int i = 0; i < n; i++) {
        int used_less = 0;   // 前面出现过的、比 p[i] 小的数
        for (int x = p[i]; x > 0; x -= x & -x) used_less += bit[x];
        ll less = p[i] - used_less;   // 后面比 p[i] 小的数
        r = (r + less % m * fact[n - 1 - i]) % m;
        for (int x = p[i] + 1; x <= n; x += x & -x) bit[x]++;
    }
    return r;
}

// 2. 逆康托展开：返回 0..n-1 的第 k 个排列（k 从 0 开始，要求 k < n!，所以 n ≤ 20）。O(n^2)
vector<int> cantor_unrank(int n, ll k) {
    vector<ll> fact(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
    vector<int> rest(n), p;
    iota(rest.begin(), rest.end(), 0);
    for (int i = n - 1; i >= 0; i--) {
        int idx = k / fact[i];
        k %= fact[i];
        p.push_back(rest[idx]), rest.erase(rest.begin() + idx);
    }
    return p;
}

// 3. 错排数 D(0..n) mod m：D(0) = 1，D(1) = 0，D(i) = (i - 1)(D(i - 1) + D(i - 2))
vector<ll> derangements(int n, ll m) {
    vector<ll> d(n + 1, 0);
    d[0] = 1 % m;
    for (int i = 2; i <= n; i++) d[i] = (ll)(i - 1) % m * ((d[i - 1] + d[i - 2]) % m) % m;
    return d;
}

// 4. 约瑟夫问题：n 个人（编号 0..n-1）围成圈，从 0 开始报数，报到 k 的出圈，返回最后剩下的人。O(n)
ll josephus(ll n, ll k) {
    ll r = 0;
    for (ll i = 2; i <= n; i++) r = (r + k) % i;
    return r;
}
// n 很大（如 1e18）、k 较小时：一轮淘汰 n/k 个人再递归，O(k log n)
ll josephus_big(ll n, ll k) {
    if (n == 1) return 0;
    if (k == 1) return n - 1;
    if (k > n) return (josephus_big(n - 1, k) + k) % n;
    ll cnt = n / k;
    ll r = josephus_big(n - cnt, k);
    r -= n % k;
    if (r < 0) r += n;
    else r += r / (k - 1);
    return r;
}
// 出圈顺序（编号 0..n-1）：树状数组上二分找"还在圈里的第 t 个人"，O(n log n)
vector<int> josephus_order(int n, ll k) {
    vector<int> bit(n + 1, 0), res;
    for (int i = 1; i <= n; i++)
        for (int x = i; x <= n; x += x & -x) bit[x]++;
    int LOG = 1;
    while ((1 << LOG) <= n) LOG++;
    ll cur = 0;   // 当前从圈中第 cur 个人（0 开始）开始报数
    for (int left = n; left > 0; left--) {
        cur = (cur + k - 1) % left;
        int pos = 0;
        ll t = cur + 1;   // 找第 t 个还在的人
        for (int j = LOG; j >= 0; j--)
            if (pos + (1 << j) <= n && bit[pos + (1 << j)] < t) pos += 1 << j, t -= bit[pos];
        res.push_back(pos);   // pos + 1 是树状数组下标，对应编号 pos
        for (int x = pos + 1; x <= n; x += x & -x) bit[x]--;
    }
    return res;
}
