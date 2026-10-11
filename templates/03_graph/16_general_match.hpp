/**
 * 03_graph/16 一般图匹配（带花树 Blossom）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：03_graph/07 二分图匹配（匈牙利 / Hopcroft-Karp）
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 一般图最大匹配与二分图的区别：奇环（花）的处理
 *   2. 带花树算法：BFS 找增广路，遇到偶环缩花
 *   3. 复杂度 O(n³)，实现细节：并查集维护花、lca 找花
 *   4. 应用：一般图最大匹配、最大权匹配（带权带花树）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/graph-matching/general-match/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P6113  P6113 【模板】一般图最大匹配
 *   https://www.luogu.com.cn/problem/P4256  P4256 [JSOI2008] Blue Mary 的战役地图（应用）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P6113  省选/NOI−  P6113 【模板】一般图最大匹配  考点：带花树
 *   https://www.luogu.com.cn/problem/P4256  省选−  P4256 Blue Mary 的战役地图  考点：匹配建模
 *   https://www.luogu.com.cn/problem/P6076  省选−  P6076 [JSOI2015] 染色问题  考点：一般图匹配判定
 *   https://www.luogu.com.cn/problem/P6693  省选/NOI−  P6693 儿童节礼物  考点：一般图匹配应用
 *   https://codeforces.com/problemset/problem/1089/B  CF2200  CF1089B Lazy Student  考点：一般图最大匹配
 *   https://www.luogu.com.cn/problem/P3067  省选−  P3067 [USACO12OPEN] Balanced Cow Subsets G  考点：搜索+匹配思想
 *
 */

// TODO：在这里写出实现
