/**
 * 02_ds/19 线段树合并与分裂
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：02_ds/11 线段树进阶、02_ds/13 可持久化数据结构
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 线段树合并：两棵动态开点线段树对应节点递归合并，信息叠加
 *   2. 复杂度分析：合并总复杂度 O(n log n)，每个节点只会被合并一次
 *   3. 线段树分裂：按排名/值域把一棵线段树拆成两棵
 *   4. 应用：树上启发式合并的替代、维护集合的并/交/差
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/seg-merge-split/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4556  P4556 [Vani有约会] 雨天的尾巴
 *   https://www.luogu.com.cn/problem/P2824  P2824 [HEOI2016/TJOI2016] 排序（分裂）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4556  提高+/省选−  P4556 [Vani有约会] 雨天的尾巴  考点：线段树合并 + 树上差分
 *   https://www.luogu.com.cn/problem/P2824  省选−  P2824 [HEOI2016/TJOI2016] 排序  考点：线段树分裂 + 合并
 *   https://www.luogu.com.cn/problem/P3224  提高+  P3224 [HNOI2012] 永无乡  考点：并查集 + 线段树合并
 *   https://www.luogu.com.cn/problem/P5298  省选−  P5298 [PKUWC2018] 随机游走（合并优化 DP）  考点：合并
 *   https://www.luogu.com.cn/problem/P3600  省选/NOI−  P3600 随机数生成器（合并思想）  考点：综合
 *   https://codeforces.com/problemset/problem/600/E  CF2300  CF600E Lomsat gelral  考点：线段树合并 / DSU on tree
 *   https://codeforces.com/problemset/problem/208/E  CF2100  CF208E Blood Cousins（合并思想）  考点：树上启发式
 *   https://www.luogu.com.cn/problem/P6777  省选/NOI−  P6777 [NOI2020] 制作菜品（分裂思想）  考点：构造 + 分裂
 *
 */

// TODO：在这里写出实现
