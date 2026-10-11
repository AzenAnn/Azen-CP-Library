/**
 * 07_string/02 KMP 与前缀函数
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 前缀函数 π
 *   2. KMP 字符串匹配
 *   3. 最小循环节
 *   4. KMP 自动机
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/kmp/
 *   cp-algorithms  https://cp-algorithms.com/string/prefix-function.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/strings.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3375  P3375 【模板】KMP
 *   https://www.luogu.com.cn/problem/P4391  P4391 [BalticOI 2009] Radio Transmission 无线传输
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10479  普及  P10479 匹配统计  考点：倍增、二分、哈希 hashing
 *   https://codeforces.com/problemset/problem/182/D  CF1400  CF182D Common Divisors  考点：暴力、哈希、实现
 *   https://www.luogu.com.cn/problem/P5546  普及+/提高−  P5546 [POI 2000 R3] 公共串  考点：二分、哈希 hashing、字典树 Trie
 *   https://www.luogu.com.cn/problem/P9606  普及+/提高−  P9606 [CERC2019] ABB  考点：字符串、哈希 hashing、KMP 算法
 *   https://codeforces.com/problemset/problem/1269/B  CF1500  CF1269B Modulo Equality  考点：暴力、排序
 *   https://codeforces.com/problemset/problem/1137/B  CF1600  CF1137B Camp Schedule  考点：贪心、哈希、字符串
 *   https://codeforces.com/problemset/problem/126/B  CF1700  CF126B Password  考点：二分、DP、哈希
 *   https://codeforces.com/problemset/problem/1690/F  CF1700  CF1690F Shifting String  考点：图论、数学、数论
 *   https://www.luogu.com.cn/problem/P3435  提高  P3435 [POI 2006] OKR-Periods of Words  考点：字符串、KMP 算法
 *   https://www.luogu.com.cn/problem/P8112  提高  P8112 [Cnoi2021] 符文破译  考点：字符串、动态规划 DP、贪心
 *   https://codeforces.com/problemset/problem/471/D  CF1800  CF471D MUH and Cube Walls  考点：后缀结构、字符串
 *   https://codeforces.com/problemset/problem/346/B  CF2000  CF346B Lucky Common Subsequence  考点：DP、字符串
 *   https://www.luogu.com.cn/problem/P3426  提高+/省选−  P3426 [POI 2005] SZA-Template  考点：字符串、动态规划 DP、树形数据结构
 *   https://www.luogu.com.cn/problem/P3538  提高+/省选−  P3538 [POI 2012] OKR-A Horrible Poem  考点：字符串、哈希 hashing
 *   https://codeforces.com/problemset/problem/25/E  CF2200  CF25E Test  考点：哈希、字符串
 *
 */

// 1. 前缀函数：pi[i] 为 s[0..i] 的最长"相等的真前缀与真后缀"的长度，O(n)
vector<int> prefix_function(const string &s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int k = pi[i - 1];
        while (k > 0 && s[i] != s[k]) k = pi[k - 1];   // 失配时跳到次长的相等前后缀
        if (s[i] == s[k]) k++;
        pi[i] = k;
    }
    return pi;
}

// 2. KMP：模式串 t 在文本串 s 中所有出现位置的起始下标（t 非空），O(|s| + |t|)
vector<int> kmp_search(const string &s, const string &t) {
    vector<int> pi = prefix_function(t), res;
    int m = t.size();
    for (int i = 0, k = 0; i < (int)s.size(); i++) {
        while (k > 0 && (k == m || s[i] != t[k])) k = pi[k - 1];
        if (s[i] == t[k]) k++;
        if (k == m) res.push_back(i - m + 1);
    }
    return res;
}

// 3. 最小周期（洛谷 P4391）：s 的最短的 p，使 s[i] = s[i + p] 对所有合法 i 成立，为 n - pi[n-1]
//    若 n % p == 0，s 由长度为 p 的串恰好重复 n / p 次组成；否则 s 是它的若干次重复再截断
int min_period(const string &s) {
    if (s.empty()) return 0;
    return s.size() - prefix_function(s).back();
}
