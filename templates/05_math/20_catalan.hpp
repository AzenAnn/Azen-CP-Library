/**
 * 05_math/20 卡特兰数与斯特林数
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：05_math/05 组合数与计数原理
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 卡特兰数：C_n = C(2n,n)/(n+1) = Σ C_i·C_{n-1-i}；出栈序列、括号匹配、二叉树计数
 *   2. 递推与通项、路径不交叉模型（折线法）
 *   3. 第一类斯特林数（无符号）：n 个元素分 k 个圆排列；递推 s(n,k)=s(n-1,k-1)+(n-1)s(n-1,k)
 *   4. 第二类斯特林数：n 个元素分 k 个非空子集；通项 S(n,k)=1/k! Σ(-1)^i C(k,i)(k-i)^n
 *   5. 斯特林数与阶乘幂/普通幂转换：x^n = Σ S(n,k) x^{\underline k}
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/combinatorics/catalan/
 *   OI-wiki        https://oi-wiki.org/math/combinatorics/stirling/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1044  P1044 [NOIP 2003 普及组] 栈
 *   https://www.luogu.com.cn/problem/P1287  P1287 盒子与球
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1722  普及−  P1722 矩阵 II  考点：Catalan 数、模拟、动态规划 DP
 *   https://www.luogu.com.cn/problem/P1754  普及  P1754 球迷购票问题  考点：Catalan 数、动态规划 DP、数学
 *   https://www.luogu.com.cn/problem/P2028  普及  P2028 龙兄摘苹果  考点：Stirling 数、动态规划 DP
 *   https://www.luogu.com.cn/problem/P1655  普及+/提高−  P1655 小朋友的球  考点：Stirling 数、动态规划 DP、高精度
 *   https://www.luogu.com.cn/problem/P2532  普及+/提高−  P2532 [AHOI2012] 树屋阶梯  考点：Catalan 数、模拟、高精度
 *   https://www.luogu.com.cn/problem/P3200  普及+/提高−  P3200 [HNOI2009] 有趣的数列  考点：Catalan 数、素数判断、栈
 *   https://www.luogu.com.cn/problem/P1641  提高  P1641 [SCOI2010] 生成字符串  考点：Catalan 数、数学、组合数学
 *   https://www.luogu.com.cn/problem/P3978  省选/NOI−  P3978 [TJOI2015] 概率论  考点：Catalan 数、递推、生成函数
 *   https://www.luogu.com.cn/problem/P4609  省选/NOI−  P4609 [FJOI2016] 建筑师  考点：Stirling 数、数学、递推
 *   https://www.luogu.com.cn/problem/P5395  省选/NOI−  P5395 第二类斯特林数·行  考点：Stirling 数、多项式、快速数论变换 NTT
 *   https://www.luogu.com.cn/problem/P5408  省选/NOI−  P5408 第一类斯特林数·行  考点：Stirling 数、数学、倍增
 *   https://www.luogu.com.cn/problem/P6620  省选/NOI−  P6620 [省选联考 2020 A 卷] 组合数问题  考点：Stirling 数、组合数学、二项式定理
 *
 */

// 卡特兰数、斯特林数、贝尔数（模 p 的 O(n²) 递推表；p 为任意模数）。
// 卡特兰：C_0 = 1，C_{n+1} = Σ C_i·C_{n−i}；= C(2n, n) / (n + 1)。出栈序列、括号序列、二叉树形态、不越过对角线的格路。
// 第一类斯特林数（无符号）s(n, k)：n 个元素排成 k 个圆排列。s(n, k) = s(n−1, k−1) + (n−1)·s(n−1, k)
// 第二类斯特林数 S(n, k)：n 个元素划分成 k 个非空集合。S(n, k) = S(n−1, k−1) + k·S(n−1, k)
// 贝尔数 B_n = Σ_k S(n, k)：n 个元素的集合划分总数。
// 常用转换：x^n = Σ_k S(n, k)·x^{(k)↓}（下降幂）；x^{(n)↑}（上升幂）= Σ_k s(n, k)·x^k
struct CountingTables {
    int n;
    ll p;
    vector<ll> catalan, bell;
    vector<vector<ll>> s1, s2;
    CountingTables(int n, ll p) : n(n), p(p), catalan(n + 1, 0), bell(n + 1, 0), s1(n + 1, vector<ll>(n + 1, 0)), s2(s1) {
        catalan[0] = 1 % p;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < i; j++) catalan[i] = (catalan[i] + catalan[j] * catalan[i - 1 - j]) % p;
        s1[0][0] = s2[0][0] = 1 % p;
        for (int i = 1; i <= n; i++)
            for (int k = 1; k <= i; k++) {
                s1[i][k] = (s1[i - 1][k - 1] + (ll)(i - 1) % p * s1[i - 1][k]) % p;
                s2[i][k] = (s2[i - 1][k - 1] + (ll)k % p * s2[i - 1][k]) % p;
            }
        for (int i = 0; i <= n; i++)
            for (int k = 0; k <= i; k++) bell[i] = (bell[i] + s2[i][k]) % p;
    }
};
