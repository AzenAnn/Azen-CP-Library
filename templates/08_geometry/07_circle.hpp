/**
 * 08_geometry/07 圆的基本计算
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：08_geometry/01 点、向量与基本运算
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 圆与直线的交点：把圆心投影到直线上，再沿直线方向走 √(r² − h²)
 *   2. 两圆的交点：先判断相离 / 内含（d > r1 + r2 或 d < |r1 − r2|），再用余弦定理求交点到圆心连线的夹角
 *   3. 过一点的切线：切点满足 (t − c)·(t − p) = 0，点在圆内没有切线、在圆上只有一条
 *   4. 两圆相交部分的面积：两个弓形面积之和；三角形外接圆
 *   5. 圆与多边形相交的面积：按边拆成"圆心 + 一条边"的三角形，求每个三角形与圆的有向交面积再求和
 *   6. 多个圆的面积并：自适应 Simpson 积分（见 08_geometry/08）或格林公式
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/geometry/2d/
 *   cp-algorithms  https://cp-algorithms.com/geometry/circle-line-intersection.html
 *   cp-algorithms  https://cp-algorithms.com/geometry/circle-circle-intersection.html
 *   cp-algorithms  https://cp-algorithms.com/geometry/tangents-to-two-circles.html
 *
 * 【模板题 / 入门题】
 *   https://codeforces.com/problemset/problem/600/D  CF600D Area of Two Circles' Intersection
 *   https://www.luogu.com.cn/problem/P1652  P1652 圆
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/1/C  CF2100  CF1C Ancient Berland Circus  考点：外接圆 + 求正多边形边数
 *   https://www.luogu.com.cn/problem/P10624  省选/NOI−  P10624 [ICPC 2013 WF] Pollution Solution  考点：圆与多边形的交面积
 *   https://www.luogu.com.cn/problem/P2510  省选/NOI−  P2510 [HAOI2008] 下落的圆盘  考点：圆弧被覆盖的部分
 *   https://www.luogu.com.cn/problem/P3268  省选/NOI−  P3268 [JLOI2016] 圆的异或并  考点：扫描线 + 圆的上下半圆
 *   https://codeforces.com/problemset/problem/2/C  CF2600  CF2C Commentator problem  考点：视角相等的点：阿波罗尼斯圆的交点
 *   https://www.luogu.com.cn/problem/P4586  NOI/NOI+/CTS  P4586 [FJOI2015] 最小覆盖双圆问题  考点：二分 + 最小圆覆盖
 *
 */

// 需要先粘贴 08_geometry/01（P、Pd、EPS、sgn）。精度要求高时可以把 double 换成 long double。
struct Circle {
    Pd c;
    double r;
};

// 1. 圆与直线 ab 的交点（0、1 或 2 个，按从 a 指向 b 的方向排序）
vector<Pd> circle_line_inter(const Circle &C, const Pd &a, const Pd &b) {
    Pd d = b - a;
    double t = (C.c - a).dot(d) / d.norm2();
    Pd h = a + d * t;   // 圆心在直线上的投影
    double h2 = C.r * C.r - (C.c - h).norm2();
    if (h2 < -EPS) return {};
    if (h2 < EPS) return {h};
    Pd off = d * (sqrt(h2) / d.len());
    return {h - off, h + off};
}

// 2. 两圆的交点（0、1 或 2 个；两圆重合时返回空）
vector<Pd> circle_circle_inter(const Circle &A, const Circle &B) {
    Pd d = B.c - A.c;
    double dist2 = d.norm2(), dist = sqrt(dist2);
    if (dist < EPS) return {};
    if (dist > A.r + B.r + EPS || dist < fabs(A.r - B.r) - EPS) return {};
    double x = (dist2 + A.r * A.r - B.r * B.r) / (2 * dist);   // 交点弦中点到 A 圆心的距离
    double y2 = max(0.0, A.r * A.r - x * x);
    Pd m = A.c + d * (x / dist);
    if (y2 < EPS) return {m};
    Pd per = Pd(-d.y, d.x) * (sqrt(y2) / dist);
    return {m + per, m - per};
}

// 3. 两圆相交部分的面积
double circle_circle_area(const Circle &A, const Circle &B) {
    double d = (A.c - B.c).len();
    if (d >= A.r + B.r) return 0;
    double r = min(A.r, B.r), R = max(A.r, B.r);
    if (d <= R - r) return acos(-1.0) * r * r;
    auto seg = [&](double r1, double r2) {   // 圆 r1 被弦切下的弓形面积
        double a = acos(max(-1.0, min(1.0, (r1 * r1 + d * d - r2 * r2) / (2 * r1 * d))));
        return r1 * r1 * (a - sin(2 * a) / 2);
    };
    return seg(A.r, B.r) + seg(B.r, A.r);
}

// 4. 过点 p 作圆的切线，返回切点（点在圆内为空，在圆上返回 p 自己）
vector<Pd> tangent_points(const Circle &C, const Pd &p) {
    Pd d = p - C.c;
    double d2 = d.norm2(), r2 = C.r * C.r;
    if (d2 < r2 - EPS) return {};
    if (d2 < r2 + EPS) return {p};
    // 切点 = c + r·(cosθ·u ± sinθ·u⊥)，其中 u = d/|d|，cosθ = r/|d|
    Pd u = d / sqrt(d2), up(-u.y, u.x);
    double cs = C.r / sqrt(d2), sn = sqrt(max(0.0, 1 - cs * cs));
    return {C.c + (u * cs + up * sn) * C.r, C.c + (u * cs - up * sn) * C.r};
}

// 5. 三角形外接圆（三点不共线）
Circle circumcircle(const Pd &a, const Pd &b, const Pd &c) {
    Pd B = b - a, Cc = c - a;
    double D = 2 * B.cross(Cc);
    Pd o((Cc.y * B.norm2() - B.y * Cc.norm2()) / D, (B.x * Cc.norm2() - Cc.x * B.norm2()) / D);
    return {a + o, o.len()};
}

// 6. 圆与简单多边形相交部分的面积（多边形逆时针时为正）。O(n)
double circle_polygon_area(const Circle &C, const vector<Pd> &poly) {
    double r = C.r;
    auto arg = [](const Pd &p, const Pd &q) { return atan2(p.cross(q), p.dot(q)); };
    // 圆心在原点时，圆与三角形 (0, p, q) 的有向交面积
    auto tri = [&](Pd p, Pd q) {
        Pd d = q - p;
        if (d.norm2() < EPS * EPS) return 0.0;
        double r2 = r * r / 2;
        double a = d.dot(p) / d.norm2(), b = (p.norm2() - r * r) / d.norm2();
        double det = a * a - b;
        if (det <= 0) return arg(p, q) * r2;   // 线段所在直线与圆不交：整个是扇形
        double s = max(0.0, -a - sqrt(det)), t = min(1.0, -a + sqrt(det));
        if (t < 0 || 1 <= s) return arg(p, q) * r2;
        Pd u = p + d * s, v = p + d * t;   // 线段在圆内的部分 [u, v]
        return arg(p, u) * r2 + u.cross(v) / 2 + arg(v, q) * r2;
    };
    double sum = 0;
    for (size_t i = 0; i < poly.size(); i++) sum += tri(poly[i] - C.c, poly[(i + 1) % poly.size()] - C.c);
    return sum;
}
