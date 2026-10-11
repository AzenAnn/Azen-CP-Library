/**
 * 05_math/19 卡特兰数与斯特林数
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：05_math/05 组合数学基础
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
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
 *   https://www.luogu.com.cn/problem/P1044  P1044 [NOIP2003 普及组] 栈（卡特兰数）
 *   https://www.luogu.com.cn/problem/P5395  P5395 【模板】第二类斯特林数 · 行（多项式）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1044  普及+  P1044 栈  考点：卡特兰数递推
 *   https://www.luogu.com.cn/problem/P1722  普及+  P1722 矩阵 II  考点：卡特兰数
 *   https://www.luogu.com.cn/problem/P1976  普及+/提高−  P1976 鸡蛋饼  考点：卡特兰数高精度
 *   https://www.luogu.com.cn/problem/P3200  提高+  P3200 [HNOI2009] 有趣的数列  考点：卡特兰数 + 质因数分解
 *   https://www.luogu.com.cn/problem/P4827  提高+  P4827 [国家集训队] Crash 的文明世界（斯特林数前置）  考点：二项式展开
 *   https://www.luogu.com.cn/problem/P5395  省选−  P5395 【模板】第二类斯特林数·行  考点：NTT + 斯特林通项
 *   https://www.luogu.com.cn/problem/P5396  省选−  P5396 【模板】第二类斯特林数·列  考点：生成函数
 *   https://www.luogu.com.cn/problem/P5408  省选−  P5408 【模板】第一类斯特林数·行  考点：倍增 / NTT
 *
 */

// TODO：在这里写出实现
