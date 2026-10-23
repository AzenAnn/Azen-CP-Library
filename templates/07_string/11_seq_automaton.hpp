/**
 * 07_string/11 序列自动机
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：07_string/08 后缀自动机（SAM）
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 定义：next[i][c] = 位置 i 之后字符 c 第一次出现的位置
 *   2. 建树 O(n·|Σ|)，查询子序列匹配 O(m)
 *   3. 与 SAM 区别：序列自动机判断子序列，SAM 判断子串
 *   4. 应用：子序列判定、贪心匹配、子序列计数 DP 辅助
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/seq-automaton/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5826  P5826 【模板】子序列自动机
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/91/A  CF1500  CF91A Newspaper Headline  考点：序列自动机：贪心跳到下一次出现的位置
 *   https://www.luogu.com.cn/problem/P1819  提高+/省选−  P1819 公共子序列  考点：三个串分别建序列自动机，记忆化计数公共子序列
 *   https://www.luogu.com.cn/problem/P3856  提高+/省选−  P3856 [TJOI2008] 公共子串  考点：动态规划 DP、枚举
 *   https://www.luogu.com.cn/problem/P4112  省选/NOI−  P4112 [HEOI2015] 最短不公共子串  考点：SAM + 序列自动机上 BFS 求最短不公共子串 / 子序列
 *   https://www.luogu.com.cn/problem/P4608  省选/NOI−  P4608 [FJOI2016] 所有公共子序列问题  考点：序列自动机上 DFS 输出所有公共子序列（高精度计数）
 *
 */

// 子序列自动机：nxt[i][c] = 位置 i 及之后字符 c 第一次出现的位置（没有为 n）。O(n·|Σ|) 建表。
// 1. is_subsequence(t)：贪心地每次跳到最早的匹配位置，O(|t|)
// 2. count_distinct_subsequences()：本质不同子序列个数（含空串）。自动机上从状态 0 出发的路径数：
//    g[i] = 1 + Σ_c g[nxt[i][c] + 1]，O(n·|Σ|)
// 字符集默认小写字母；字符集很大时把 nxt 换成"每个字符的出现位置表 + 二分"，每步 O(log n)。
struct SeqAutomaton {
    int n;
    vector<array<int, 26>> nxt;   // nxt[i]，i = 0..n
    SeqAutomaton(const string &s) : n(s.size()), nxt(n + 1) {
        nxt[n].fill(n);
        for (int i = n - 1; i >= 0; i--) nxt[i] = nxt[i + 1], nxt[i][s[i] - 'a'] = i;
    }
    bool is_subsequence(const string &t) const {
        int p = 0;
        for (char ch : t) {
            if (p > n) return false;
            int q = nxt[min(p, n)][ch - 'a'];
            if (q == n) return false;
            p = q + 1;
        }
        return true;
    }
    ll count_distinct_subsequences(ll mod) const {
        vector<ll> g(n + 2, 0);
        for (int i = n; i >= 0; i--) {
            g[i] = 1 % mod;
            for (int c = 0; c < 26; c++)
                if (nxt[i][c] < n) g[i] = (g[i] + g[nxt[i][c] + 1]) % mod;
        }
        return g[0];
    }
};
