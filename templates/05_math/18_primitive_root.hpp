/**
 * 05_math/18 阶与原根
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：05_math/04 欧拉函数、05_math/06 快速幂 / 费马小定理
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 阶的定义：使 a^d ≡ 1 (mod p) 的最小正整数 d，记 ord_p(a)，d | φ(p)
 *   2. 原根：ord_p(g) = φ(p) 的 g；p, 2p, p^k, 2p^k（p 奇素数）存在原根
 *   3. 求原根：找最小原根（试除 + 检验 φ(p) 的素因子）
 *   4. 应用：离散对数、指标法（原根将乘法化为加法）、NTT 模数
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/primitive-root/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P6091  P6091 【模板】原根
 *   https://www.luogu.com.cn/problem/P3846  P3846 [TJOI2007] 可爱的质数 / 【模板】BSGS
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P6091  提高+  P6091 【模板】原根  考点：求最小原根 / 所有原根
 *   https://www.luogu.com.cn/problem/P3846  提高+  P3846 【模板】BSGS  考点：离散对数
 *   https://www.luogu.com.cn/problem/P4195  提高+  P4195 【模板】扩展 BSGS / exBSGS  考点：非互质离散对数
 *   https://www.luogu.com.cn/problem/P3306  提高+  P3306 [SDOI2013] 随机数生成器  考点：二次剩余 + BSGS
 *   https://www.luogu.com.cn/problem/P5491  省选−  P5491 【模板】二次剩余  考点：Cipolla 算法
 *   https://www.luogu.com.cn/problem/P2480  省选−  P2480 [SDOI2010] 古代猪文  考点：原根 + Lucas + BSGS
 *
 */

// TODO：在这里写出实现
