/**
 * 08_geometry/10 最小圆覆盖
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：08_geometry/01 点、向量与基本运算
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 定理：最小覆盖圆由 2 个点（直径）或 3 个点（外接圆）确定
 *   2. 随机增量法：随机打乱后，若新点不在当前圆内，则以该点为边界递归求解
 *   3. 期望 O(n)：三层循环 + 随机打乱保证期望线性
 *   4. 精度处理：eps 判断点是否在圆内
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/geometry/smallest-enclosing-circle/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1742  P1742 最小圆覆盖
 *   https://www.luogu.com.cn/problem/P2533  P2533 [AHOI2012] 信号塔（应用）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1742  提高+  P1742 最小圆覆盖  考点：随机增量法
 *   https://www.luogu.com.cn/problem/P2533  提高+  P2533 信号塔  考点：最小圆覆盖应用
 *   https://www.luogu.com.cn/problem/P4280  省选−  P4280 [AHOI2008] 矩形藏身处（几何变形）  考点：几何 + 二分
 *   https://codeforces.com/problemset/problem/119/B  CF1800  CF119B Before Exam（前置：几何枚举）  考点：枚举 + 几何
 *   https://www.luogu.com.cn/problem/P1357  提高+  P1357 花园（圆覆盖思想）  考点：几何
 *   https://www.luogu.com.cn/problem/P3833  省选−  P3833 [SHOI2012] 魔法树（几何建模）  考点：综合
 *
 */

// TODO：在这里写出实现
