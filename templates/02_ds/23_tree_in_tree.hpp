/**
 * 02_ds/23 树套树
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：02_ds/12 线段树进阶、02_ds/14 平衡树
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 问题模型：带修改的区间第 k 小（动态区间 kth）
 *   2. 树状数组套权值线段树：外层维护前缀，内层维护权值线段树（可持久化或动态开点）
 *   3. 线段树套平衡树：外层区间，内层平衡树维护有序集合
 *   4. 复杂度：修改 O(log²n)，查询 O(log²n) 或 O(log³n)
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/seg-in-bit/
 *   OI-wiki        https://oi-wiki.org/ds/balanced-in-seg/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2617  P2617 Dynamic Rankings
 *   https://www.luogu.com.cn/problem/P3380  P3380 【模板】树套树
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3380  提高+/省选−  P3380 【模板】树套树  考点：线段树套平衡树
 *   https://www.luogu.com.cn/problem/P2617  提高+/省选−  P2617 Dynamic Rankings  考点：树状数组套权值线段树
 *   https://www.luogu.com.cn/problem/P1903  提高+  P1903 [国家集训队] 数颜色（带修莫队可替）  考点：带修区间统计
 *   https://www.luogu.com.cn/problem/P3157  省选−  P3157 [CQOI2011] 动态逆序对  考点：树套树 / CDQ
 *   https://www.luogu.com.cn/problem/P3759  省选−  P3759 [TJOI2017] 不勤劳的图书管理员  考点：树状数组套权值树
 *   https://codeforces.com/problemset/problem/1109/F1  CF2500  CF1109F1 Sasha and Algorithm of Silence's Sounds（树套树思想）  考点：二维统计
 *   https://www.luogu.com.cn/problem/P4690  省选/NOI−  P4690 [Ynoi2016] 镜中的昆虫  考点：树套树 + 分块
 *   https://www.luogu.com.cn/problem/P2132  省选−  P2132 狗男男（二维数据结构练习）  考点：二维树状数组
 *
 */

// TODO：在这里写出实现
