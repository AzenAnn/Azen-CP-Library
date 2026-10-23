/**
 * 05_math/10 高斯消元
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：05_math/08 矩阵与矩阵快速幂
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 实数方程组
 *   2. 模意义下的方程组
 *   3. 异或方程组（bitset）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/numerical/gauss/
 *   cp-algorithms  https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/math_matrix.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3389  P3389 【模板】高斯消元法
 *   https://www.luogu.com.cn/problem/P2455  P2455 [SDOI2006] 线性方程组
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1092  提高  P1092 [NOIP 2004 提高组] 虫食算  考点：数学、深度优先搜索 DFS、剪枝
 *   https://www.luogu.com.cn/problem/P2447  提高  P2447 [SDOI2010] 外星千足虫  考点：高斯消元、线性基、位运算
 *   https://www.luogu.com.cn/problem/P2962  提高  P2962 [USACO09NOV] Lights G  考点：搜索、深度优先搜索 DFS、高斯消元
 *   https://www.luogu.com.cn/problem/P4035  提高  P4035 [JSOI2008] 球形空间产生器  考点：模拟退火、高斯消元、构造
 *   https://www.luogu.com.cn/problem/P4783  提高  P4783 【模板】矩阵求逆  考点：数学、线性代数、高斯消元
 *   https://www.luogu.com.cn/problem/P5027  提高  P5027 Barracuda  考点：枚举、高斯消元
 *   https://www.luogu.com.cn/problem/P7112  提高  P7112 【模板】行列式求值  考点：数学、线性代数、高斯消元
 *   https://codeforces.com/problemset/problem/21/B  CF2000  CF21B Intersection  考点：实现、数学
 *   https://www.luogu.com.cn/problem/P2109  提高+/省选−  P2109 [NOI2007] 生成树计数  考点：动态规划 DP、矩阵树定理、矩阵加速
 *   https://codeforces.com/problemset/problem/24/D  CF2400  CF24D Broken robot  考点：DP、数学、概率期望
 *   https://www.luogu.com.cn/problem/P3232  省选/NOI−  P3232 [HNOI2013 / JSOI2013] 游走  考点：贪心、期望、高斯消元
 *   https://www.luogu.com.cn/problem/P3265  省选/NOI−  P3265 [JLOI2015] 装备购买  考点：高斯消元、线性基、向量
 *   https://www.luogu.com.cn/problem/P4111  省选/NOI−  P4111 [HEOI2015] 小 Z 的房间  考点：矩阵树定理、生成树、素数判断
 *   https://www.luogu.com.cn/problem/P6030  省选/NOI−  P6030 [SDOI2012] 走迷宫  考点：拓扑排序、Tarjan、期望
 *   https://www.luogu.com.cn/problem/P6178  省选/NOI−  P6178 【模板】Matrix-Tree 定理  考点：图论、矩阵树定理、生成树
 *
 */

// 高斯消元解线性方程组。a 为 n 行 m+1 列的增广矩阵（最后一列为常数项），未知数 m 个。
// 逐列选主元，把这一列其他行都消成 0（高斯-约旦消元），O(n · m^2)。
// 返回值：0 无解；1 唯一解；2 无穷多解（此时 x 为自由变量取 0 的一组解）

// 1. 实数方程组：选绝对值最大的元素作主元，减小误差
int gauss_real(vector<vector<double>> a, vector<double> &x, double eps = 1e-9) {
    int n = a.size(), m = a[0].size() - 1;
    vector<int> where(m, -1);   // where[col]：第 col 个未知数由哪一行确定
    for (int col = 0, row = 0; col < m && row < n; col++) {
        int sel = row;
        for (int i = row; i < n; i++)
            if (fabs(a[i][col]) > fabs(a[sel][col])) sel = i;
        if (fabs(a[sel][col]) < eps) continue;   // 这一列全是 0：自由变量
        swap(a[sel], a[row]);
        where[col] = row;
        for (int i = 0; i < n; i++) {
            if (i == row) continue;
            double c = a[i][col] / a[row][col];
            for (int j = col; j <= m; j++) a[i][j] -= a[row][j] * c;
        }
        row++;
    }
    x.assign(m, 0);
    for (int col = 0; col < m; col++)
        if (where[col] != -1) x[col] = a[where[col]][m] / a[where[col]][col];
    for (int i = 0; i < n; i++) {   // 代回检查：出现 0 = 非零 说明无解
        double s = 0;
        for (int j = 0; j < m; j++) s += a[i][j] * x[j];
        if (fabs(s - a[i][m]) > eps) return 0;
    }
    for (int col = 0; col < m; col++)
        if (where[col] == -1) return 2;
    return 1;
}

// 2. 模质数 p 的方程组：除法换成乘逆元，其余相同
int gauss_mod(vector<vector<ll>> a, vector<ll> &x, ll p) {
    int n = a.size(), m = a[0].size() - 1;
    auto power = [&](ll b, ll e) {
        ll r = 1;
        for (b %= p; e; e >>= 1, b = b * b % p)
            if (e & 1) r = r * b % p;
        return r;
    };
    for (auto &row : a)
        for (auto &v : row) v = (v % p + p) % p;
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; col++) {
        int sel = -1;
        for (int i = row; i < n; i++)
            if (a[i][col]) { sel = i; break; }
        if (sel == -1) continue;
        swap(a[sel], a[row]);
        where[col] = row;
        ll inv = power(a[row][col], p - 2);
        for (int j = col; j <= m; j++) a[row][j] = a[row][j] * inv % p;   // 主元化为 1
        for (int i = 0; i < n; i++) {
            if (i == row || !a[i][col]) continue;
            ll c = a[i][col];
            for (int j = col; j <= m; j++) a[i][j] = ((a[i][j] - c * a[row][j]) % p + p) % p;
        }
        row++;
    }
    x.assign(m, 0);
    for (int col = 0; col < m; col++)
        if (where[col] != -1) x[col] = a[where[col]][m];
    for (int i = 0; i < n; i++) {
        ll s = 0;
        for (int j = 0; j < m; j++) s = (s + a[i][j] * x[j]) % p;
        if (s != a[i][m]) return 0;
    }
    for (int col = 0; col < m; col++)
        if (where[col] == -1) return 2;
    return 1;
}

// 3. 异或方程组（模 2）：每一行用 bitset 存，消元时整行异或，O(n · m^2 / 64)
//    a[i] 的第 0..m-1 位为系数，第 m 位为常数项；N 为 bitset 的长度（>= m + 1）
template <size_t N>
int gauss_xor(vector<bitset<N>> a, int m, vector<int> &x) {
    int n = a.size();
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; col++) {
        int sel = -1;
        for (int i = row; i < n; i++)
            if (a[i][col]) { sel = i; break; }
        if (sel == -1) continue;
        swap(a[sel], a[row]);
        where[col] = row;
        for (int i = 0; i < n; i++)
            if (i != row && a[i][col]) a[i] ^= a[row];
        row++;
    }
    x.assign(m, 0);
    for (int col = 0; col < m; col++)
        if (where[col] != -1) x[col] = a[where[col]][m];
    for (int i = 0; i < n; i++) {
        int s = 0;
        for (int j = 0; j < m; j++) s ^= a[i][j] & x[j];
        if (s != a[i][m]) return 0;
    }
    for (int col = 0; col < m; col++)
        if (where[col] == -1) return 2;
    return 1;
}
