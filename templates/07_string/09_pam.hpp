/**
 * 07_string/09 回文自动机（PAM）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：07_string/04 Manacher 最长回文子串
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 回文树的构造
 *   2. 本质不同回文子串
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/pam/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/pam.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5496  P5496 【模板】回文树 / 回文自动机（PAM）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P12671  省选/NOI−  P12671 「TFXOI Round 2」String  考点：倍增、二分、回文自动机 PAM
 *   https://www.luogu.com.cn/problem/P16693  省选/NOI−  P16693 Tokitsukaze and Palindrome Border  考点：线段树、树链剖分、虚树
 *   https://www.luogu.com.cn/problem/P3649  省选/NOI−  P3649 [APIO2014] 回文串  考点：字符串、后缀自动机 SAM、后缀数组 SA
 *   https://www.luogu.com.cn/problem/P4287  省选/NOI−  P4287 [SHOI2011] 双倍回文  考点：字符串、回文自动机 PAM、Manacher 算法
 *   https://www.luogu.com.cn/problem/P4762  省选/NOI−  P4762 [CERC2014] Virus synthesis  考点：回文自动机 PAM
 *   https://www.luogu.com.cn/problem/P5555  省选/NOI−  P5555 秩序魔咒  考点：字符串、后缀自动机 SAM、哈希 hashing
 *   https://www.luogu.com.cn/problem/P5685  省选/NOI−  P5685 [JSOI2013] 快乐的 JYY  考点：字符串、后缀自动机 SAM、回文自动机 PAM
 *   https://www.luogu.com.cn/problem/P6396  省选/NOI−  P6396 要有光  考点：字符串、动态规划 DP、图论
 *   https://www.luogu.com.cn/problem/P8406  省选/NOI−  P8406 [COCI 2021/2022 #6]  Palindromi  考点：回文自动机 PAM
 *   https://codeforces.com/problemset/problem/932/G  CF2900  CF932G Palindrome Partition  考点：DP、后缀结构、字符串
 *   https://www.luogu.com.cn/problem/P14185  NOI/NOI+/CTS  P14185 回文子串划分计数  考点：字符串、回文自动机 PAM
 *   https://www.luogu.com.cn/problem/P14771  NOI/NOI+/CTS  P14771 [ICPC 2024 Seoul R] Palindromic Length  考点：回文自动机 PAM
 *
 */

// 回文自动机（回文树，PAM）：每个节点对应 s 的一个本质不同的回文子串（最多 n 个），线性构造。
// 两个根：节点 0 为长度 0 的"偶根"，节点 1 为长度 -1 的"奇根"。ch[v][c] 表示在回文串 v 两端各加一个 c。
// fail[v] 指向 v 的最长回文真后缀。逐个加入字符，从上一个位置的最长回文后缀开始沿 fail 跳，
// 找到第一个能在两端扩展的回文串。只处理小写字母
struct PAM {
    vector<array<int, 26>> ch;
    vector<int> len, fail, cnt, num;   // cnt：作为"最长回文后缀"出现的次数；num：以该节点结尾的回文后缀个数
    string s;
    int last = 0;
    vector<int> suffix_count;   // suffix_count[i]：以 s[i] 结尾的回文子串个数（洛谷 P5496）
    PAM() {
        new_node(0), new_node(-1);
        fail[0] = 1, fail[1] = 0;
    }
    int new_node(int l) {
        ch.push_back({}), ch.back().fill(0);
        len.push_back(l), fail.push_back(0), cnt.push_back(0), num.push_back(0);
        return len.size() - 1;
    }
    int get_fail(int x, int i) const {   // 沿 fail 跳到第一个满足 s[i - len - 1] == s[i] 的回文串
        while (i - len[x] - 1 < 0 || s[i - len[x] - 1] != s[i]) x = fail[x];
        return x;
    }
    void add(char c) {
        s += c;
        int i = s.size() - 1, x = c - 'a';
        int cur = get_fail(last, i);
        if (!ch[cur][x]) {
            int now = new_node(len[cur] + 2);
            fail[now] = len[now] == 1 ? 0 : ch[get_fail(fail[cur], i)][x];
            num[now] = num[fail[now]] + 1;
            ch[cur][x] = now;   // 必须在求完 fail 之后再连边
        }
        last = ch[cur][x];
        cnt[last]++;
        suffix_count.push_back(num[last]);
    }
    // 每个回文子串在 s 中出现的次数：按建立顺序倒序，把 cnt 累加到 fail 上
    vector<ll> occurrences() const {
        vector<ll> occ(cnt.begin(), cnt.end());
        for (int v = (int)len.size() - 1; v >= 2; v--) occ[fail[v]] += occ[v];
        return occ;
    }
    int distinct_palindromes() const { return (int)len.size() - 2; }
};
