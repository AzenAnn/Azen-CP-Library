/**
 * 01_basic/06 位运算
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 基本操作与 __builtin 系列函数
 *   2. lowbit 与枚举二进制位
 *   3. 枚举子集
 *   4. 前缀异或
 *   5. 拆位算贡献
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/bit/
 *   cp-algorithms  https://cp-algorithms.com/algebra/bit-manipulation.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/bits.go
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4702  入门  P4702 取石子  考点：博弈论、进制、前缀和
 *   https://www.luogu.com.cn/problem/P9496  入门  P9496 「RiOI-2」hacker  考点：位运算
 *   https://codeforces.com/problemset/problem/1915/A  CF800  CF1915A Odd One Out  考点：位运算、实现
 *   https://codeforces.com/problemset/problem/1915/B  CF800  CF1915B Not Quite Latin Square  考点：位运算、暴力、实现
 *   https://codeforces.com/problemset/problem/1907/B  CF1000  CF1907B YetnotherrokenKeoard  考点：数据结构、实现、字符串
 *   https://codeforces.com/problemset/problem/1682/B  CF1100  CF1682B AND Sorting  考点：位运算、构造、排序
 *   https://codeforces.com/problemset/problem/2074/C  CF1100  CF2074C XOR and Triangle  考点：位运算、暴力、计算几何
 *   https://codeforces.com/problemset/problem/2162/C  CF1100  CF2162C Beautiful XOR  考点：位运算、构造、贪心
 *   https://www.luogu.com.cn/problem/P2420  普及  P2420 让我们异或吧  考点：树的遍历、前缀和、差分
 *   https://codeforces.com/problemset/problem/1420/B  CF1200  CF1420B Rock and Lever  考点：位运算、数学
 *   https://codeforces.com/problemset/problem/1909/B  CF1200  CF1909B Make Almost Equal With Mod  考点：位运算、构造、数学
 *   https://codeforces.com/problemset/problem/1601/A  CF1300  CF1601A Array Elimination  考点：位运算、贪心、数学
 *   https://codeforces.com/problemset/problem/1362/C  CF1400  CF1362C Johnny and Another Rating Drop  考点：位运算、贪心、数学
 *   https://codeforces.com/problemset/problem/1513/B  CF1400  CF1513B AND Sequences  考点：位运算、组合数学、构造
 *   https://codeforces.com/problemset/problem/2020/C  CF1400  CF2020C Bitwise Balancing  考点：位运算、哈希、实现
 *
 */

// 1. 常用操作（ll 版本的函数名加 ll，如 __builtin_popcountll）
//    x >> k & 1           取第 k 位
//    x | (1 << k)         第 k 位置 1；  x & ~(1 << k) 置 0；  x ^ (1 << k) 翻转
//    x & -x               lowbit：最低位的 1 所代表的值
//    x & (x - 1)          去掉最低位的 1
//    __builtin_popcount(x)            二进制中 1 的个数
//    __builtin_ctz(x)                 末尾 0 的个数（x != 0）
//    __lg(x) = 31 - __builtin_clz(x)  最高位 1 的位置（x != 0）
//    注意：1 << k 是 int，k >= 31 时要写 1LL << k

// 2. 枚举 mask 的所有子集（从大到小，包含空集）
//    对所有 mask 都枚举一遍子集，总复杂度 O(3^n)
template <class F>
void for_each_subset(int mask, F f) {
    for (int s = mask;; s = (s - 1) & mask) {
        f(s);
        if (s == 0) break;
    }
}

// 3. 枚举 n 位中恰有 k 个 1 的所有集合（Gosper's hack），按数值从小到大
template <class F>
void for_each_k_subset(int n, int k, F f) {
    if (k == 0) { f(0); return; }
    for (int s = (1 << k) - 1; s < (1 << n);) {
        f(s);
        int c = s & -s, r = s + c;
        s = (((r ^ s) >> 2) / c) | r;
    }
}

// 4. 前缀异或：p[i] = a[0] ^ ... ^ a[i-1]，区间 [l, r) 的异或 = p[r] ^ p[l]

// 5. 拆位算贡献：所有数对 (i < j) 的 a[i] ^ a[j] 之和。
//    对每一位，异或为 1 当且仅当一个是 0、一个是 1，贡献为 cnt0 * cnt1 * 2^b
ll pair_xor_sum(const vector<ll> &a, int bits = 31) {
    ll ans = 0, n = a.size();
    for (int b = 0; b < bits; b++) {
        ll c1 = 0;
        for (ll x : a) c1 += x >> b & 1;
        ans += c1 * (n - c1) << b;
    }
    return ans;
}
