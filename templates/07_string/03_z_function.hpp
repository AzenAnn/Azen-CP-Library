/**
 * 07_string/03 Z 函数（扩展 KMP）
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：07_string/02 KMP 与前缀函数
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Z 函数的线性求法
 *   2. 用 Z 函数做字符串匹配
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/z-func/
 *   cp-algorithms  https://cp-algorithms.com/string/z-function.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/strings.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5410  P5410 【模板】扩展 KMP / exKMP（Z 函数）
 *   https://judge.yosupo.jp/problem/zalgorithm  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10479  普及  P10479 匹配统计  考点：倍增、二分、哈希 hashing
 *   https://codeforces.com/problemset/problem/2010/C2  CF1700  CF2010C2 Message Transmission Error (hard version)  考点：哈希、后缀结构、字符串
 *   https://www.luogu.com.cn/problem/P13790  提高  P13790 「CZOI-R6」Border  考点：字符串、倍增、二分
 *   https://www.luogu.com.cn/problem/P2375  提高  P2375 [NOI2014] 动物园  考点：字符串、递推、倍增
 *   https://codeforces.com/problemset/problem/535/D  CF1900  CF535D Tavas and Malekas  考点：贪心、哈希、后缀结构
 *   https://codeforces.com/problemset/problem/432/D  CF2000  CF432D Prefixes and Suffixes  考点：DP、后缀结构、字符串
 *   https://www.luogu.com.cn/problem/P17330  提高+/省选−  P17330 [ICPC 2018 Nanjing R] Mediocre String Problem  考点：字符串、二分、哈希 hashing
 *   https://www.luogu.com.cn/problem/P17556  提高+/省选−  P17556 「WWOI R4」WsW 的数字  考点：字符串、动态规划 DP、二分
 *   https://www.luogu.com.cn/problem/P7114  提高+/省选−  P7114 [NOIP2020] 字符串匹配  考点：字符串、倍增、树状数组
 *   https://www.luogu.com.cn/problem/P8698  提高+/省选−  P8698 [蓝桥杯 2019 国 A] 逃出生天  考点：Z 函数
 *   https://codeforces.com/problemset/problem/1968/G2  CF2200  CF1968G2 Division + LCP (hard version)  考点：二分、暴力、数据结构
 *
 */

// 1. Z 函数：z[i] 为 s 与 s[i..] 的最长公共前缀长度，约定 z[0] = n，O(n)
//    维护最靠右的匹配段 [l, r)：s[l, r) = s[0, r - l]，i 在段内时可以利用 z[i - l]
template <class S>
vector<int> z_function(const S &s) {
    int n = s.size();
    vector<int> z(n, 0);
    if (n) z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}

// 2. 用 Z 函数做匹配：对 t + 分隔符 + s 求 Z 函数，z 值等于 |t| 的位置就是一次出现。
//    这里先转成 int 序列，用 -1 作分隔符，保证不会和任何字符相同
vector<int> z_search(const string &s, const string &t) {
    vector<int> c;
    for (char ch : t) c.push_back((unsigned char)ch);
    c.push_back(-1);
    for (char ch : s) c.push_back((unsigned char)ch);
    vector<int> z = z_function(c), res;
    int m = t.size();
    for (int i = 0; i + m <= (int)s.size(); i++)
        if (z[m + 1 + i] >= m) res.push_back(i);
    return res;
}

// 3. 扩展 KMP（洛谷 P5410）：求 s 的每个后缀与 t 的最长公共前缀，
//    就是 z_function(t + 分隔符 + s) 中后半部分的值
