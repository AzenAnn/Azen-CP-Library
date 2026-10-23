/**
 * 08_geometry/08 自适应 Simpson 积分
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：08_geometry/07 圆的基本计算
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Simpson 公式：∫_l^r f ≈ (r − l)/6 · (f(l) + 4f(m) + f(r))，对三次以下多项式精确
 *   2. 自适应：把区间对半分，若两半之和与整体相差 < 15·eps 就接受（并加上修正项），否则递归
 *   3. 用在几何上：f(x) = 竖直扫描线 x 与图形相交的总长度，积分得到面积（圆的面积并、月下柠檬树）
 *   4. 注意：函数有尖点、间断时容易误判，先按"事件点"（圆的左右端点）分段再分别积分；
 *      限定最少递归层数，防止一开始的几个采样点恰好都是 0
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/numerical/integral/
 *   cp-algorithms  https://cp-algorithms.com/num_methods/simpson-integration.html
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4525  P4525 【模板】自适应辛普森法 1
 *   https://www.luogu.com.cn/problem/P4526  P4526 【模板】自适应辛普森法 2
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P17050  普及+/提高−  P17050 [NWERC 2022] 翻瓶挑战 / Bottle Flip  考点：数值积分
 *   https://www.luogu.com.cn/problem/P1222  省选/NOI−  P1222 三角形  考点：三角形面积并：扫描线 + Simpson
 *   https://www.luogu.com.cn/problem/SP8073  省选/NOI−  SP8073 CIRU - The area of the union of circles  考点：圆的面积并：Simpson 积分
 *   https://www.luogu.com.cn/problem/P4207  NOI/NOI+/CTS  P4207 [NOI2005] 月下柠檬树  考点：圆台的投影：自适应 Simpson
 *
 */

// 1. 自适应 Simpson 积分：∫_l^r f(x) dx，eps 为允许误差，depth 为至少递归的层数
template <class F>
double simpson_integrate(F f, double l, double r, double eps = 1e-9, int depth = 6) {
    auto simpson = [&](double a, double b, double fa, double fm, double fb) { return (b - a) / 6 * (fa + 4 * fm + fb); };
    function<double(double, double, double, double, double, double, double, int)> rec =
        [&](double a, double b, double fa, double fm, double fb, double whole, double e, int dep) {
            double m = (a + b) / 2, lm = (a + m) / 2, rm = (m + b) / 2;
            double flm = f(lm), frm = f(rm);
            double L = simpson(a, m, fa, flm, fm), R = simpson(m, b, fm, frm, fb);
            if (dep <= 0 && fabs(L + R - whole) <= 15 * e) return L + R + (L + R - whole) / 15;
            return rec(a, m, fa, flm, fm, L, e / 2, dep - 1) + rec(m, b, fm, frm, fb, R, e / 2, dep - 1);
        };
    double fl = f(l), fr = f(r), fm = f((l + r) / 2);
    return rec(l, r, fl, fm, fr, simpson(l, r, fl, fm, fr), eps, depth);
}

// 2. 例：多个圆的面积并（需要先粘贴 08_geometry/01 与 08_geometry/07 的 Circle）。
//    先删掉被别的圆包含的圆，再按圆的 x 范围分成若干段，每段内对"竖线与圆并的长度"积分
double circle_union_area(vector<Circle> cs, double eps = 1e-9) {
    // 去掉被包含的圆（完全相同的圆只保留一个）
    vector<Circle> keep;
    for (size_t i = 0; i < cs.size(); i++) {
        bool inside = false;
        for (size_t j = 0; j < cs.size() && !inside; j++) {
            if (i == j) continue;
            double d = (cs[i].c - cs[j].c).len();
            if (d + cs[i].r <= cs[j].r + 1e-12 && (cs[i].r < cs[j].r || d > 1e-12 || j < i)) inside = true;
        }
        if (!inside && cs[i].r > 0) keep.push_back(cs[i]);
    }
    cs = keep;
    auto len = [&](double x) {   // 竖线 x 与圆并的交集长度
        vector<pair<double, double>> seg;
        for (auto &c : cs) {
            double t = c.r * c.r - (x - c.c.x) * (x - c.c.x);
            if (t > 0) seg.push_back({c.c.y - sqrt(t), c.c.y + sqrt(t)});
        }
        sort(seg.begin(), seg.end());
        double s = 0, lo = -1e300, hi = -1e300;
        for (auto [a, b] : seg) {
            if (a > hi) s += hi - lo, lo = a, hi = b;
            else hi = max(hi, b);
        }
        return s + hi - lo;
    };
    // 按所有圆的左右端点切段：段内被积函数光滑得多
    vector<double> xs;
    for (auto &c : cs) xs.push_back(c.c.x - c.r), xs.push_back(c.c.x + c.r);
    sort(xs.begin(), xs.end());
    double area = 0;
    for (size_t i = 0; i + 1 < xs.size(); i++)
        if (xs[i + 1] - xs[i] > 1e-12) area += simpson_integrate(len, xs[i], xs[i + 1], eps);
    return area;
}
