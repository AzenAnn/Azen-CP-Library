/**
 * 01_basic/10 分治
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：01_basic/05 排序与离散化
 * 状态：NOTE（没有固定模板，以笔记和题单为主）
 *
 * 【学习顺序】
 *   1. 分治三步：分、治、合
 *   2. 归并分治统计跨区间贡献
 *   3. 后续：CDQ 分治、点分治、平面最近点对
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/basic/divide-and-conquer/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1257  P1257 平面上的最接近点对
 *
 * 【我的笔记】
 *   分治三步：分（Divide）→ 治（Conquer）→ 合（Combine）。关键是"合"这一步，
 *   即如何处理跨越左右两半的解。
 *   经典模型：
 *     - 归并排序求逆序对：合并时统计左半在右半之前的元素对。
 *     - 平面最近点对：按 x 分治，合并时只需检查中间带状区域内的点对（按 y 排序后
 *       每个点只需检查后面 7 个点）。
 *     - 最大子段和：max(左半最大，右半最大，横跨中点的最大)。
 *   复杂度分析：T(n) = aT(n/b) + f(n)，主定理。归并类分治通常是 O(n log n)。
 *   易错点：
 *     - 合并时忘记排序或顺序错乱，导致后续合并错误。
 *     - 递归边界处理：n=1 时直接返回，n=0 时注意空区间。
 *     - 平面最近点对中，中间区域只需检查 y 坐标差 < d 的点，但实现时容易忘记按 y 排序。
 *   与其他算法的联系：
 *     - CDQ 分治：处理三维偏序等离线问题，把"修改"和"查询"分治，用归并统计贡献。
 *     - 点分治：在树上选重心分治，保证树高 O(log n)。
 *     - 快速幂、FFT 也是分治思想。
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1228  普及  P1228 地毯填补问题  考点：递归、分治
 *   https://www.luogu.com.cn/problem/P1498  普及  P1498 南蛮图腾  考点：字符串、递归、分治
 *   https://www.luogu.com.cn/problem/P1928  普及  P1928 外星密码  考点：模拟、字符串、递归
 *   https://www.luogu.com.cn/problem/P5461  普及  P5461 赦免战俘  考点：递归、分治
 *   https://codeforces.com/problemset/problem/2093/D  CF1400  CF2093D Skibidi Table  考点：位运算、实现
 *   https://www.luogu.com.cn/problem/P1637  普及+/提高−  P1637 三元上升子序列  考点：线段树、平衡树、树状数组
 *   https://www.luogu.com.cn/problem/P4147  普及+/提高−  P4147 玉蟾宫  考点：动态规划 DP、线段树、枚举
 *   https://www.luogu.com.cn/problem/P8815  普及+/提高−  P8815 [CSP-J 2022] 逻辑表达式  考点：模拟、树形数据结构、分治
 *   https://codeforces.com/problemset/problem/559/B  CF1700  CF559B Equivalent Strings  考点：分治、哈希、排序
 *   https://www.luogu.com.cn/problem/P4095  提高  P4095 [HEOI2013] Eden 的新背包问题  考点：枚举、分治、背包 DP
 *   https://www.luogu.com.cn/problem/P9753  提高  P9753 [CSP-S 2023] 消消乐  考点：动态规划 DP、分治、哈希 hashing
 *   https://codeforces.com/problemset/problem/459/D  CF1800  CF459D Pashmak and Parmida's problem  考点：数据结构、分治、排序
 *   https://www.luogu.com.cn/problem/P4149  提高+/省选−  P4149 [IOI 2011] Race  考点：点分治、递归、树上启发式合并
 *   https://www.luogu.com.cn/problem/P4178  提高+/省选−  P4178 Tree  考点：线段树、点分治、树状数组
 *   https://www.luogu.com.cn/problem/P7883  提高+/省选−  P7883 平面最近点对（加强加强版）  考点：计算几何、分治
 *
 */

// 本专题没有固定的代码模板，重点是理解思路、积累模型：
//   1. 按上面【学习顺序】逐项学习，把每种模型的直观理解写进【我的笔记】；
//   2. 典型题的完整代码放在 solutions/ 中，在【题单】里写上链接和一句话提示。
