/**
 * 05_math/23 单纯形法（线性规划）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：05_math/09 高斯消元
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 线性规划标准型：max cᵀx, Ax ≤ b, x ≥ 0
 *   2. 单纯形：松弛变量化为等式，转轴操作（pivot）移动顶点
 *   3. 两阶段法处理初始不可行 / Bland 规则防退化环
 *   4. 对偶定理与费用流/网络流的关系
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/simplex/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3337  P3337 [ZJOI2013] 防守阵地（对偶转费用流）
 *   https://www.luogu.com.cn/problem/P3980  P3980 [NOI2008] 志愿者招募（LP / 费用流）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3337  省选−  P3337 防守阵地  考点：LP 对偶 → 费用流
 *   https://www.luogu.com.cn/problem/P3980  省选−  P3980 志愿者招募  考点：LP / 上下界费用流
 *   https://www.luogu.com.cn/problem/P4416  省选−  P4416 [AHOI2009] 中国象棋（前置：LP 建模思想）  考点：建模
 *   https://www.luogu.com.cn/problem/P2053  省选/NOI−  P2053 [SCOI2007] 修车  考点：费用流（LP 特例）
 *   https://www.luogu.com.cn/problem/P4015  省选−  P4015 运输问题  考点：费用流（对偶练习）
 *   https://codeforces.com/problemset/problem/375/E  CF2600  CF375E Red and Black Tree  考点：LP / 贪心 + 费用流
 *
 */

// TODO：在这里写出实现
