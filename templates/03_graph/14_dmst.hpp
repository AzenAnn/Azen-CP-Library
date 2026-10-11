/**
 * 03_graph/14 最小树形图（朱刘算法 / Edmonds）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：03_graph/04 最小生成树
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 有向图最小生成树定义：固定根，每个非根点选一条入边，权值和最小且无环
 *   2. 朱刘算法：每点选最小入边 → 无环则结束；有环则缩点、调整入边权值、递归
 *   3. 复杂度：O(nm)，缩点最多 n 次
 *   4. 进阶：Tarjan 优化实现、不定根问题（虚拟根）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/dmst/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4716  P4716 【模板】最小树形图
 *   https://www.luogu.com.cn/problem/P2792  P2792 小卖部选址（不定根变式）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4716  提高+/省选−  P4716 【模板】最小树形图  考点：朱刘算法
 *   https://www.luogu.com.cn/problem/P2792  省选−  P2792 小卖部选址  考点：虚拟超级根
 *   https://www.luogu.com.cn/problem/P1555  提高+  P1555 尴尬的数字  考点：树形图建模
 *   https://www.luogu.com.cn/problem/P4331  省选−  P4331 [BalticOI 2004] Sequence 数字序列  考点：左偏树（相关技巧）
 *   https://codeforces.com/problemset/problem/240/E  CF2400  CF240E Road Repairs  考点：最小树形图输出方案
 *   https://codeforces.com/problemset/problem/67/E  CF2300  CF67E Save the City!  考点：建模转化为树形图
 *
 */

// TODO：在这里写出实现
