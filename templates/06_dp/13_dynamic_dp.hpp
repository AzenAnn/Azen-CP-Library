/**
 * 06_dp/13 动态 DP
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：06_dp/05 树形 DP、05_math/07 矩阵乘法 / 矩阵快速幂
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 问题模型：DP 状态转移带修改（如带修的树上最大独立集）
 *   2. 矩阵描述转移：把 DP 转移写成 (max,+) 或 (+,×) 矩阵乘法
 *   3. 树链剖分维护矩阵乘积，修改点权 → 路径矩阵乘更新
 *   4. 广义矩阵乘法：max-plus、min-plus 半环
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/dynamic/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4719  P4719 【模板】"动态 DP" & 动态树分治
 *   https://www.luogu.com.cn/problem/P5024  P5024 [NOIP2018 提高组] 保卫王国
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4719  省选−  P4719 【模板】动态 DP  考点：树剖 + 矩阵
 *   https://www.luogu.com.cn/problem/P5024  省选−  P5024 保卫王国  考点：动态 DP 强制选/不选
 *   https://www.luogu.com.cn/problem/P4751  省选/NOI−  P4751 动态 DP【加强版】  考点：全局平衡二叉树
 *   https://codeforces.com/problemset/problem/750/E  CF2600  CF750E New Year and Old Subsequence  考点：序列自动机 + 矩阵
 *   https://www.luogu.com.cn/problem/P6021  省选/NOI−  P6021 洪水  考点：动态 DP 应用
 *   https://www.luogu.com.cn/problem/P6773  省选/NOI−  P6773 [NOI2020] 命运  考点：动态 DP + 树剖
 *
 */

// TODO：在这里写出实现
