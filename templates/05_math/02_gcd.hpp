/**
 * 05_math/02 GCD 与扩展欧几里得
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. gcd / lcm
 *   2. 扩展欧几里得 exgcd
 *   3. 线性同余方程 ax ≡ b (mod m)
 *   4. 二元一次不定方程的通解
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/gcd/
 *   OI-wiki        https://oi-wiki.org/math/number-theory/linear-equation/
 *   cp-algorithms  https://cp-algorithms.com/algebra/euclid-algorithm.html
 *   cp-algorithms  https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
 *   cp-algorithms  https://cp-algorithms.com/algebra/linear-diophantine-equation.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1082  P1082 [NOIP 2012 提高组] 同余方程
 *   https://www.luogu.com.cn/problem/P5656  P5656 【模板】二元一次不定方程 (exgcd)
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1888  入门  P1888 三角函数  考点：数学、排序、最大公约数 gcd
 *   https://www.luogu.com.cn/problem/P4956  入门  P4956 [COCI 2017/2018 #6] Davor  考点：不定方程
 *   https://www.luogu.com.cn/problem/P1029  普及−  P1029 [NOIP 2001 普及组] 最大公约数和最小公倍数问题  考点：数学、枚举、最大公约数 gcd
 *   https://www.luogu.com.cn/problem/P1072  普及−  P1072 [NOIP 2009 提高组] Hankson 的趣味题  考点：数学、枚举、最大公约数 gcd
 *   https://www.luogu.com.cn/problem/P1372  普及−  P1372 又是毕业季I  考点：数学、最大公约数 gcd
 *   https://www.luogu.com.cn/problem/P2118  普及−  P2118 [NOIP 2014 普及组] 比例简化  考点：数学、枚举、最大公约数 gcd
 *   https://codeforces.com/problemset/problem/2244/C  CF1100  CF2244C Stepan and Permutation  考点：构造、搜索、并查集
 *   https://www.luogu.com.cn/problem/P10031  普及  P10031 「Cfz Round 3」Xor with Gcd  考点：数学、最大公约数 gcd、位运算
 *   https://www.luogu.com.cn/problem/P3951  普及  P3951 [NOIP 2017 提高组] 小凯的疑惑  考点：数学、不定方程、中国剩余定理 CRT
 *   https://codeforces.com/problemset/problem/1736/B  CF1200  CF1736B Playing with GCD  考点：数学、数论
 *   https://codeforces.com/problemset/problem/1853/B  CF1200  CF1853B Fibonaccharsis  考点：二分、暴力、数学
 *   https://codeforces.com/problemset/problem/1462/D  CF1400  CF1462D Add to Neighbour and Remove  考点：贪心、数学、数论
 *   https://codeforces.com/problemset/problem/1526/B  CF1400  CF1526B I Hate 1111  考点：DP、数学、数论
 *   https://codeforces.com/problemset/problem/1458/A  CF1600  CF1458A Row GCD  考点：数学、数论
 *   https://codeforces.com/problemset/problem/1920/C  CF1600  CF1920C Partitioning the Array  考点：暴力、数学、数论
 *
 */

// 1. gcd / lcm：C++17 起有 std::gcd、std::lcm（<numeric>），也可以用 __gcd
//    lcm 先除后乘防溢出：a / gcd(a, b) * b

// 2. 扩展欧几里得：求一组 x, y 使 a*x + b*y = gcd(a, b)，返回 gcd(a, b)
//    推导：gcd(a, b) = gcd(b, a % b)，由 b*x' + (a % b)*y' = g 得 x = y', y = x' - (a / b) * y'
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1, y = 0; return a; }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// 3. 线性同余方程 a*x ≡ b (mod m)（m >= 1）：返回 {最小非负解 x, 解的周期 m / g}，无解返回 {-1, -1}
//    有解当且仅当 g = gcd(a, m) 整除 b；所有解为 x + k * (m / g)
pair<ll, ll> linear_congruence(ll a, ll b, ll m) {
    a = (a % m + m) % m, b = (b % m + m) % m;
    ll x, y, g = exgcd(a, m, x, y);
    if (b % g) return {-1, -1};
    ll period = m / g;
    x = (__int128)x * (b / g) % period;
    if (x < 0) x += period;
    return {x, period};
}

// 4. 二元一次不定方程 a*x + b*y = c：先用 exgcd 求出 a*x0 + b*y0 = g，c % g != 0 则无解；
//    否则一组特解为 x0 * c/g, y0 * c/g，通解为 x = x1 + k * (b/g), y = y1 - k * (a/g)
