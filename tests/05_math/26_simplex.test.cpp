#include "../common.hpp"
#include "../../templates/05_math/26_simplex.hpp"

// 暴力：枚举 n 个"取等号"的约束（Ax ≤ b 中的行或 x_j ≥ 0），解出顶点，取可行顶点中目标最大的
int main() {
    for (int it = 0; it < 3000; it++) {
        int n = rnd(1, 3), m = rnd(0, 4);
        vector<vector<double>> A(m, vector<double>(n));
        vector<double> b(m), c(n);
        for (auto &r : A)
            for (auto &x : r) x = rnd(-5, 5);
        for (auto &x : b) x = rnd(-5, 10);
        for (auto &x : c) x = rnd(-5, 5);
        bool boxed = it % 2;   // 一半数据加上 x_j ≤ 20，保证有界
        if (boxed)
            for (int j = 0; j < n; j++) {
                vector<double> r(n, 0);
                r[j] = 1, A.push_back(r), b.push_back(20);
            }
        int M = A.size();
        // 全部约束写成 G x ≤ h（包括 −x_j ≤ 0）
        vector<vector<double>> Gm = A;
        vector<double> h = b;
        for (int j = 0; j < n; j++) {
            vector<double> r(n, 0);
            r[j] = -1, Gm.push_back(r), h.push_back(0);
        }
        int K = Gm.size();
        bool feasible = false;
        double best = -1e18;
        vector<int> pick;
        function<void(int)> go = [&](int st) {
            if ((int)pick.size() == n) {
                vector<vector<double>> a(n, vector<double>(n + 1));
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) a[i][j] = Gm[pick[i]][j];
                    a[i][n] = h[pick[i]];
                }
                for (int col = 0; col < n; col++) {   // 高斯消元
                    int p = col;
                    for (int r = col; r < n; r++)
                        if (fabs(a[r][col]) > fabs(a[p][col])) p = r;
                    if (fabs(a[p][col]) < 1e-9) return;
                    swap(a[p], a[col]);
                    for (int r = 0; r < n; r++)
                        if (r != col) {
                            double f = a[r][col] / a[col][col];
                            for (int k = col; k <= n; k++) a[r][k] -= f * a[col][k];
                        }
                }
                vector<double> x(n);
                for (int i = 0; i < n; i++) x[i] = a[i][n] / a[i][i];
                for (int i = 0; i < K; i++) {
                    double s = 0;
                    for (int j = 0; j < n; j++) s += Gm[i][j] * x[j];
                    if (s > h[i] + 1e-7) return;
                }
                double v = 0;
                for (int j = 0; j < n; j++) v += c[j] * x[j];
                feasible = true, best = max(best, v);
                return;
            }
            for (int i = st; i < K; i++) pick.push_back(i), go(i + 1), pick.pop_back();
        };
        go(0);
        LPSolver lp(A, b, c);
        vector<double> x;
        auto [st, val] = lp.solve(x);
        if (boxed) {   // 有界：可行 ⇔ 有顶点；最优值等于顶点最大值
            CHECK(st == (feasible ? 0 : -1));
            if (st == 0) CHECK(fabs(val - best) < 1e-6);
        } else if (st == 0) {
            CHECK(feasible && fabs(val - best) < 1e-6);
        } else if (st == -1) {
            CHECK(!feasible);
        }
        if (st == 0) {   // 给出的解满足约束且取到最优值
            double v = 0;
            for (int j = 0; j < n; j++) {
                CHECK(x[j] >= -1e-7);
                v += c[j] * x[j];
            }
            for (int i = 0; i < M; i++) {
                double s = 0;
                for (int j = 0; j < n; j++) s += A[i][j] * x[j];
                CHECK(s <= b[i] + 1e-7);
            }
            CHECK(fabs(v - val) < 1e-6);
        }
    }
    // 无界的例子：max x，约束 −x ≤ 1
    {
        LPSolver lp({{-1}}, {1}, {1});
        vector<double> x;
        CHECK(lp.solve(x).first == 1);
    }
    // 无可行解：x ≤ −1
    {
        LPSolver lp({{1}}, {-1}, {1});
        vector<double> x;
        CHECK(lp.solve(x).first == -1);
    }
    return 0;
}
