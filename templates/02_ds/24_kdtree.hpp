/**
 * 02_ds/24 K-D Tree
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/07 线段树（含懒标记）
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 建树：按维度交替选择中位数，递归建树
 *   2. 最近邻查询：优先搜索更近的子树，回溯时检查另一子树
 *   3. 范围查询：矩形区域内查询，利用边界剪枝
 *   4. 应用：高维空间最近邻、平面点集查询
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/kdt/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1429  P1429 平面最近点对（加强版）
 *   https://www.luogu.com.cn/problem/P4169  P4169 [Violet] 天使玩偶/SJY 摆棋子
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1429  普及+/提高−  P1429 平面最近点对（加强版）  考点：最近点对 / KDT
 *   https://www.luogu.com.cn/problem/P2479  提高  P2479 [SDOI2010] 捉迷藏（KDT 思想前置）  考点：平面点统计
 *   https://www.luogu.com.cn/problem/P4169  提高+/省选−  P4169 [Violet] 天使玩偶/SJY 摆棋子  考点：KDT 最远点
 *   https://www.luogu.com.cn/problem/P4357  提高+  P4357 [CQOI2016] k 远点对  考点：KDT + 堆
 *   https://www.luogu.com.cn/problem/P4148  省选−  P4148 简单题  考点：KDT 矩形加 / 矩形查
 *   https://codeforces.com/problemset/problem/293/E  CF2600  CF293E Close Vertices（点分治/KDT 思想）  考点：平面统计
 *   https://www.luogu.com.cn/problem/P5471  省选/NOI−  P5471 [NOI2019] 弹跳  考点：KDT / 分块优化建图
 *   https://www.luogu.com.cn/problem/P7883  省选/NOI−  P7883 平面最近点对（加强加强版）  考点：KDT 严格复杂度
 *
 */

// TODO：在这里写出实现
