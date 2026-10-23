/**
 * 08_geometry/10 最小圆覆盖
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：08_geometry/01 点、向量与基本运算
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 定理：最小覆盖圆由 2 个点（直径）或 3 个点（外接圆）确定
 *   2. 随机增量法：随机打乱后，若新点不在当前圆内，则以该点为边界递归求解
 *   3. 期望 O(n)：三层循环 + 随机打乱保证期望线性
 *   4. 精度处理：eps 判断点是否在圆内
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/geometry/smallest-enclosing-circle/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1742  P1742 最小圆覆盖
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/1059/D  CF2200  CF1059D Nature Reserve  考点：二分半径，或三分圆心横坐标
 *   https://www.luogu.com.cn/problem/P2533  省选/NOI−  P2533 [AHOI2012] 信号塔  考点：最小圆覆盖模板
 *   https://www.luogu.com.cn/problem/P4586  NOI/NOI+/CTS  P4586 [FJOI2015] 最小覆盖双圆问题  考点：二分 + 最小圆覆盖
 *
 */

// 最小圆覆盖（随机增量法，期望 O(n)）。需要先粘贴 08_geometry/01（Pd）。
// 定理：最小覆盖圆由 2 个点（作直径）或 3 个点（外接圆）确定；若第 i 个点不在前 i−1 个点的最小圆内，它一定在新圆的边界上。
// 三重循环 + 随机打乱，期望线性。返回 {圆心, 半径}。
pair<Pd, double> min_enclosing_circle(vector<Pd> pts) {
    if (pts.empty()) return {Pd(0, 0), 0};
    shuffle(pts.begin(), pts.end(), mt19937(20261023));
    auto circum = [](const Pd &a, const Pd &b, const Pd &c) {   // 外接圆圆心
        Pd B = b - a, C = c - a;
        double D = 2 * B.cross(C);
        return a + Pd((C.y * B.norm2() - B.y * C.norm2()) / D, (B.x * C.norm2() - C.x * B.norm2()) / D);
    };
    const double eps = 1e-9;
    Pd o = pts[0];
    double r2 = 0;
    auto out = [&](const Pd &q) { return (q - o).norm2() > r2 * (1 + eps) + eps; };
    for (size_t i = 1; i < pts.size(); i++) {
        if (!out(pts[i])) continue;
        o = pts[i], r2 = 0;
        for (size_t j = 0; j < i; j++) {
            if (!out(pts[j])) continue;
            o = (pts[i] + pts[j]) / 2, r2 = (pts[i] - o).norm2();
            for (size_t k = 0; k < j; k++) {
                if (!out(pts[k])) continue;
                o = circum(pts[i], pts[j], pts[k]), r2 = (pts[i] - o).norm2();
            }
        }
    }
    return {o, sqrt(r2)};
}
