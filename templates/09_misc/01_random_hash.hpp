/**
 * 09_misc/01 随机数与防卡哈希
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. mt19937 随机数
 *   2. unordered_map 防卡（splitmix64）
 *   3. 随机化算法的思路
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/misc/rand-technique/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/rand.go
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/hack.go
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P11615  普及  P11615 【模板】哈希表  考点：哈希表
 *   https://www.luogu.com.cn/problem/P16201  普及  P16201 【MX-S13-T1】旋转工艺  考点：二分、前缀和、哈希表
 *   https://www.luogu.com.cn/problem/P3691  普及  P3691 妖精大战争  考点：随机化
 *   https://www.luogu.com.cn/problem/P9914  普及  P9914 「RiOI-3」匀速相遇  考点：双指针 two-pointer、哈希表
 *   https://www.luogu.com.cn/problem/P10277  普及+/提高−  P10277 [USACO24OPEN] Bessie's Interview S  考点：堆、图论建模、哈希表
 *   https://www.luogu.com.cn/problem/P1441  普及+/提高−  P1441 砝码称重  考点：动态规划 DP、搜索、随机化
 *   https://www.luogu.com.cn/problem/P2210  普及+/提高−  P2210 [USACO13OPEN] Haywire B  考点：动态规划 DP、搜索、模拟退火
 *   https://www.luogu.com.cn/problem/P4703  普及+/提高−  P4703 偷上网  考点：计算几何、枚举、向量
 *   https://www.luogu.com.cn/problem/P1054  提高  P1054 [NOIP 2005 提高组] 等价表达式  考点：模拟、字符串、栈
 *   https://www.luogu.com.cn/problem/P4212  提高  P4212 外太空旅行  考点：模拟、枚举、随机化
 *   https://codeforces.com/problemset/problem/1689/D  CF1900  CF1689D Lena and Matrix  考点：数据结构、DP、计算几何
 *   https://codeforces.com/problemset/problem/2014/H  CF1900  CF2014H Robin Hood Archery  考点：数据结构、分治、贪心
 *   https://codeforces.com/problemset/problem/843/B  CF2000  CF843B Interactive LowerBound  考点：暴力、交互、概率期望
 *   https://codeforces.com/problemset/problem/1114/E  CF2200  CF1114E Arithmetic Progression  考点：二分、交互、数论
 *   https://codeforces.com/problemset/problem/1996/G  CF2200  CF1996G Penacony  考点：暴力、数据结构、图论
 *
 */

// 1. 随机数：用 mt19937 / mt19937_64，以时间作种子。不要用 rand()（Windows 上最大只有 32767）
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand_int(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rng); }   // [l, r] 内均匀随机
//    随机打乱：shuffle(a.begin(), a.end(), rng);   （random_shuffle 在 C++17 中已被删除）

// 2. unordered_map 防 hack：默认哈希可以被构造数据卡成 O(n) 一次操作（Codeforces 上很常见）
//    用法：unordered_map<ll, int, SafeHash> mp;     gp_hash_table 同理
struct SafeHash {
    static unsigned long long splitmix64(unsigned long long x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(unsigned long long x) const {
        static const unsigned long long FIXED = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED);
    }
    size_t operator()(const pair<ll, ll> &p) const {   // pair 作为键
        return (*this)(splitmix64(p.first) ^ (unsigned long long)p.second);
    }
};

// 3. 随机化思路：随机打乱输入防止最坏情况；随机选点 / 随机权值做哈希（如集合哈希、树哈希）；
//    多次随机取最优（正确率不够时多跑几次）
