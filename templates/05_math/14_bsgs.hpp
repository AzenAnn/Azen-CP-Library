/**
 * 05_math/14 离散对数 BSGS
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：05_math/04 乘法逆元
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Baby-Step Giant-Step
 *   2. 扩展 BSGS
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/discrete-logarithm/
 *   cp-algorithms  https://cp-algorithms.com/algebra/discrete-log.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3846  P3846 【模板】BSGS / [TJOI2007] 可爱的质数
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P17254  提高+/省选−  P17254 线性筛 2  考点：大步小步算法 BSGS、线性筛法
 *   https://www.luogu.com.cn/problem/P3306  提高+/省选−  P3306 [SDOI2013] 随机数生成器  考点：数论、逆元、大步小步算法 BSGS
 *   https://www.luogu.com.cn/problem/P11175  省选/NOI−  P11175 【模板】基于值域预处理的快速离散对数  考点：数学、原根、数论
 *   https://www.luogu.com.cn/problem/P12239  省选/NOI−  P12239 [蓝桥杯 2023 国 Java A] 游戏的得分  考点：数论、大步小步算法 BSGS
 *   https://www.luogu.com.cn/problem/P12523  省选/NOI−  P12523 [Aboi Round 1] Nomad  考点：线段树、大步小步算法 BSGS
 *   https://www.luogu.com.cn/problem/P12694  省选/NOI−  P12694 BZOJ2219 数论之神  考点：原根、中国剩余定理 CRT、大步小步算法 BSGS
 *   https://www.luogu.com.cn/problem/P4195  省选/NOI−  P4195 【模板】扩展 BSGS / exBSGS  考点：数学、数论、枚举
 *   https://www.luogu.com.cn/problem/P6736  省选/NOI−  P6736 「Wdsr-2」白泽教育  考点：递归、数论、哈希 hashing
 *   https://www.luogu.com.cn/problem/P12011  NOI/NOI+/CTS  P12011 【MX-X10-T7】[LSOT-4] 春开，意遥遥。  考点：数学、原根、数论
 *   https://www.luogu.com.cn/problem/P12541  NOI/NOI+/CTS  P12541 [APIO2025] Hack!  考点：二分、构造、大步小步算法 BSGS
 *   https://www.luogu.com.cn/problem/P17225  NOI/NOI+/CTS  P17225 [Math×Girl²] 算术课堂  考点：数论、大步小步算法 BSGS
 *   https://www.luogu.com.cn/problem/P5668  NOI/NOI+/CTS  P5668 【模板】N 次剩余  考点：数学、原根、数论
 *   https://www.luogu.com.cn/problem/P6690  NOI/NOI+/CTS  P6690 一次函数  考点：动态规划 DP、原根、扩展欧几里德算法
 *
 */

// 离散对数：求最小的非负整数 x 使 a^x ≡ b (mod p)，无解返回 -1。

// 1. BSGS（要求 gcd(a, p) = 1）：令 m = ceil(√p)，x = i·m - j（1 <= i <= m，0 <= j < m），
//    则 a^(i·m) ≡ b · a^j。先把所有 b · a^j 存进哈希表（小步），再枚举 i 查表（大步）。O(√p)
ll bsgs(ll a, ll b, ll p) {
    a %= p, b %= p;
    if (b == 1 % p) return 0;
    ll m = ceil(sqrt((double)p));
    unordered_map<ll, ll> table;
    ll cur = b;
    for (ll j = 0; j < m; j++) table[cur] = j, cur = (__int128)cur * a % p;   // 同一个值保留较大的 j
    ll am = 1;
    for (ll j = 0; j < m; j++) am = (__int128)am * a % p;
    cur = 1;
    for (ll i = 1; i <= m; i++) {
        cur = (__int128)cur * am % p;
        auto it = table.find(cur);
        if (it != table.end()) return i * m - it->second;
    }
    return -1;
}

// 2. 扩展 BSGS（不要求互质）：不断用 g = gcd(a, p) 约分：a^x ≡ b ⇒ (a/g)·a^(x-1) ≡ b/g (mod p/g)，
//    直到 a 与模数互质，再用 BSGS 解剩下的方程，答案加上约分的次数
ll exbsgs(ll a, ll b, ll p) {
    a %= p, b %= p;
    if (b == 1 % p) return 0;
    ll k = 0, c = 1 % p;   // 已约分 k 次，方程变为 c · a^(x-k) ≡ b (mod p)
    while (true) {
        ll g = __gcd(a, p);
        if (g == 1) break;
        if (b % g) return -1;
        p /= g, b /= g, c = (__int128)c * (a / g) % p, k++;
        if (c == b % p) return k;
    }
    // c 与 p 互质，求 c 的逆元
    ll r0 = c, r1 = p, s0 = 1, s1 = 0;
    while (r1) {
        ll q = r0 / r1;
        r0 -= q * r1, swap(r0, r1);
        s0 -= q * s1, swap(s0, s1);
    }
    ll inv_c = (s0 % p + p) % p;
    ll r = bsgs(a, (__int128)b * inv_c % p, p);
    return r == -1 ? -1 : r + k;
}
