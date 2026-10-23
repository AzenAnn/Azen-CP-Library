/**
 * 06_dp/15 DP 套 DP
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：06_dp/06 状压 DP、06_dp/01 线性 DP 入门与记忆化搜索
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 内层 DP：计算某个具体方案的权值（如 LIS 长度、匹配数）
 *   2. 外层 DP：把内层 DP 的状态作为外层状态的一维
 *   3. 经典模型：统计 LIS 长度 ≤ k 的排列数、LCS 自动机上 DP
 *   4. 自动机视角：内层 DP 状态转移 → 自动机，外层在自动机上计数
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/dp-of-dp/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4590  P4590 [TJOI2018] 游园会（LCS 自动机 DP）
 *   https://www.luogu.com.cn/problem/P5287  P5287 [HNOI2019] JOJO（LIS 套 DP）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4137  省选−  P4137 Rmq Problem / mex（前置：状态设计）  考点：状态设计
 *   https://www.luogu.com.cn/problem/P4590  省选/NOI−  P4590 游园会  考点：LCS 轮廓 DP 套 DP
 *   https://www.luogu.com.cn/problem/P5287  省选/NOI−  P5287 JOJO  考点：LIS 状态压缩套 DP
 *   https://www.luogu.com.cn/problem/P3301  省选/NOI−  P3301 [SDOI2013] 试题（LIS 计数）  考点：DP 套 DP
 *   https://codeforces.com/problemset/problem/448/D  CF2500  CF448D Multiplications（前置：二分答案）  考点：二分 + 计数
 *   https://www.luogu.com.cn/problem/P8350  省选/NOI−  P8350 [SDOI/SXOI2022] 子串统计  考点：DP 套 DP 综合
 *
 */

// TODO：在这里写出实现
