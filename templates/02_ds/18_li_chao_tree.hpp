/**
 * 02_ds/18 李超线段树
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/07 线段树（含懒标记）
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 理解线段树维护"区间内所有直线在某一 x 处的最值"
 *   2. 插入直线：与当前节点直线比较，在中点处占优的留下，劣势的下放到子节点
 *   3. 查询：从根到叶子路径上所有直线在 x 处的最值
 *   4. 进阶：支持线段（有限区间）、动态开点
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/li-chao-tree/
 *   cp-algorithms  https://cp-algorithms.com/geometry/convex_hull_trick.html
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4097  P4097 [HEOI2013] Segment
 *   https://www.luogu.com.cn/problem/P4254  P4254 [JSOI2008] Blue Mary 开公司
 *
 * 【我的笔记】
 *   适用场景：动态插入直线（或线段），查询某点 x 处所有直线的最大/最小值。
 *   核心思想：每个线段树节点保存"在该节点区间中点处最优"的直线。
 *     插入时比较新旧直线在中点的值，劣势一方下放到其可能翻盘的子区间。
 *   复杂度：插入 O(log²n)（线段退化 O(log n) 分支），查询 O(log n)。
 *   易错点：
 *     - 比较大小要带 eps（浮点）或改用斜率比较避免除法；
 *     - 下放时只需往"劣势直线可能更优"的那一侧递归；
 *     - 插入线段时要先按区间定位 O(log n) 个节点，再在各节点内做直线插入。
 *   与斜率优化的联系：斜率优化 DP 的凸壳维护可以用李超树替代，
 *     支持任意顺序插入和任意 x 查询（不要求斜率/查询单调）。
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4097  提高+/省选−  P4097 [HEOI2013] Segment  考点：线段插入 + 单点查询
 *   https://www.luogu.com.cn/problem/P4254  提高+/省选−  P4254 [JSOI2008] Blue Mary 开公司  考点：直线插入 + 单点查询
 *   https://www.luogu.com.cn/problem/P3081  提高+  P3081 [USACO13MAR] The Farm and Grill G（凸壳思想前置）  考点：凸壳
 *   https://codeforces.com/problemset/problem/1083/E  CF2400  CF1083E The Fair Nut and Rectangles  考点：李超树优化 DP
 *   https://www.luogu.com.cn/problem/P4655  省选−  P4655 [CEOI2017] Building Bridges  考点：李超树 + 分治 DP
 *   https://codeforces.com/problemset/problem/932/F  CF2700  CF932F Escape Through Leaf  考点：李超树合并 / DSU on tree
 *   https://www.luogu.com.cn/problem/P5468  省选/NOI−  P5468 [NOI2019] 回家路线  考点：斜率优化 + 李超树
 *   https://www.luogu.com.cn/problem/P4027  省选/NOI−  P4027 [NOI2007] 货币兑换  考点：CDQ 分治 / 李超树维护凸壳
 *
 */

// TODO：在这里写出实现
