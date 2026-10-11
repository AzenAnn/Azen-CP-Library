/**
 * 05_math/04 乘法逆元
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：05_math/01 取模运算与快速幂、05_math/02 GCD 与扩展欧几里得
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 费马小定理求逆元（模数为质数）
 *   2. exgcd 求逆元（模数不是质数）
 *   3. 线性求 1..n 的逆元
 *   4. 阶乘逆元倒推
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/inverse/
 *   cp-algorithms  https://cp-algorithms.com/algebra/module-inverse.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math_basic.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3811  P3811 【模板】模意义下的乘法逆元
 *   https://www.luogu.com.cn/problem/P5431  P5431 【模板】模意义下的乘法逆元 2
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P11465  普及  P11465 水上舞者索尼娅  考点：逆元
 *   https://www.luogu.com.cn/problem/P12217  普及  P12217 [蓝桥杯 2023 国 Java B] 逆元  考点：数论、逆元
 *   https://www.luogu.com.cn/problem/P17017  普及  P17017 [GESP202606 八级] 堆石子  考点：组合数学、排列组合、逆元
 *   https://www.luogu.com.cn/problem/P2265  普及  P2265 路边的水沟  考点：组合数学、逆元
 *   https://www.luogu.com.cn/problem/P2613  普及+/提高−  P2613 【模板】有理数取余  考点：数学、数论、扩展欧几里德算法
 *   https://www.luogu.com.cn/problem/P4071  普及+/提高−  P4071 [SDOI2016] 排列计数  考点：数学、递推、枚举
 *   https://www.luogu.com.cn/problem/P5104  普及+/提高−  P5104 红包发红包  考点：概率论、期望、逆元
 *   https://www.luogu.com.cn/problem/P5689  普及+/提高−  P5689 [CSP-S 2019 江西] 多叉堆  考点：并查集、组合数学、逆元
 *   https://codeforces.com/problemset/problem/1833/F  CF1700  CF1833F Ira and Flamenco  考点：组合数学、构造、数据结构
 *   https://www.luogu.com.cn/problem/P1641  提高  P1641 [SCOI2010] 生成字符串  考点：数学、组合数学、排列组合
 *   https://www.luogu.com.cn/problem/P2260  提高  P2260 [清华集训 2012] 模积和  考点：数学、数论、容斥原理
 *   https://www.luogu.com.cn/problem/P2485  提高  P2485 [SDOI2011] 计算器  考点：素数判断、最大公约数 gcd、逆元
 *   https://www.luogu.com.cn/problem/P2155  提高+/省选−  P2155 [SDOI2008] 沙拉公主的困惑  考点：数学、素数判断、逆元
 *   https://www.luogu.com.cn/problem/P3306  提高+/省选−  P3306 [SDOI2013] 随机数生成器  考点：数论、逆元、大步小步算法 BSGS
 *   https://www.luogu.com.cn/problem/P4774  提高+/省选−  P4774 [NOI2018] 屠龙勇士  考点：不定方程、中国剩余定理 CRT、逆元
 *
 */

// a 在模 m 下的逆元 x 满足 a*x ≡ 1 (mod m)，存在当且仅当 gcd(a, m) = 1。

// 1. 费马小定理：m 为质数且 a 不是 m 的倍数时，a 的逆元为 a^(m-2) mod m（用 05_math/01 的 qpow）

// 2. 扩展欧几里得求逆元：m 不必是质数；逆元不存在时返回 -1（迭代写法，不依赖其他模板）
ll inv_mod(ll a, ll m) {
    ll r0 = (a % m + m) % m, r1 = m, s0 = 1, s1 = 0;
    while (r1) {
        ll q = r0 / r1;
        r0 -= q * r1, swap(r0, r1);
        s0 -= q * s1, swap(s0, s1);
    }
    if (r0 != 1) return -1;
    return (s0 % m + m) % m;
}

// 3. 线性求 1..n 的逆元（p 为质数，n < p），O(n)
//    由 p = (p / i) * i + p % i 得 inv[i] = -(p / i) * inv[p % i]
vector<ll> inverses(int n, ll p) {
    vector<ll> inv(n + 1, 0);
    if (n >= 1) inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (p - p / i) * inv[p % i] % p;
    return inv;
}

// 4. 阶乘逆元：先用快速幂求 n! 的逆元，再倒推 inv_fact[i - 1] = inv_fact[i] * i。
//    见 05_math/05 的 Comb。
//    求任意 n 个数的逆元也可以用同样的思路：先求前缀积，只做一次快速幂，再倒推（洛谷 P5431）。
