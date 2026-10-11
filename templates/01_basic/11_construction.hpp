/**
 * 01_basic/11 构造
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：无
 * 状态：NOTE（没有固定模板，以笔记和题单为主）
 *
 * 【学习顺序】
 *   1. 从小数据找规律
 *   2. 奇偶性与不变量
 *   3. 归纳构造
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/basic/construction/
 *
 * 【我的笔记】
 *   构造题没有固定套路，但有一些常用策略：
 *   1. 从小数据找规律：枚举 n=1,2,3,4...，观察合法解的结构，猜想一般规律。
 *      特别注意 n 为奇数/偶数、质数/合数、2 的幂次时的差异。
 *   2. 奇偶性与不变量：操作往往保持某种不变量（如和 mod 2、黑白染色差、逆序对奇偶性）。
 *      如果目标状态的不变量与初始不同，则无解；否则尝试构造达到目标的操作序列。
 *   3. 归纳构造：假设 n-1 有解，扩展到 n。比如先构造前 n-1 个元素，再插入第 n 个。
 *   4. 分情况讨论：通常按 n 的大小、奇偶性、是否包含特殊值分类。
 *   5. 构造序列类：从特殊序列出发（全相同、等差、交替），再微调满足条件。
 *   6. 利用二进制/位运算：构造满足特定 XOR、AND、OR 条件的数组时，按位独立考虑。
 *   验证方法：写完构造后，手动模拟小样例，再写暴力检查所有小 n 的解是否合法。
 *   易错点：
 *     - 遗漏无解情况的判断。
 *     - 边界情况：n=1、n=2、所有元素相同、目标值恰好等于极值。
 *     - 构造的解不满足题目隐藏约束（如"字典序最小"）。
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1160  普及  P1160 队列安排  考点：模拟、线性数据结构、构造
 *   https://codeforces.com/problemset/problem/1635/C  CF1200  CF1635C Differential Sorting  考点：构造、贪心
 *   https://codeforces.com/problemset/problem/2134/B  CF1200  CF2134B Add 0 or K  考点：构造、数学、数论
 *   https://codeforces.com/problemset/problem/4/B  CF1200  CF4B Before an Exam  考点：构造、贪心
 *   https://codeforces.com/problemset/problem/1838/C  CF1400  CF1838C No Prime Differences  考点：构造、数学、数论
 *   https://codeforces.com/problemset/problem/1974/D  CF1400  CF1974D Ingenuity-2  考点：构造、贪心、实现
 *   https://codeforces.com/problemset/problem/2126/E  CF1400  CF2126E G-C-D, Unlucky!  考点：数学、数论
 *   https://codeforces.com/problemset/problem/1630/A  CF1500  CF1630A And Matching  考点：位运算、构造
 *   https://codeforces.com/problemset/problem/1893/B  CF1700  CF1893B Neutral Tonality  考点：构造、贪心、排序
 *   https://codeforces.com/problemset/problem/2071/C  CF1700  CF2071C Trapmigiano Reggiano  考点：构造、数据结构、搜索
 *   https://codeforces.com/problemset/problem/2112/D  CF1700  CF2112D Reachability and Tree  考点：构造、搜索、图论
 *   https://codeforces.com/problemset/problem/1554/D  CF1800  CF1554D Diane  考点：构造、贪心、字符串
 *   https://codeforces.com/problemset/problem/1558/C  CF2000  CF1558C Bottom-Tier Reversals  考点：构造、贪心
 *   https://codeforces.com/problemset/problem/2146/D2  CF2000  CF2146D2 Max Sum OR (Hard Version)  考点：位运算、构造、分治
 *   https://codeforces.com/problemset/problem/2171/E  CF2000  CF2171E Anisphia Wynn Palettia and Good Permutations  考点：构造、贪心、数论
 *
 */

// 本专题没有固定的代码模板，重点是理解思路、积累模型：
//   1. 按上面【学习顺序】逐项学习，把每种模型的直观理解写进【我的笔记】；
//   2. 典型题的完整代码放在 solutions/ 中，在【题单】里写上链接和一句话提示。
