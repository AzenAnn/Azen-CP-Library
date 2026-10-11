/**
 * 07_string/11 序列自动机
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：07_string/08 后缀自动机（理解自动机思想）
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 定义：next[i][c] = 位置 i 之后字符 c 第一次出现的位置
 *   2. 建树 O(n·|Σ|)，查询子序列匹配 O(m)
 *   3. 与 SAM 区别：序列自动机判断子序列，SAM 判断子串
 *   4. 应用：子序列判定、贪心匹配、子序列计数 DP 辅助
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/seq-automaton/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5826  P5826 【模板】子序列自动机
 *   https://www.luogu.com.cn/problem/P4119  P4119 可持久化序列自动机（进阶）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P5826  提高  P5826 【模板】子序列自动机  考点：next 数组
 *   https://www.luogu.com.cn/problem/P2108  提高  P2108 学英语  考点：子序列判定
 *   https://www.luogu.com.cn/problem/P5283  提高+  P5283 [十二省联考 2019] 异或粽子（贪心思想）  考点：贪心 + 自动机
 *   https://codeforces.com/problemset/problem/1183/H  CF1900  CF1183H Subsequences (hard version)  考点：子序列计数 DP
 *   https://www.luogu.com.cn/problem/P2032  提高  P2032 扫描（next 数组思想前置）  考点：单调队列
 *   https://www.luogu.com.cn/problem/P6136  省选−  P6136 【模板】普通平衡树（数据加强，辅助练习）  考点：平衡树维护 next
 *
 */

// TODO：在这里写出实现
