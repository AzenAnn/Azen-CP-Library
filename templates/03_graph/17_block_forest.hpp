/**
 * 03_graph/17 圆方树
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：03_graph/06 Tarjan（割点 / 点双连通分量）
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 点双连通分量（v-BCC）与 Tarjan 求法
 *   2. 圆方树建树：每个点双建方点，方点与分量内所有圆点连边 → 得到一棵树/森林
 *   3. 性质：圆点间路径 ↔ 圆方树上路径，方点度数 = 点双大小
 *   4. 应用：仙人掌等价转化、必经点/路径计数、点双上 DP
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/block-forest/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4630  P4630 [APIO2018] 铁人两项
 *   https://www.luogu.com.cn/problem/P4334  P4334 [COI2007] Policja（路径必经判断）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3225  提高+  P3225 [HNOI2012] 矿场搭建  考点：点双 + 圆方树计数
 *   https://www.luogu.com.cn/problem/P4606  省选−  P4606 [SDOI2018] 战略游戏  考点：圆方树 + 虚树
 *   https://www.luogu.com.cn/problem/P4334  省选−  P4334 [COI2007] Policja  考点：路径必经点判断
 *   https://www.luogu.com.cn/problem/P4630  省选/NOI−  P4630 [APIO2018] 铁人两项  考点：圆方树上路径贡献
 *   https://www.luogu.com.cn/problem/P5236  省选−  P5236 [AHOI2013] 联通图（仙人掌最短路）  考点：圆方树处理环
 *   https://codeforces.com/problemset/problem/1763/F  CF2600  CF1763F Edge Queries  考点：圆方树 + 点双
 *   https://www.luogu.com.cn/problem/P8456  省选/NOI−  P8456 「SWTR-8」地地铁铁  考点：圆方树计数
 *
 */

// TODO：在这里写出实现
