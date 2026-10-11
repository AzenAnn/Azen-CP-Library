/**
 * 02_ds/05 ST 表
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：01_basic/09 倍增
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 静态区间最值 RMQ
 *   2. 可重复贡献问题：gcd / and / or
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/sparse-table/
 *   cp-algorithms  https://cp-algorithms.com/data_structures/sparse-table.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/sparse_table.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3865  P3865 【模板】ST 表 & RMQ 问题
 *   https://www.luogu.com.cn/problem/P2880  P2880 [USACO07JAN] Balanced Lineup G
 *   https://judge.yosupo.jp/problem/staticrmq  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1106  普及  P1106 删数问题  考点：字符串、贪心、ST 表
 *   https://www.luogu.com.cn/problem/P1816  普及  P1816 忠诚  考点：线段树、倍增、树状数组
 *   https://www.luogu.com.cn/problem/P1890  普及  P1890 gcd 区间  考点：数学、线段树、最大公约数 gcd
 *   https://www.luogu.com.cn/problem/P4086  普及  P4086 [USACO17DEC] My Cow Ate My Homework S  考点：递推、线段树、枚举
 *   https://www.luogu.com.cn/problem/P2422  普及+/提高−  P2422 良好的感觉  考点：线段树、倍增、二分
 *   https://www.luogu.com.cn/problem/P3901  普及+/提高−  P3901 数列找不同  考点：模拟、莫队、线段树
 *   https://www.luogu.com.cn/problem/P6510  普及+/提高−  P6510 奶牛排队  考点：单调队列、分治、栈
 *   https://www.luogu.com.cn/problem/P8818  普及+/提高−  P8818 [CSP-S 2022] 策略游戏  考点：贪心、线段树、ST 表
 *   https://codeforces.com/problemset/problem/1709/D  CF1700  CF1709D Rorororobot  考点：二分、数据结构、贪心
 *   https://codeforces.com/problemset/problem/2050/F  CF1700  CF2050F Maximum modulo equality  考点：数据结构、分治、数学
 *   https://www.luogu.com.cn/problem/P2471  提高  P2471 [SCOI2007] 降雨量  考点：线段树、离散化、ST 表
 *   https://codeforces.com/problemset/problem/1548/B  CF1800  CF1548B Integers Have Friends  考点：二分、数据结构、分治
 *   https://www.luogu.com.cn/problem/P3295  提高+/省选−  P3295 [SCOI2016] 萌萌哒  考点：并查集、枚举、分块
 *   https://www.luogu.com.cn/problem/P3793  提高+/省选−  P3793 由乃救爷爷  考点：线段树、栈、分块
 *   https://codeforces.com/problemset/problem/689/D  CF2100  CF689D Friends and Subsequences  考点：二分、数据结构
 *
 */

// ST 表：O(n log n) 预处理，O(1) 查询静态区间的"可重复贡献"信息
// 可重复贡献：op(x, x) = x，如 max / min / gcd / and / or（区间和不行，用前缀和）
// 下标从 0 开始，查询区间左闭右开 [l, r)，要求 l < r
// 用法：SparseTable st(a, [](ll x, ll y) { return max(x, y); });
//       st.query(l, r);
template <class T, class Op>
struct SparseTable {
    vector<vector<T>> st;   // st[k][i] = op(a[i], ..., a[i + 2^k - 1])
    Op op;
    SparseTable(const vector<T> &a, Op op) : op(op) {
        int n = a.size(), K = n ? __lg(n) + 1 : 1;
        st.assign(K, a);
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                st[k][i] = op(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }
    T query(int l, int r) const {
        int k = __lg(r - l);   // 两段长度为 2^k 的区间可以覆盖 [l, r)（允许重叠）
        return op(st[k][l], st[k][r - (1 << k)]);
    }
};
