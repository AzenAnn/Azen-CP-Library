/**
 * 05_math/10 线性基
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：01_basic/06 位运算
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 插入与求最大异或和
 *   2. 第 k 小异或和
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/linear-algebra/basis/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math_matrix.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3812  P3812 【模板】线性基
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P11146  提高  P11146 「SFMOI Round I」Strange Train Game  考点：贪心、并查集、图论建模
 *   https://www.luogu.com.cn/problem/P14526  提高  P14526 [BYOI R1] 心之所愿  考点：线性基、bitset
 *   https://www.luogu.com.cn/problem/P17127  提高  P17127 [ICPC 2025 Shanghai R] Gemcrate  考点：贪心、线性基、位运算
 *   https://www.luogu.com.cn/problem/P2447  提高  P2447 [SDOI2010] 外星千足虫  考点：高斯消元、线性基、位运算
 *   https://www.luogu.com.cn/problem/P3857  提高  P3857 [TJOI2008] 彩灯  考点：进制、线性基
 *   https://codeforces.com/problemset/problem/895/C  CF2000  CF895C Square Subsets  考点：位运算、组合数学、DP
 *   https://www.luogu.com.cn/problem/P4301  提高+/省选−  P4301 [CQOI2013] 新Nim游戏  考点：贪心、博弈论、线性基
 *   https://www.luogu.com.cn/problem/P4570  提高+/省选−  P4570 [BJWC2011] 元素  考点：贪心、线性基
 *   https://codeforces.com/problemset/problem/1101/G  CF2300  CF1101G (Zero XOR Subset)-less  考点：数学、矩阵
 *   https://codeforces.com/problemset/problem/845/G  CF2300  CF845G Shortest Path Problem?  考点：搜索、图论、数学
 *   https://codeforces.com/problemset/problem/959/F  CF2400  CF959F Mahmoud and Ehab and yet another xor task  考点：位运算、DP、数学
 *   https://www.luogu.com.cn/problem/P3292  省选/NOI−  P3292 [SCOI2016] 幸运数字  考点：倍增、最近公共祖先 LCA、线性基
 *   https://www.luogu.com.cn/problem/P4151  省选/NOI−  P4151 [WC2011] 最大 XOR 和路径  考点：图论、贪心、枚举
 *   https://codeforces.com/problemset/problem/1100/F  CF2500  CF1100F Ivan and Burgers  考点：数据结构、分治、贪心
 *   https://codeforces.com/problemset/problem/1427/E  CF2500  CF1427E Xum  考点：位运算、构造、数学
 *
 */

// 线性基（异或基）：用最多 60 个数表示一个集合所有子集的异或值。
// b[i] 为最高位是第 i 位的基向量。插入 x 时从高位到低位，若 b[i] 存在就异或掉，否则 x 成为新的 b[i]。
struct LinearBasis {
    static const int B = 60;   // 处理 [0, 2^60) 的数
    ll b[B] = {};
    int cnt = 0;               // 基的大小
    bool has_zero = false;     // 是否有非空子集的异或为 0（插入时出现过线性相关）
    bool insert(ll x) {        // 返回 x 是否使基变大
        for (int i = B - 1; i >= 0; i--) {
            if (!(x >> i & 1)) continue;
            if (!b[i]) { b[i] = x, cnt++; return true; }
            x ^= b[i];
        }
        has_zero = true;
        return false;
    }
    bool contains(ll x) const {   // x 能否由若干个（可以是 0 个）数异或得到
        for (int i = B - 1; i >= 0; i--)
            if (x >> i & 1) x ^= b[i];
        return x == 0;
    }
    ll max_xor(ll init = 0) const {   // 子集异或（再异或上 init）的最大值：从高位贪心
        ll r = init;
        for (int i = B - 1; i >= 0; i--) r = max(r, r ^ b[i]);
        return r;
    }
    ll min_xor() const {   // 非空子集异或的最小值
        if (has_zero) return 0;
        for (int i = 0; i < B; i++)
            if (b[i]) return b[i];
        return -1;   // 一个数都没有插入
    }
    // 非空子集异或值（去重后）中第 k 小，k 从 1 开始；不存在返回 -1。
    // 先把基消成"每个主元位只在自己的基向量中出现"，k 的二进制就对应选哪些基向量
    ll kth(ll k) const {
        vector<ll> v;
        ll c[B];
        copy(b, b + B, c);
        for (int i = B - 1; i >= 0; i--)
            for (int j = i - 1; j >= 0; j--)
                if (c[i] >> j & 1) c[i] ^= c[j];
        for (int i = 0; i < B; i++)
            if (c[i]) v.push_back(c[i]);
        if (has_zero) {
            if (k == 1) return 0;
            k--;
        }
        if (k >= (1LL << v.size())) return -1;
        ll r = 0;
        for (size_t i = 0; i < v.size(); i++)
            if (k >> i & 1) r ^= v[i];
        return r;
    }
};
