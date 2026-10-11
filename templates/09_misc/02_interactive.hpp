/**
 * 09_misc/02 交互题
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：01_basic/03 二分查找、二分答案与三分
 * 状态：NOTE（没有固定模板，以笔记和题单为主）
 *
 * 【学习顺序】
 *   1. 每次输出后刷新缓冲区
 *   2. 询问次数限制与二分
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/contest/interaction/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/interactive.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1733  P1733 猜数（IO交互版）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10451  普及  P10451 Innovative Business  考点：二分
 *   https://www.luogu.com.cn/problem/P11145  普及  P11145 「SFMOI Round I」Strange Homura Game  考点：Ad-hoc
 *   https://www.luogu.com.cn/problem/P12509  普及  P12509 通信题  考点：哈希 hashing、位运算
 *   https://codeforces.com/problemset/problem/1807/E  CF1300  CF1807E Interview  考点：二分、实现、交互
 *   https://codeforces.com/problemset/problem/1167/B  CF1400  CF1167B Lost Numbers  考点：暴力、分治、交互
 *   https://codeforces.com/problemset/problem/679/A  CF1400  CF679A Bear and Prime 100  考点：构造、交互、数学
 *   https://codeforces.com/problemset/problem/1999/G1  CF1500  CF1999G1 Ruler (easy version)  考点：二分、交互
 *   https://codeforces.com/problemset/problem/1407/C  CF1600  CF1407C Chocolate Bunny  考点：构造、交互、数学
 *   https://codeforces.com/problemset/problem/1479/A  CF1700  CF1479A Searching Local Minimum  考点：二分、交互、三分
 *   https://codeforces.com/problemset/problem/1999/G2  CF1700  CF1999G2 Ruler (hard version)  考点：二分、交互、三分
 *   https://codeforces.com/problemset/problem/1556/D  CF1800  CF1556D Take a Guess  考点：位运算、构造、交互
 *   https://codeforces.com/problemset/problem/1486/C2  CF1900  CF1486C2 Guessing the Greatest (hard version)  考点：二分、交互
 *   https://codeforces.com/problemset/problem/1521/C  CF2000  CF1521C Nastia and a Hidden Permutation  考点：构造、交互
 *   https://codeforces.com/problemset/problem/1634/D  CF2000  CF1634D Finding Zero  考点：构造、交互、数学
 *   https://codeforces.com/problemset/problem/1363/D  CF2100  CF1363D Guess The Maximums  考点：二分、实现、交互
 *
 */

// 本专题没有固定的代码模板，重点是理解思路、积累模型：
//   1. 按上面【学习顺序】逐项学习，把每种模型的直观理解写进【我的笔记】；
//   2. 典型题的完整代码放在 solutions/ 中，在【题单】里写上链接和一句话提示。
// 交互题要点：
//   - 每次输出询问后必须刷新缓冲区：cout << ... << endl;  或  cout.flush();  （printf 用 fflush(stdout)）
//   - 先算清楚询问次数上限，常见做法是二分（log2(1e9) ≈ 30 次）
//   - 本地调试可以自己写一个"交互器"程序，或者先手动输入回答
