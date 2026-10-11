/**
 * 06_dp/15 WQS 二分与 Slope Trick
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：06_dp/10 斜率优化 DP
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. WQS 二分：限制选 k 个 → 每选一个附带 λ 惩罚，二分 λ 使最优解恰好选 k 个
 *   2. 要求：f(k)（选 k 个的最优值）关于 k 是凸/凹函数
 *   3. 内层 DP 需同时维护"值"和"选的个数"，平局取个数多/少
 *   4. Slope Trick：维护分段线性凸函数（拐点多重集合），支持平移、取 min、合并
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/opt/wqs-binary-search/
 *   OI-wiki        https://oi-wiki.org/dp/opt/slope-trick/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2619  P2619 [国家集训队] Tree I（WQS 二分）
 *   https://www.luogu.com.cn/problem/P2892  P2892 [USACO07OPEN] Dining G（Slope Trick 前置：带权中位数）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P5631  提高+  P5631 最小生成树计数（前置：MST 变形）  考点：MST 计数
 *   https://www.luogu.com.cn/problem/P2619  省选−  P2619 Tree I  考点：WQS 二分 + MST
 *   https://www.luogu.com.cn/problem/P4983  省选−  P4983 忘情  考点：WQS + 斜率优化
 *   https://codeforces.com/problemset/problem/739/E  CF2900  CF739E Gosha is hunting  考点：WQS 二维费用流
 *   https://www.luogu.com.cn/problem/P4331  省选−  P4331 [BalticOI 2004] Sequence  考点：Slope Trick / 左偏树
 *   https://codeforces.com/problemset/problem/713/C  CF2300  CF713C Sonya and Problem Wihtout a Legend  考点：Slope Trick 模板
 *   https://www.luogu.com.cn/problem/P3648  省选/NOI−  P3648 [APIO2014] 序列分割  考点：斜率优化（WQS 前置）
 *
 */

// TODO：在这里写出实现
