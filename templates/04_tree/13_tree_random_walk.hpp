/**
 * 04_tree/13 树上随机游走
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：04_tree/01 树的基础：直径、重心、DFS 序、06_dp/09 概率与期望 DP
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 随机游走期望方程：f[u] = 1 + Σ f[v] / deg[u]
 *   2. 叶子消元：利用叶子只连父亲，把叶子期望用父亲表示，逐层消元
 *   3. 从根出发/任意点对间期望步数
 *   4. 结合高斯消元：方程组直接求解（n 较小时）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/tree-random-walk/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1365  P1365 WJMZBMR 打 osu!（期望入门）
 *   https://www.luogu.com.cn/problem/P3830  P3830 [SHOI2012] 随机树
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1365  提高  P1365 WJMZBMR 打 osu!  考点：期望 DP
 *   https://www.luogu.com.cn/problem/P4316  提高+  P4316 绿豆蛙的归宿  考点：图上期望拓扑
 *   https://www.luogu.com.cn/problem/P3830  省选−  P3830 [SHOI2012] 随机树  考点：随机游走期望
 *   https://www.luogu.com.cn/problem/P3232  省选−  P3232 [HNOI2013] 游走  考点：边经过次数期望
 *   https://codeforces.com/problemset/problem/280/C  CF1900  CF280C Game on Tree  考点：树上期望
 *   https://www.luogu.com.cn/problem/P2081  省选/NOI−  P2081 [NOI2012] 迷失游乐园  考点：基环树 + 随机游走
 *
 */

// TODO：在这里写出实现
