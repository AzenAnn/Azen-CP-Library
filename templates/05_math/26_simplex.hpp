/**
 * 05_math/26 单纯形法（线性规划）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：05_math/10 高斯消元
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 线性规划标准型：max cᵀx, Ax ≤ b, x ≥ 0
 *   2. 单纯形：松弛变量化为等式，转轴操作（pivot）移动顶点
 *   3. 两阶段法处理初始不可行 / Bland 规则防退化环
 *   4. 对偶定理与费用流/网络流的关系
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/simplex/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P13337  P13337 【模板】线性规划
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10669  省选/NOI−  P10669 BZOJ3118 Orz the MST  考点：线性规划
 *   https://www.luogu.com.cn/problem/P3980  省选/NOI−  P3980 [NOI2008] 志愿者招募  考点：线性规划 / 费用流
 *   https://www.luogu.com.cn/problem/P4412  省选/NOI−  P4412 [SHOI2004] 最小生成树  考点：线性规划、网络流、最小割
 *   https://www.luogu.com.cn/problem/P6967  省选/NOI−  P6967 [NEERC 2016] Delight for a Cat  考点：线性规划对偶 → 费用流
 *   https://www.luogu.com.cn/problem/P8182  NOI/NOI+/CTS  P8182 「EZEC-11」雪的魔法  考点：线性规划、动态规划 DP、分治
 *
 */

// 单纯形法求线性规划：max cᵀx，约束 Ax ≤ b，x ≥ 0（写法参考 kactl）。
// 两阶段：b 有负数时先引入辅助变量求一个可行基（找不到 ⇒ 无可行解）；选进基 / 出基变量时按 (值, 下标) 比较，
// 相当于 Bland 规则，避免退化时死循环。
// 返回 {状态, 最优值}，状态：0 有最优解（x 中给出一组最优解），1 无界，-1 无可行解。
// 精度用 double，EPS 视数据范围调整。等式约束拆成 ≤ 和 ≥ 两条；≥ 约束两边乘 −1。
struct LPSolver {
    using T = double;
    static constexpr T EPS = 1e-9;
    int m, n;
    vector<int> N, B;
    vector<vector<T>> D;
    LPSolver(const vector<vector<T>> &A, const vector<T> &b, const vector<T> &c)
        : m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vector<T>(n + 2)) {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) D[i][j] = A[i][j];
        for (int i = 0; i < m; i++) B[i] = n + i, D[i][n] = -1, D[i][n + 1] = b[i];
        for (int j = 0; j < n; j++) N[j] = j, D[m][j] = -c[j];
        N[n] = -1, D[m + 1][n] = 1;
    }
    void pivot(int r, int s) {
        T inv = 1 / D[r][s];
        for (int i = 0; i < m + 2; i++)
            if (i != r && fabs(D[i][s]) > EPS) {
                T f = D[i][s] * inv;
                for (int j = 0; j < n + 2; j++) D[i][j] -= D[r][j] * f;
                D[i][s] = D[r][s] * f;
            }
        for (int j = 0; j < n + 2; j++)
            if (j != s) D[r][j] *= inv;
        for (int i = 0; i < m + 2; i++)
            if (i != r) D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }
    bool simplex(int phase) {
        int x = m + phase - 1;
        while (true) {
            int s = -1;
            for (int j = 0; j <= n; j++)
                if (N[j] != -phase && (s == -1 || make_pair(D[x][j], N[j]) < make_pair(D[x][s], N[s]))) s = j;
            if (D[x][s] >= -EPS) return true;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (D[i][s] <= EPS) continue;
                if (r == -1 || make_pair(D[i][n + 1] / D[i][s], B[i]) < make_pair(D[r][n + 1] / D[r][s], B[r])) r = i;
            }
            if (r == -1) return false;   // 无界
            pivot(r, s);
        }
    }
    pair<int, T> solve(vector<T> &x) {
        int r = 0;
        for (int i = 1; i < m; i++)
            if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (m > 0 && D[r][n + 1] < -EPS) {   // 第一阶段：找可行解
            pivot(r, n);
            if (!simplex(2) || D[m + 1][n + 1] < -EPS) return {-1, 0};
            for (int i = 0; i < m; i++)
                if (B[i] == -1) {
                    int s = 0;
                    for (int j = 1; j <= n; j++)
                        if (make_pair(D[i][j], N[j]) < make_pair(D[i][s], N[s])) s = j;
                    pivot(i, s);
                }
        }
        bool ok = simplex(1);
        x.assign(n, 0);
        for (int i = 0; i < m; i++)
            if (B[i] < n) x[B[i]] = D[i][n + 1];
        return ok ? make_pair(0, D[m][n + 1]) : make_pair(1, (T)0);
    }
};
