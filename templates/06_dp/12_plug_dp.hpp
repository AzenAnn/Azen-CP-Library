/**
 * 06_dp/12 插头 DP（轮廓线 DP）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：06_dp/06 状态压缩 DP
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 轮廓线：逐格转移，记录当前格与上方/左方的连通状态（插头）
 *   2. 括号表示法：每格两状态（无插头/左括号/右括号），用三进制或四进制
 *   3. 最小表示法：对连通块标号，哈希存状态
 *   4. 经典模型：多回路覆盖、单回路（哈密顿）、连通块计数
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/plug/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5056  P5056 【模板】插头 DP / 回路计数
 *   https://www.luogu.com.cn/problem/P2289  P2289 [HNOI2004] 邮递员
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P5056  省选−  P5056 【模板】插头 DP  考点：括号表示法回路
 *   https://www.luogu.com.cn/problem/P2289  省选−  P2289 邮递员  考点：多回路覆盖
 *   https://www.luogu.com.cn/problem/P3190  省选−  P3190 [HNOI2007] 神奇游乐园  考点：插头 DP 取权值最大
 *   https://www.luogu.com.cn/problem/P3272  省选/NOI−  P3272 [SCOI2011] 地板  考点：插头 DP 连通性
 *   https://www.luogu.com.cn/problem/P3886  省选/NOI−  P3886 [JLOI2009] 神秘的生物  考点：单链连通
 *   https://codeforces.com/problemset/problem/11/D  CF2200  CF11D A Simple Task（前置：状压计数）  考点：哈密顿回路
 *
 */

// TODO：在这里写出实现
