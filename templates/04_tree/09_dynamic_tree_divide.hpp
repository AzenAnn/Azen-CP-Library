/**
 * 04_tree/09 动态点分治（点分树）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：04_tree/07 静态点分治
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 回顾静态点分治：离线处理树上路径统计
 *   2. 点分树：点分治重心构成一棵高 O(log n) 的树
 *   3. 每个节点维护到各祖先重心的距离信息（线段树/平衡树/堆）
 *   4. 支持动态修改 + 查询最近点、距离和等
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/dynamic-tree-divide/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P6329  P6329 【模板】点分树 / 震波
 *   https://www.luogu.com.cn/problem/P3241  P3241 [HNOI2015] 开店
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3806  提高+/省选−  P3806 【模板】点分治 1（静态前置）  考点：点分治
 *   https://www.luogu.com.cn/problem/P6329  省选−  P6329 【模板】点分树 / 震波  考点：动态点分治
 *   https://www.luogu.com.cn/problem/P3241  省选−  P3241 [HNOI2015] 开店  考点：点分树 + 前缀和
 *   https://www.luogu.com.cn/problem/P5306  省选−  P5306 [COCI2019] 交通  考点：点分树应用
 *   https://codeforces.com/problemset/problem/757/G  CF2600  CF757G Can Bash Save the Day?  考点：点分树 + 李超树
 *   https://www.luogu.com.cn/problem/P6620  省选/NOI−  P6620 [2020 年联考 A 卷] 组合数问题  考点：点分树 + 多项式
 *
 */

// TODO：在这里写出实现
