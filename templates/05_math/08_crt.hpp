/**
 * 05_math/08 中国剩余定理
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：05_math/02 GCD 与扩展欧几里得
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. CRT（模数两两互质）
 *   2. 扩展 CRT（模数不互质）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/crt/
 *   cp-algorithms  https://cp-algorithms.com/algebra/chinese-remainder-theorem.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1495  P1495 【模板】中国剩余定理（CRT）/ 曹冲养猪
 *   https://www.luogu.com.cn/problem/P4777  P4777 【模板】扩展中国剩余定理（EXCRT）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1516  提高  P1516 [ZJOI2002] 青蛙的约会  考点：数学、数论、扩展欧几里德算法
 *   https://www.luogu.com.cn/problem/P3868  提高  P3868 [TJOI2009] 猜数字  考点：数学、扩展欧几里德算法、中国剩余定理 CRT
 *   https://www.luogu.com.cn/problem/P4861  提高  P4861 按钮  考点：数学、枚举、中国剩余定理 CRT
 *   https://www.luogu.com.cn/problem/P8060  提高  P8060 [POI 2003] Sums  考点：图论、图论建模、最短路
 *   https://codeforces.com/problemset/problem/687/B  CF1800  CF687B Remainders Game  考点：中国剩余定理、数学、数论
 *   https://codeforces.com/problemset/problem/1665/D  CF2000  CF1665D GCD Guess  考点：位运算、中国剩余定理、构造
 *   https://www.luogu.com.cn/problem/P4774  提高+/省选−  P4774 [NOI2018] 屠龙勇士  考点：不定方程、中国剩余定理 CRT、逆元
 *   https://codeforces.com/problemset/problem/1748/D  CF2100  CF1748D ConstructOR   考点：位运算、中国剩余定理、组合数学
 *   https://codeforces.com/problemset/problem/919/E  CF2100  CF919E Congruence Equation  考点：中国剩余定理、数学、数论
 *   https://codeforces.com/problemset/problem/1500/B  CF2200  CF1500B Two chandeliers  考点：二分、暴力、中国剩余定理
 *   https://www.luogu.com.cn/problem/P2183  省选/NOI−  P2183 [国家集训队] 礼物  考点：数学、中国剩余定理 CRT、Lucas 定理
 *   https://www.luogu.com.cn/problem/P2480  省选/NOI−  P2480 [SDOI2010] 古代猪文  考点：数学、素数判断、中国剩余定理 CRT
 *   https://www.luogu.com.cn/problem/P4245  省选/NOI−  P4245 【模板】任意模数多项式乘法  考点：数学、多项式、中国剩余定理 CRT
 *   https://www.luogu.com.cn/problem/P4720  省选/NOI−  P4720 【模板】扩展卢卡斯定理 / exLucas  考点：数学、数论、中国剩余定理 CRT
 *   https://codeforces.com/problemset/problem/1515/G  CF2700  CF1515G Phoenix and Odometers  考点：搜索、图论、数学
 *
 */

// 求解同余方程组 x ≡ r[i] (mod m[i])。所有中间运算用 __int128，要求最终的模数（lcm）不超过 ll 范围

ll crt_exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1, y = 0; return a; }
    ll d = crt_exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// 1. 中国剩余定理（模数两两互质）：x = Σ r[i] · M_i · inv(M_i)，其中 M = Π m[i]，M_i = M / m[i]
//    返回最小非负解（模 M 意义下唯一）
ll crt(const vector<ll> &r, const vector<ll> &m) {
    ll M = 1, x = 0;
    for (ll mi : m) M *= mi;
    for (size_t i = 0; i < r.size(); i++) {
        ll Mi = M / m[i], inv, y;
        crt_exgcd(Mi % m[i], m[i], inv, y);   // Mi · inv ≡ 1 (mod m[i])
        inv = (inv % m[i] + m[i]) % m[i];
        ll ri = (r[i] % m[i] + m[i]) % m[i];
        x = (x + (__int128)ri * Mi % M * inv) % M;
    }
    return x;
}

// 2. 扩展中国剩余定理（模数不一定互质）：两个两个合并。
//    x ≡ a (mod m1)、x ≡ b (mod m2)：设 x = a + m1·t，则 m1·t ≡ b - a (mod m2)，用 exgcd 解出 t。
//    返回 {最小非负解, lcm}；无解返回 {-1, -1}
pair<ll, ll> excrt(const vector<ll> &r, const vector<ll> &m) {
    ll x = 0, M = 1;   // 当前解为 x (mod M)
    for (size_t i = 0; i < r.size(); i++) {
        ll a = x, b = (r[i] % m[i] + m[i]) % m[i], t, y;
        ll g = crt_exgcd(M, m[i], t, y);
        ll diff = ((b - a) % m[i] + m[i]) % m[i];
        if (diff % g) return {-1, -1};
        ll mod = m[i] / g;
        t = (__int128)((t % mod + mod) % mod) * (diff / g) % mod;
        ll newM = M / g * m[i];
        x = (a + (__int128)M * t) % newM;
        M = newM;
    }
    return {(x % M + M) % M, M};
}
