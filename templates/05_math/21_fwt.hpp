/**
 * 05_math/21 FWT（快速沃尔什变换）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：05_math/16 FFT / NTT
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 位运算卷积：C[k] = Σ_{i⊕j=k} A[i]·B[j]，⊕ 为 or / and / xor
 *   2. xor 卷积：FWT(A)[i] = Σ (−1)^{popcount(i&j)} A[j]；正逆变换同构，逆变换除以 n
 *   3. or / and 卷积：子集/超集和变换，逆变换做差分
 *   4. 高维前缀和视角、子集卷积（SOS DP 关联）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/poly/fwt/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4717  P4717 【模板】快速莫比乌斯/沃尔什变换（FMT/FWT）
 *   https://www.luogu.com.cn/problem/P6097  P6097 【模板】子集卷积
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4717  提高+/省选−  P4717 【模板】FMT/FWT  考点：or/and/xor 卷积
 *   https://www.luogu.com.cn/problem/P5495  省选−  P5495 【模板】FWT（xor 卷积应用）  考点：FWT
 *   https://www.luogu.com.cn/problem/P6097  省选−  P6097 【模板】子集卷积  考点：按 popcount 分层 FWT
 *   https://www.luogu.com.cn/problem/P5908  省选−  P5908 猫猫和企鹅  考点：or 卷积应用
 *   https://codeforces.com/problemset/problem/914/G  CF2600  CF914G Sum the Fibonacci  考点：FWT + 子集卷积
 *   https://www.luogu.com.cn/problem/P6622  省选/NOI−  P6622 [2020 年联考 A 卷] 信号传递  考点：FWT 优化 DP
 *
 */

// TODO：在这里写出实现
