/**
 * 05_math/08 矩阵与矩阵快速幂
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：05_math/01 取模运算与快速幂
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 矩阵乘法
 *   2. 矩阵快速幂加速线性递推
 *   3. 广义矩阵乘法（min, +）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/linear-algebra/matrix/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math_matrix.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3390  P3390 【模板】矩阵快速幂
 *   https://www.luogu.com.cn/problem/P1962  P1962 斐波那契数列
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P13417  普及  P13417 [COCI 2012/2013 #4] DLAKAVAC  考点：动态规划 DP、数学、递推
 *   https://www.luogu.com.cn/problem/P16055  普及  P16055 [CSPro 31] 坐标变换（其二）  考点：数学、线段树、前缀和
 *   https://www.luogu.com.cn/problem/P7318  普及  P7318 「PMOI-4」人赢  考点：数学、枚举、矩阵乘法
 *   https://codeforces.com/problemset/problem/450/B  CF1300  CF450B Jzzhu and Sequences  考点：实现、数学
 *   https://www.luogu.com.cn/problem/P1349  普及+/提高−  P1349 广义斐波那契数列  考点：数学、矩阵加速、矩阵乘法
 *   https://www.luogu.com.cn/problem/P1939  普及+/提高−  P1939 矩阵加速（数列）  考点：数学、矩阵运算、矩阵加速
 *   https://www.luogu.com.cn/problem/P9777  普及+/提高−  P9777 [HUSTFC 2023] Fujisaki 讨厌数学  考点：矩阵加速
 *   https://codeforces.com/problemset/problem/166/E  CF1500  CF166E Tetrahedron  考点：DP、数学、矩阵
 *   https://www.luogu.com.cn/problem/P1306  提高  P1306 斐波那契公约数  考点：数学、倍增、线性数据结构
 *   https://www.luogu.com.cn/problem/P3216  提高  P3216 [HNOI2011] 数学作业  考点：数学、递推、矩阵乘法
 *   https://codeforces.com/problemset/problem/222/E  CF1900  CF222E Decoding Genome  考点：DP、矩阵
 *   https://codeforces.com/problemset/problem/691/E  CF1900  CF691E Xor-sequences  考点：矩阵
 *   https://codeforces.com/problemset/problem/621/E  CF2000  CF621E Wet Shark and Blocks  考点：DP、矩阵
 *   https://codeforces.com/problemset/problem/1117/D  CF2100  CF1117D Magic Gems  考点：DP、数学、矩阵
 *   https://codeforces.com/problemset/problem/514/E  CF2200  CF514E Darth Vader and Tree  考点：DP、矩阵
 *
 */

// 矩阵用 vector<vector<ll>> 表示，所有运算对 mod 取模（要求 mod < 3e9，乘积不溢出 ll）
using Mat = vector<vector<ll>>;

// 1. 矩阵乘法 (n×k) * (k×m)，O(nkm)。按 i-k-j 的顺序循环，访问内存连续，更快
Mat mat_mul(const Mat &a, const Mat &b, ll mod) {
    int n = a.size(), K = b.size(), m = b[0].size();
    Mat c(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < K; k++) {
            if (!a[i][k]) continue;
            for (int j = 0; j < m; j++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
        }
    return c;
}

// 2. 矩阵快速幂：方阵 a 的 e 次方，O(n^3 log e)
Mat mat_pow(Mat a, ll e, ll mod) {
    int n = a.size();
    Mat r(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) r[i][i] = 1 % mod;
    for (; e; e >>= 1, a = mat_mul(a, a, mod))
        if (e & 1) r = mat_mul(r, a, mod);
    return r;
}

//    例：斐波那契数列 F(0) = 0, F(1) = 1。[F(n+1), F(n)]^T = [[1, 1], [1, 0]]^n * [1, 0]^T
ll fib(ll n, ll mod) {
    Mat m = mat_pow({{1, 1}, {1, 0}}, n, mod);
    return m[1][0];
}

// 3. 广义矩阵乘法 (min, +)：c[i][j] = min_k (a[i][k] + b[k][j])，同样满足结合律。
//    邻接矩阵的 k 次 (min, +) 幂 = 恰好走 k 条边的最短路。inf 表示没有边
Mat minplus_mul(const Mat &a, const Mat &b, ll inf) {
    int n = a.size(), K = b.size(), m = b[0].size();
    Mat c(n, vector<ll>(m, inf));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < K; k++) {
            if (a[i][k] >= inf) continue;
            for (int j = 0; j < m; j++)
                if (b[k][j] < inf) c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
        }
    return c;
}
