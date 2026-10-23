/**
 * 09_misc/04 折半搜索 / Meet in the Middle
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：01_basic/03 二分查找、二分答案与三分、01_basic/12 搜索：DFS、BFS、剪枝
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 核心思想：把规模为 n 的问题拆成两半各 n/2，分别枚举后合并
 *   2. 复杂度：O(2^{n/2} · poly(n))，n ≤ 40~45 可过
 *   3. 合并方式：排序 + 二分 / 哈希表 / 双指针
 *   4. 应用：子集和、精确覆盖、高维部分和
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/search/bidirectional/（双向搜索关联）
 *   USACO Guide    https://usaco.guide/gold/meet-in-the-middle
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4799  P4799 [CEOI2015 Day2] 世界冰球锦标赛
 *   https://www.luogu.com.cn/problem/P3067  P3067 [USACO12OPEN] Balanced Cow Subsets G
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4799  提高  P4799 世界冰球锦标赛  考点：折半枚举 + 二分
 *   https://www.luogu.com.cn/problem/P2962  提高+  P2962 [USACO09NOV] 灯 Lights  考点：折半 + 状态压缩
 *   https://www.luogu.com.cn/problem/P3067  提高+  P3067 Balanced Cow Subsets  考点：折半 + 平衡判断
 *   https://www.luogu.com.cn/problem/P5194  提高+  P5194 [USACO05DEC] Scales  考点：折半搜索
 *   https://codeforces.com/problemset/problem/888/E  CF1800  CF888E Maximum Subsequence  考点：折半 + 二分
 *   https://codeforces.com/problemset/problem/1006/F  CF2100  CF1006F Xor-Paths  考点：折半 + 哈希
 *   https://www.luogu.com.cn/problem/P2321  省选−  P2321 [SCOI2005] 扫雷（折半思想）  考点：搜索剪枝
 *
 */

// TODO：在这里写出实现
