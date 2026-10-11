/**
 * 06_dp/01 线性 DP 入门与记忆化搜索
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：NOTE（没有固定模板，以笔记和题单为主）
 *
 * 【学习顺序】
 *   1. 状态定义与转移（爬楼梯、打家劫舍）
 *   2. 网格路径 DP
 *   3. 最大子段和
 *   4. 记忆化搜索 → 递推
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/basic/
 *   OI-wiki        https://oi-wiki.org/dp/memo/
 *   cp-algorithms  https://cp-algorithms.com/dynamic_programming/intro-to-dp.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/dp.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1216  P1216 [IOI 1994 / USACO1.5] 数字三角形 Number Triangles
 *   https://www.luogu.com.cn/problem/P1115  P1115 最大子段和
 *
 * 【我的笔记】
 *   DP 三要素：状态定义、状态转移方程、初始条件与边界。
 *   状态定义：明确"子问题"是什么。f[i] 表示什么？f[i][j] 又表示什么？
 *     好的状态定义应该满足：无后效性（当前状态确定后，未来决策与如何到达当前无关）。
 *   转移方程：考虑"最后一步"或"第一个决策"，把大问题分解为小问题。
 *     比如：f[i] = max(f[i-1], f[i-2] + a[i])（打家劫舍：不偷 i 或偷 i）。
 *   记忆化搜索 vs 递推：
 *     - 记忆化搜索：自顶向下，自然对应递归思路，但常数大、可能爆栈。
 *     - 递推：自底向上，需要确定计算顺序（拓扑序），但效率高、可滚动数组优化。
 *     - 新手建议先写记忆化搜索，再改递推。
 *   常见线性 DP 模型：
 *     - 爬楼梯/斐波那契：f[i] = f[i-1] + f[i-2]。
 *     - 打家劫舍：f[i] = max(f[i-1], f[i-2] + a[i])。
 *     - 最大子段和：f[i] = max(a[i], f[i-1] + a[i])，ans = max(f[i])。
 *     - 网格路径：f[i][j] = f[i-1][j] + f[i][j-1]（或 min/max 版本）。
 *   易错点：
 *     - 状态定义不清：f[i] 到底包不包括 i？是前缀还是后缀？
 *     - 边界条件：f[0]、f[1]、空数组、单元素。
 *     - 递推顺序：保证转移时用到的小问题已经计算过。
 *     - 滚动数组时忘记备份旧值，或维度压错了。
 *   与贪心的关系：当问题具有最优子结构但贪心选择性质不成立时，用 DP。
 *     比如：区间调度可以贪心，但带权区间调度必须 DP。
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1634  入门  P1634 禽兽的传染病  考点：模拟、数学、递推
 *   https://www.luogu.com.cn/problem/P1720  入门  P1720 月落乌啼算钱（斐波那契数列）  考点：模拟、数学、递推
 *   https://www.luogu.com.cn/problem/P17645  入门  P17645 [ICPC 2019 Yinchuan R] Fibonacci Sequence  考点：模拟、递推
 *   https://www.luogu.com.cn/problem/P1002  普及−  P1002 [NOIP 2002 普及组] 过河卒  考点：动态规划 DP、递推、记忆化搜索
 *   https://www.luogu.com.cn/problem/P1028  普及−  P1028 [NOIP 2001 普及组] 数的计算  考点：动态规划 DP、递推、递归
 *   https://www.luogu.com.cn/problem/P1164  普及−  P1164 小 A 点菜  考点：动态规划 DP、记忆化搜索、背包 DP
 *   https://www.luogu.com.cn/problem/P1605  普及−  P1605 迷宫  考点：搜索、递推、枚举
 *   https://www.luogu.com.cn/problem/P1719  普及  P1719 最大加权矩形  考点：动态规划 DP、递推、枚举
 *   https://www.luogu.com.cn/problem/P8816  普及  P8816 [CSP-J 2022] 上升点列  考点：动态规划 DP、记忆化搜索、Floyd 算法
 *   https://codeforces.com/problemset/problem/1987/C  CF1200  CF1987C Basil's Garden  考点：DP、贪心
 *   https://codeforces.com/problemset/problem/1285/B  CF1300  CF1285B Just Eat It!  考点：DP、贪心、实现
 *   https://codeforces.com/problemset/problem/1195/C  CF1400  CF1195C Basketball Exercise  考点：DP
 *   https://codeforces.com/problemset/problem/1881/E  CF1500  CF1881E Block Sequence  考点：DP
 *   https://codeforces.com/problemset/problem/1373/D  CF1600  CF1373D Maximum Sum on Even Positions  考点：分治、DP、贪心
 *   https://codeforces.com/problemset/problem/1741/E  CF1600  CF1741E Sending a Sequence Over the Network  考点：DP
 *
 */

// 本专题没有固定的代码模板，重点是理解思路、积累模型：
//   1. 按上面【学习顺序】逐项学习，把每种模型的直观理解写进【我的笔记】；
//   2. 典型题的完整代码放在 solutions/ 中，在【题单】里写上链接和一句话提示。
