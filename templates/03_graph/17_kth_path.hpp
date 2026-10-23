/**
 * 03_graph/17 K 短路
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：03_graph/03 最短路
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 第 k 短路定义：允许重复经过点的第 k 短简单路径（通常允许非简单路径）
 *   2. A* 算法：估价函数 f = 已走距离 + 到终点的最短距离（反图 Dijkstra 预处理）
 *   3. 每个点第 k 次出队时即得到起点的第 k 短路
 *   4. 进阶：可持久化可并堆（左偏树）做法 O(m log m + k log k)
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/kth-path/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2483  P2483 【模板】k 短路 / [SDOI2010] 魔法猪学院
 *   https://www.luogu.com.cn/problem/P4467  P4467 [SCOI2007] k 短路
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2449  提高  P2449 [SDOI2010] 古代猪文（前置练习：最短路）  考点：Dijkstra
 *   https://www.luogu.com.cn/problem/P2483  提高+/省选−  P2483 【模板】k 短路  考点：A* + 反图最短路
 *   https://www.luogu.com.cn/problem/P4467  提高+/省选−  P4467 [SCOI2007] k 短路  考点：A* 第 k 次出队
 *   https://www.luogu.com.cn/problem/P2968  提高  P2968 [USACO09DEC] Music Notes G  考点：k 短路思想
 *   https://www.luogu.com.cn/problem/P5283  省选/NOI−  P5283 [十二省联考 2019] 异或粽子  考点：可持久化 01Trie 求第 k 大（思想类比）
 *   https://codeforces.com/problemset/problem/1196/F  CF2400  CF1196F K-th Path  考点：保留前 k 短候选边
 *
 */

// TODO：在这里写出实现
