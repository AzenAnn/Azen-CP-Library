/**
 * 07_string/07 后缀数组
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：01_basic/05 排序与离散化
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 倍增 + 基数排序求 SA
 *   2. height 数组
 *   3. 本质不同子串个数
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/sa/
 *   cp-algorithms  https://cp-algorithms.com/string/suffix-array.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/strings.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3809  P3809 【模板】后缀排序（SA）
 *   https://judge.yosupo.jp/problem/suffixarray  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/123/D  CF2300  CF123D String  考点：后缀结构
 *   https://codeforces.com/problemset/problem/149/E  CF2300  CF149E Martian Strings  考点：后缀结构、字符串
 *   https://codeforces.com/problemset/problem/557/E  CF2300  CF557E Ann and Half-Palindrome  考点：数据结构、DP、图论
 *   https://codeforces.com/problemset/problem/727/E  CF2300  CF727E Games on a CD  考点：数据结构、哈希、后缀结构
 *   https://codeforces.com/problemset/problem/802/G3  CF2300  CF802G3 Fake News (hard)  考点：后缀结构
 *   https://www.luogu.com.cn/problem/P1117  省选/NOI−  P1117 [NOI2016] 优秀的拆分  考点：字符串、枚举、ST 表
 *   https://www.luogu.com.cn/problem/P2178  省选/NOI−  P2178 [NOI2015] 品酒大会  考点：并查集、后缀数组 SA、单调栈
 *   https://www.luogu.com.cn/problem/P3975  省选/NOI−  P3975 [TJOI2015] 弦论  考点：二分、后缀自动机 SAM、枚举
 *   https://www.luogu.com.cn/problem/P4070  省选/NOI−  P4070 [SDOI2016] 生成魔咒  考点：字符串、平衡树、后缀自动机 SAM
 *   https://www.luogu.com.cn/problem/P6095  省选/NOI−  P6095 [JSOI2015] 串分割  考点：二分、后缀数组 SA
 *   https://codeforces.com/problemset/problem/1654/F  CF2800  CF1654F Minimal String Xoration  考点：位运算、数据结构、分治
 *   https://codeforces.com/problemset/problem/547/E  CF2800  CF547E Mike and Friends  考点：数据结构、后缀结构、字符串
 *   https://www.luogu.com.cn/problem/P4094  NOI/NOI+/CTS  P4094 [HEOI2016/TJOI2016] 字符串  考点：线段树、二分、后缀自动机 SAM
 *   https://www.luogu.com.cn/problem/P4770  NOI/NOI+/CTS  P4770 [NOI2018] 你的名字  考点：线段树、后缀自动机 SAM、可持久化线段树
 *   https://www.luogu.com.cn/problem/P7361  NOI/NOI+/CTS  P7361 「JZOI-1」拜神  考点：后缀自动机 SAM、后缀数组 SA
 *
 */

// 后缀数组：sa[i] 为字典序第 i 小的后缀的起始位置（洛谷 P3809）。
// 倍增：已知所有长度为 2^h 的子串的排名，长度为 2^(h+1) 的子串可以看作二元组 (前半排名, 后半排名) 排序，
// 用基数排序（计数排序）每轮 O(n)，共 O(log n) 轮，总 O(n log n)。
// 这里在末尾加一个比所有字符都小的哨兵，按循环移位排序（cp-algorithms 的写法）
vector<int> suffix_array(const string &str) {
    vector<int> s;
    for (char ch : str) s.push_back((unsigned char)ch + 1);
    s.push_back(0);   // 哨兵
    int n = s.size(), alphabet = 257;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    int classes = 1;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]]) classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; h++) {
        for (int i = 0; i < n; i++) pn[i] = (p[i] - (1 << h) + n) % n;   // 按后半部分排好序后，前移 2^h
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];   // 再按前半部分稳定排序
        cn[p[0]] = 0, classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur{c[p[i]], c[(p[i] + (1 << h)) % n]}, prev{c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
            if (cur != prev) classes++;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    p.erase(p.begin());   // 去掉哨兵对应的后缀
    return p;
}

// height 数组（Kasai 算法，O(n)）：lcp[i] 为后缀 sa[i] 与 sa[i-1] 的最长公共前缀，lcp[0] = 0。
// 利用性质：rank[i+1] 对应的 lcp >= rank[i] 对应的 lcp - 1
vector<int> lcp_array(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rk(n), lcp(n, 0);
    for (int i = 0; i < n; i++) rk[sa[i]] = i;
    for (int i = 0, k = 0; i < n; i++) {
        if (rk[i] == 0) { k = 0; continue; }
        if (k) k--;
        int j = sa[rk[i] - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rk[i]] = k;
    }
    return lcp;
}

// 应用：本质不同的子串个数 = 所有后缀的长度之和 - Σ lcp
//       任意两个后缀的 LCP = lcp 数组上一段区间的最小值（配合 ST 表）
ll distinct_substrings(const string &s) {
    ll n = s.size(), res = n * (n + 1) / 2;
    for (int x : lcp_array(s, suffix_array(s))) res -= x;
    return res;
}
