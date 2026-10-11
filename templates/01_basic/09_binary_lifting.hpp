/**
 * 01_basic/09 倍增
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：01_basic/03 二分查找、二分答案与三分
 * 状态：NOTE（没有固定模板，以笔记和题单为主）
 *
 * 【学习顺序】
 *   1. 倍增思想：跳 2^k 步
 *   2. 函数迭代 / 跳转表
 *   3. ST 表与倍增 LCA 的共同基础
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/basic/binary-lifting/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1081  P1081 [NOIP 2012 提高组] 开车旅行
 *
 * 【我的笔记】
 *   倍增思想：预处理 f[i][k] = 从 i 出发跳 2^k 步的结果，把 O(n) 的逐次跳转变成 O(log n)。
 *   关键观察：任何正整数都能表示成若干个 2 的幂次之和（二进制分解），所以"跳 n 步"等价于
 *   按二进制位从大到小（或从小到大）依次跳 2^k 步。
 *   实现要点：
 *     - 预处理通常用 DP：f[i][k] = f[f[i][k-1]][k-1]（先跳 2^(k-1) 步，再跳 2^(k-1) 步）。
 *     - 查询时从高位到低位枚举 k，如果跳了不会越界/满足条件，就跳。这样保证最后位置是
 *       满足条件的最后一个位置（或第一个不满足的位置，看定义）。
 *     - 边界：k 的上界取 log2(n) + 1；f 数组的 0 行通常是"跳 1 步"的直接后继。
 *   与 ST 表、LCA 的联系：
 *     - ST 表：倍增在静态数组上求 RMQ，st[k][i] = 区间 [i, i+2^k-1] 的最值。
 *     - 倍增 LCA：fa[k][v] = v 的 2^k 级祖先，先把深度大的节点提到同一深度，再一起往上跳。
 *     - 三者都是"二进制拆分 + 预处理幂次信息"的思想。
 *   常见应用：
 *     - 函数迭代：求 f^K(x)（K 很大），用倍增预处理 f^(2^k)(x)。
 *     - 树上路径问题：K 级祖先、路径最值（配合 ST 表思想）。
 *     - 跳转游戏：从每个位置能跳到某个范围，求跳到终点的最少步数（BFS 预处理 + 倍增）。
 *   易错点：
 *     - 跳 2^k 步 vs 跳 k 步混淆。
 *     - 预处理时数组越界（f[i][k] 中的 i 可能超出范围，需要特殊处理）。
 *     - 查询时从低位开始跳会导致错误（应该从高位到低位，贪心匹配二进制位）。
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10479  普及  P10479 匹配统计  考点：倍增、二分、哈希 hashing
 *   https://www.luogu.com.cn/problem/P1396  普及  P1396 营救  考点：搜索、图论、倍增
 *   https://www.luogu.com.cn/problem/P1816  普及  P1816 忠诚  考点：线段树、倍增、树状数组
 *   https://www.luogu.com.cn/problem/P3252  普及  P3252 [JLOI2012] 树  考点：动态规划 DP、搜索、倍增
 *   https://www.luogu.com.cn/problem/P1198  普及+/提高−  P1198 [JSOI2008] 最大数  考点：线段树、倍增、二分
 *   https://www.luogu.com.cn/problem/P1613  普及+/提高−  P1613 跑路  考点：动态规划 DP、倍增、广度优先搜索 BFS
 *   https://www.luogu.com.cn/problem/P4281  普及+/提高−  P4281 [AHOI2008] 紧急集合 / 聚会  考点：倍增、最近公共祖先 LCA、树链剖分
 *   https://www.luogu.com.cn/problem/P7167  普及+/提高−  P7167 [eJOI 2020] Fountain (Day1)  考点：倍增、ST 表、单调栈
 *   https://www.luogu.com.cn/problem/P1967  提高  P1967 [NOIP 2013 提高组] 货车运输  考点：图论、贪心、倍增
 *   https://www.luogu.com.cn/problem/P3147  提高  P3147 [USACO16OPEN] 262144 P  考点：动态规划 DP、贪心、倍增
 *   https://www.luogu.com.cn/problem/P3509  提高  P3509 [POI 2010] ZAB-Frog  考点：动态规划 DP、倍增、单调队列
 *   https://www.luogu.com.cn/problem/P4155  提高  P4155 [SCOI2015] 国旗计划  考点：贪心、倍增、二分
 *   https://codeforces.com/problemset/problem/1142/B  CF2000  CF1142B Lynyrd Skynyrd  考点：数据结构、搜索、DP
 *   https://codeforces.com/problemset/problem/1516/D  CF2100  CF1516D Cut  考点：二分、数据结构、DP
 *   https://codeforces.com/problemset/problem/1175/E  CF2200  CF1175E Minimal Segment Cover  考点：数据结构、搜索、分治
 *
 */

// 本专题没有固定的代码模板，重点是理解思路、积累模型：
//   1. 按上面【学习顺序】逐项学习，把每种模型的直观理解写进【我的笔记】；
//   2. 典型题的完整代码放在 solutions/ 中，在【题单】里写上链接和一句话提示。
