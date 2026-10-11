/**
 * 01_basic/07 贪心常见模型
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：NOTE（没有固定模板，以笔记和题单为主）
 *
 * 【学习顺序】
 *   1. 排序后贪心
 *   2. 区间问题：选最多不相交区间 / 区间覆盖
 *   3. 邻项交换证明
 *   4. 反悔贪心（配合堆）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/basic/greedy/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1803  P1803 凌乱的yyy / 线段覆盖
 *   https://www.luogu.com.cn/problem/P1080  P1080 [NOIP 2012 提高组] 国王游戏
 *   https://www.luogu.com.cn/problem/P2949  P2949 [USACO09OPEN] Work Scheduling G
 *
 * 【我的笔记】
 *   核心判断：当前步的最优选择能否保证全局最优？贪心不依赖之前的选择（无后效性）。
 *   验证贪心是否成立的方法：
 *     1. 交换论证法：假设存在更优解，通过交换两个相邻元素，证明交换后不会更差。
 *     2. 反证法：假设贪心解不是最优，推导矛盾。
 *     3. 直觉 + 小数据对拍：先写暴力，跑随机小数据验证。
 *   常见模型：
 *     - 排序贪心：按某个关键字排序后顺序取（如结束时间最早的区间、单位价值最大的物品）。
 *       关键是找到正确的排序关键字，常常需要"如果交换这两个会怎样"来发现。
 *     - 区间问题：选最多不相交区间（按右端点排序）；用最少数量的点覆盖所有区间（按右端点排序，在右端点放哨兵）；
 *       区间覆盖（按左端点排序，在能覆盖当前点的区间中选右端点最远的）。
 *     - 邻项交换证明：对于"安排顺序使总代价最小"类问题，比较相邻两项交换前后的代价，
 *       推出排序规则（通常是 a_i + b_j vs a_j + b_i 之类的比较）。
 *     - 反悔贪心：先做贪心选择，如果发现更优方案就"反悔"（用堆维护已选元素，
 *       遇到更优的替换掉最差的已选元素）。经典：股票买卖、 scheduling。
 *   易错点：
 *     - 排序关键字选错（比如按左端点排序而不是右端点）。
 *     - 边界条件：空区间、单元素、全部相等。
 *     - 反悔贪心的堆要及时弹出已不在候选集中的元素（懒删除）。
 *   与 DP 的关系：贪心是 DP 的特例（最优子结构 + 贪心选择性质）。当贪心无法证明时，考虑 DP。
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1639  入门  P1639 [USACO18FEB] Teleportation B  考点：贪心
 *   https://www.luogu.com.cn/problem/P3742  入门  P3742 umi的函数  考点：模拟、字符串、贪心
 *   https://codeforces.com/problemset/problem/2047/B  CF900  CF2047B Replace Character  考点：暴力、组合数学、贪心
 *   https://codeforces.com/problemset/problem/246/A  CF900  CF246A Buggy Sorting  考点：构造、贪心、排序
 *   https://www.luogu.com.cn/problem/P1478  普及−  P1478 陶陶摘苹果（升级版）  考点：贪心、排序、背包 DP
 *   https://www.luogu.com.cn/problem/P2240  普及−  P2240 【深基12.例1】部分背包问题  考点：贪心
 *   https://codeforces.com/problemset/problem/1550/B  CF1000  CF1550B Maximum Cost Deletion  考点：贪心、数学
 *   https://codeforces.com/problemset/problem/1993/B  CF1100  CF1993B Parity and Sum  考点：构造、贪心
 *   https://www.luogu.com.cn/problem/P1016  普及  P1016 [NOIP 1999 普及组/提高组] 旅行家的预算  考点：模拟、搜索、贪心
 *   https://www.luogu.com.cn/problem/P1250  普及  P1250 种树  考点：贪心、排序、差分约束
 *   https://www.luogu.com.cn/problem/P1842  普及  P1842 [USACO05NOV] 奶牛玩杂技  考点：贪心
 *   https://www.luogu.com.cn/problem/P2887  普及  P2887 [USACO07NOV] Sunscreen G  考点：动态规划 DP、贪心
 *   https://codeforces.com/problemset/problem/1369/C  CF1400  CF1369C RationalLee  考点：贪心、数学、排序
 *   https://codeforces.com/problemset/problem/1579/D  CF1400  CF1579D Productive Meeting  考点：构造、图论、贪心
 *   https://codeforces.com/problemset/problem/1989/C  CF1400  CF1989C Two Movies  考点：贪心、数学
 *
 */

// 本专题没有固定的代码模板，重点是理解思路、积累模型：
//   1. 按上面【学习顺序】逐项学习，把每种模型的直观理解写进【我的笔记】；
//   2. 典型题的完整代码放在 solutions/ 中，在【题单】里写上链接和一句话提示。
