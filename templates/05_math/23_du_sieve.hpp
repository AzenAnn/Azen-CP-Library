/**
 * 05_math/23 杜教筛
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：05_math/14 莫比乌斯反演
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 目标：求积性函数前缀和 S(n) = Σ_{i≤n} f(i)，n ≤ 1e10
 *   2. 核心：构造 g 使 (f*g) 易求，S(n) = (Σ_{i≤n}(f*g)(i) − Σ_{d≥2} g(d)S(n/d)) / g(1)
 *   3. 数论分块 + 记忆化：不同 ⌊n/i⌋ 只有 O(√n) 个
 *   4. 预处理前 n^{2/3}，复杂度 O(n^{2/3})
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/du/
 *   OI-wiki        https://oi-wiki.org/math/number-theory/hyperbola/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4213  P4213 【模板】杜教筛（Sum）
 *   https://www.luogu.com.cn/problem/P3768  P3768 简单的数学题（杜教筛求 φ 前缀）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4213  省选−  P4213 【模板】杜教筛  考点：μ 和 φ 前缀和
 *   https://www.luogu.com.cn/problem/P3768  省选−  P3768 简单的数学题  考点：杜教筛 + 欧拉函数前缀
 *   https://www.luogu.com.cn/problem/P5325  省选/NOI−  P5325 【模板】Min_25 筛  考点：Min_25（替代/进阶）
 *   https://www.luogu.com.cn/problem/P1587  省选/NOI−  P1587 [NOI2016] 循环之美  考点：杜教筛 + 数论
 *   https://www.luogu.com.cn/problem/P5571  省选/NOI−  P5571 有趣的数  考点：杜教筛
 *   https://codeforces.com/problemset/problem/1093/G  CF2400  CF1093G Multidimensional Queries（前置：数论分块）  考点：分块思想
 *
 */

// TODO：在这里写出实现
