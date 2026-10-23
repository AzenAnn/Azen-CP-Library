/**
 * 01_basic/12 搜索：DFS、BFS、剪枝
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：01_basic/10 分治
 * 状态：NOTE（没有固定模板，以笔记和题单为主）
 *
 * 【学习顺序】
 *   1. DFS 回溯：全排列、子集、N 皇后
 *   2. BFS：最短路径、拓扑排序、双向 BFS
 *   3. 剪枝：可行性剪枝、最优性剪枝、记忆化
 *   4. 迭代加深（IDDFS）与 A*
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/search/
 *   OI-wiki        https://oi-wiki.org/search/dfs/
 *   OI-wiki        https://oi-wiki.org/search/bfs/
 *   OI-wiki        https://oi-wiki.org/search/backtracking/
 *   OI-wiki        https://oi-wiki.org/search/astar/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1219  P1219 [USACO1.5] 八皇后 Checker Challenge
 *   https://www.luogu.com.cn/problem/P1135  P1135 奇怪的电梯
 *   https://www.luogu.com.cn/problem/P1605  P1605 迷宫
 *
 * 【我的笔记】
 *   搜索本质：穷举所有可能解空间，通过剪枝和优化减少实际搜索量。
 *   DFS 适合：解空间树状、需要回溯、路径相关的问题。递归实现注意栈深度。
 *   BFS 适合：无权图最短路径、状态空间逐层扩展。用队列实现。
 *   剪枝策略：
 *     - 可行性剪枝：当前状态已不可能产生合法解，提前返回。
 *     - 最优性剪枝：当前代价已超过已知最优解，提前返回。
 *     - 记忆化：记录已访问状态，避免重复搜索（转化为 DP）。
 *     - 启发式搜索：用估价函数引导搜索方向（A*、IDA*）。
 *   双向 BFS：起点和终点同时 BFS，相遇时结束。适合状态空间大但深度浅的问题。
 *   迭代加深：限制 DFS 深度，逐步增加。适合深度未知但解较浅的问题。
 *   易错点：
 *     - 回溯时忘记恢复现场（标记数组、全局变量）。
 *     - BFS 队列中元素重复（忘记判重）。
 *     - 剪枝条件写错，导致剪掉了最优解。
 *   与 DP 的关系：记忆化搜索本质上是自顶向下的 DP；搜索 + 剪枝 ≈ 状态压缩 DP。
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1036  普及−  P1036 [NOIP 2002 普及组] 选数  考点：DFS、回溯、素数判断
 *   https://www.luogu.com.cn/problem/P1443  普及−  P1443 马的遍历  考点：BFS
 *   https://www.luogu.com.cn/problem/P1101  普及−  P1101 单词方阵  考点：DFS、字符串
 *   https://www.luogu.com.cn/problem/P1162  普及−  P1162 填涂颜色  考点：BFS、Flood Fill
 *   https://www.luogu.com.cn/problem/P2392  普及−  P2392 kkksc03 考前临时抱佛脚  考点：DFS、背包、贪心
 *   https://www.luogu.com.cn/problem/P1141  普及  P1141 01迷宫  考点：BFS、连通块
 *   https://www.luogu.com.cn/problem/P1219  普及  P1219 [USACO1.5] 八皇后 Checker Challenge  考点：DFS、回溯、位运算优化
 *   https://www.luogu.com.cn/problem/P1135  普及  P1135 奇怪的电梯  考点：BFS、最短路
 *   https://www.luogu.com.cn/problem/P1103  普及  P1103 书本整理  考点：DFS、贪心
 *   https://www.luogu.com.cn/problem/P2327  普及  P2327 [SCOI2005] 扫雷  考点：枚举第一格后逐格递推、可行性检查
 *   https://www.luogu.com.cn/problem/P1379  普及+/提高−  P1379 八数码难题  考点：BFS、A*、哈希判重
 *   https://codeforces.com/problemset/problem/1741/E  CF1600  CF1741E Sending a Sequence Over the Network  考点：BFS/DFS、DP
 *   https://www.luogu.com.cn/problem/P2324  提高  P2324 [SCOI2005] 骑士精神  考点：IDA*、启发式搜索
 *   https://www.luogu.com.cn/problem/P1084  省选/NOI−  P1084 [NOIP 2012 提高组] 疫情控制  考点：DFS、贪心、倍增
 *
 */

// 本专题没有固定的代码模板，重点是理解思路、积累模型：
//   1. 按上面【学习顺序】逐项学习，把每种模型的直观理解写进【我的笔记】；
//   2. 典型题的完整代码放在 solutions/ 中，在【题单】里写上链接和一句话提示。
