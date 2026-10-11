/**
 * 07_string/01 字符串哈希
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：05_math/01 取模运算与快速幂
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 多项式哈希与子串哈希 O(1)
 *   2. 自然溢出会被卡，使用随机底数
 *   3. 模 2^61-1 的大模数哈希
 *   4. 二分 + 哈希求最长公共前缀
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/hash/
 *   cp-algorithms  https://cp-algorithms.com/string/string-hashing.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/strings.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3370  P3370 【模板】字符串哈希
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10468  普及  P10468 兔子与兔子  考点：字符串、哈希 hashing
 *   https://www.luogu.com.cn/problem/P2786  普及  P2786 英语1（eng1）- 英语作文  考点：字符串、树形数据结构、平衡树
 *   https://codeforces.com/problemset/problem/1800/D  CF1200  CF1800D Remove Two Letters  考点：数据结构、贪心、哈希
 *   https://codeforces.com/problemset/problem/4/C  CF1300  CF4C Registration System  考点：数据结构、哈希、实现
 *   https://codeforces.com/problemset/problem/1451/C  CF1400  CF1451C String Equality  考点：DP、贪心、哈希
 *   https://www.luogu.com.cn/problem/P1381  普及+/提高−  P1381 单词背诵  考点：模拟、字符串、二分
 *   https://codeforces.com/problemset/problem/1133/D  CF1500  CF1133D Zero Quantity Maximization  考点：哈希、数学、数论
 *   https://codeforces.com/problemset/problem/2/A  CF1500  CF2A Winner  考点：哈希、实现
 *   https://www.luogu.com.cn/problem/P2375  提高  P2375 [NOI2014] 动物园  考点：字符串、递推、倍增
 *   https://www.luogu.com.cn/problem/P4503  提高  P4503 [CTSC2014] 企鹅 QQ  考点：字符串、哈希 hashing
 *   https://www.luogu.com.cn/problem/P4555  提高  P4555 [国家集训队] 最长双回文串  考点：字符串、线段树、枚举
 *   https://www.luogu.com.cn/problem/P4824  提高  P4824 [USACO15FEB] Censoring S  考点：字符串、线段树、哈希 hashing
 *   https://codeforces.com/problemset/problem/1200/E  CF2000  CF1200E Compress Words  考点：暴力、哈希、实现
 *   https://codeforces.com/problemset/problem/514/C  CF2000  CF514C Watto and Mechanism  考点：二分、数据结构、哈希
 *   https://www.luogu.com.cn/problem/P7114  提高+/省选−  P7114 [NOIP2020] 字符串匹配  考点：字符串、倍增、树状数组
 *
 */

// 多项式哈希：h(s) = s[0]*B^(n-1) + s[1]*B^(n-2) + ... + s[n-1]  (mod M)
// 取 M = 2^61 - 1（大质数），底数 B 在运行时随机选取：碰撞概率约 n / 2^61，也不怕被特意构造的数据卡。
// 不要用 unsigned long long 自然溢出（模 2^64），有固定的构造方法可以卡掉。
// 所有 StrHash 对象共用同一个底数，所以不同字符串的子串哈希也可以直接比较。
struct StrHash {
    using u64 = unsigned long long;
    static constexpr u64 M = (1ULL << 61) - 1;
    static u64 mul(u64 a, u64 b) {   // a * b mod (2^61 - 1)
        __uint128_t c = (__uint128_t)a * b;
        u64 r = (u64)(c & M) + (u64)(c >> 61);
        return r >= M ? r - M : r;
    }
    static u64 base() {
        static const u64 B = mt19937_64(chrono::steady_clock::now().time_since_epoch().count())() % (M - 1000) + 500;
        return B;
    }
    vector<u64> h, p;   // h[i]：前 i 个字符的哈希；p[i] = B^i
    StrHash(const string &s) : h(s.size() + 1, 0), p(s.size() + 1, 1) {
        u64 B = base();
        for (size_t i = 0; i < s.size(); i++) {
            h[i + 1] = mul(h[i], B) + (unsigned char)s[i];
            if (h[i + 1] >= M) h[i + 1] -= M;
            p[i + 1] = mul(p[i], B);
        }
    }
    u64 get(int l, int r) const {   // 子串 s[l, r) 的哈希
        u64 x = h[r] + M - mul(h[l], p[r - l]);
        return x >= M ? x - M : x;
    }
};

// 二分 + 哈希：a 从 i 开始、b 从 j 开始的最长公共前缀长度，O(log n)
int hash_lcp(const StrHash &a, int i, const StrHash &b, int j) {
    int lo = 0, hi = min((int)a.h.size() - 1 - i, (int)b.h.size() - 1 - j) + 1;   // 答案在 [lo, hi)
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        (a.get(i, i + mid) == b.get(j, j + mid) ? lo : hi) = mid;
    }
    return lo;
}
