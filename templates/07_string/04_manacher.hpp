/**
 * 07_string/04 Manacher 最长回文子串
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：07_string/03 Z 函数（扩展 KMP）
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 插入分隔符统一奇偶回文
 *   2. 利用对称性线性求回文半径
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/manacher/
 *   cp-algorithms  https://cp-algorithms.com/string/manacher.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/strings.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3805  P3805 【模板】Manacher
 *   https://judge.yosupo.jp/problem/enumerate_palindromes  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1659  提高  P1659 [国家集训队] 拉拉队排练  考点：字符串、前缀和、回文自动机 PAM
 *   https://www.luogu.com.cn/problem/P1723  提高  P1723 高手过愚人节  考点：字符串、Manacher 算法
 *   https://www.luogu.com.cn/problem/P3501  提高  P3501 [POI 2010] ANT-Antisymmetry  考点：二分、哈希 hashing、Manacher 算法
 *   https://www.luogu.com.cn/problem/P5446  提高  P5446 [THUPC 2018] 绿绿和串串  考点：哈希 hashing、Manacher 算法
 *   https://codeforces.com/problemset/problem/1326/D2  CF1800  CF1326D2 Prefix-Suffix Palindrome (Hard version)  考点：二分、贪心、哈希
 *   https://codeforces.com/problemset/problem/835/D  CF1900  CF835D Palindromic characteristics  考点：暴力、DP、哈希
 *   https://www.luogu.com.cn/problem/P17330  提高+/省选−  P17330 [ICPC 2018 Nanjing R] Mediocre String Problem  考点：字符串、二分、哈希 hashing
 *   https://www.luogu.com.cn/problem/P6216  提高+/省选−  P6216 回文匹配  考点：前缀和、KMP 算法、Manacher 算法
 *   https://codeforces.com/problemset/problem/7/D  CF2200  CF7D Palindrome Degree  考点：哈希、字符串
 *   https://codeforces.com/problemset/problem/1080/E  CF2400  CF1080E Sonya and Matrix Beauty  考点：字符串
 *   https://www.luogu.com.cn/problem/P3546  省选/NOI−  P3546 [POI 2012] PRE-Prefixuffix  考点：字符串、哈希 hashing、线性递推
 *   https://www.luogu.com.cn/problem/P4199  省选/NOI−  P4199 万径人踪灭  考点：字符串、枚举、快速傅里叶变换 FFT
 *   https://www.luogu.com.cn/problem/P4287  省选/NOI−  P4287 [SHOI2011] 双倍回文  考点：字符串、回文自动机 PAM、Manacher 算法
 *   https://www.luogu.com.cn/problem/P9482  省选/NOI−  P9482 [NOI2023] 字符串  考点：字符串、树状数组、哈希 hashing
 *   https://codeforces.com/problemset/problem/1827/C  CF2600  CF1827C Palindrome Partition  考点：二分、暴力、数据结构
 *
 */

// 在字符之间插入 '#'：t = "#s0#s1#...#s(n-1)#"，长度 2n+1，这样奇、偶回文都变成奇回文。
// d[i] 为以 t[i] 为中心的最长回文半径（包含中心），对应 s 中长度为 d[i] - 1 的回文子串。O(n)
vector<int> manacher(const string &s) {
    string t = "#";
    for (char c : s) t += c, t += '#';
    int m = t.size();
    vector<int> d(m);
    for (int i = 0, l = 0, r = -1; i < m; i++) {   // [l, r] 是右端点最靠右的回文
        int k = i > r ? 1 : min(d[l + r - i], r - i + 1);   // 利用对称位置的答案
        while (i - k >= 0 && i + k < m && t[i - k] == t[i + k]) k++;
        d[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }
    return d;
}

// 最长回文子串：返回 {起点, 长度}
pair<int, int> longest_palindrome(const string &s) {
    vector<int> d = manacher(s);
    int best = 0;
    for (int i = 0; i < (int)d.size(); i++)
        if (d[i] > d[best]) best = i;
    int len = d[best] - 1;
    return {(best - len) / 2, len};
}

// O(1) 判断 s[l, r) 是否回文（l < r）：在 t 中的中心为 l + r
bool is_palindrome(const vector<int> &d, int l, int r) { return d[l + r] - 1 >= r - l; }
