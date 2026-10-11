/**
 * 08_geometry/01 点、向量与基本运算
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 点 / 向量结构体
 *   2. 点积与叉积
 *   3. eps 比较与整数坐标优先
 *   4. 直线、线段相交
 *   5. 多边形面积
 *   6. 点在多边形内
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/geometry/2d/
 *   cp-algorithms  https://cp-algorithms.com/geometry/basic-geometry.html
 *   cp-algorithms  https://cp-algorithms.com/geometry/check-segments-intersection.html
 *   cp-algorithms  https://cp-algorithms.com/geometry/area-of-simple-polygon.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/geometry.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1183  P1183 多边形的面积
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10859  普及  P10859 [HBCPC2024] Nana Likes Polygons  考点：数学、叉积
 *   https://www.luogu.com.cn/problem/P1355  普及  P1355 神秘大三角  考点：数学、计算几何、向量
 *   https://www.luogu.com.cn/problem/P4894  普及  P4894 GodFly 求解法向量  考点：数学、计算几何、向量
 *   https://www.luogu.com.cn/problem/P6160  普及  P6160 [Cnoi2020] 向量  考点：向量
 *   https://codeforces.com/problemset/problem/1648/A  CF1400  CF1648A Weird Sum  考点：组合数学、数据结构、计算几何
 *   https://codeforces.com/problemset/problem/507/B  CF1400  CF507B Amr and Pins  考点：计算几何、数学
 *   https://codeforces.com/problemset/problem/514/B  CF1400  CF514B Han Solo and Lazer Gun  考点：暴力、数据结构、计算几何
 *   https://codeforces.com/problemset/problem/1486/B  CF1500  CF1486B Eastern Exhibition  考点：二分、计算几何、最短路
 *   https://codeforces.com/problemset/problem/498/A  CF1700  CF498A Crazy Town  考点：计算几何
 *   https://www.luogu.com.cn/problem/P2520  提高  P2520 [HAOI2011] 向量  考点：数学、最大公约数 gcd、向量
 *   https://www.luogu.com.cn/problem/P2992  提高  P2992 [USACO10OPEN] Triangle Counting G  考点：计算几何、排序、容斥原理
 *   https://www.luogu.com.cn/problem/P3744  提高  P3744 李彬的几何  考点：数学、贪心、计算几何
 *   https://www.luogu.com.cn/problem/P8854  提高+/省选−  P8854 [POI 2002 R1] 超级马  考点：计算几何、广度优先搜索 BFS、线性代数
 *   https://codeforces.com/problemset/problem/1/C  CF2100  CF1C Ancient Berland Circus  考点：计算几何、数学
 *   https://codeforces.com/problemset/problem/319/C  CF2100  CF319C Kalila and Dimna in the Logging Industry  考点：DP、计算几何
 *
 */

// 计算几何基础。坐标为整数时尽量用 ll（P<ll>），全程精确、没有误差；
// 只有求交点、距离、角度时才用 double（P<double>），比较时配合 EPS。
// 08_geometry 后面的模板都要用到这里的点结构，使用时先粘贴本文件。
template <class T>
struct P {
    T x, y;
    P(T x = 0, T y = 0) : x(x), y(y) {}
    P operator+(const P &o) const { return {x + o.x, y + o.y}; }
    P operator-(const P &o) const { return {x - o.x, y - o.y}; }
    P operator*(T k) const { return {x * k, y * k}; }
    P operator/(T k) const { return {x / k, y / k}; }
    T dot(const P &o) const { return x * o.x + y * o.y; }     // 点积：|a||b|cosθ
    T cross(const P &o) const { return x * o.y - y * o.x; }   // 叉积：|a||b|sinθ，> 0 表示 o 在 this 的逆时针方向
    T norm2() const { return x * x + y * y; }
    double len() const { return sqrt((double)norm2()); }
    bool operator<(const P &o) const { return tie(x, y) < tie(o.x, o.y); }
    bool operator==(const P &o) const { return x == o.x && y == o.y; }
};
using Pt = P<ll>;
using Pd = P<double>;
const double EPS = 1e-9;
int sgn(ll x) { return (x > 0) - (x < 0); }
int sgn(double x) { return (x > EPS) - (x < -EPS); }

// 1. 方向判断：orient(a, b, c) = (b - a) × (c - a)。> 0：c 在有向直线 ab 的左侧（a→b→c 逆时针）；= 0：三点共线
template <class T>
T orient(const P<T> &a, const P<T> &b, const P<T> &c) { return (b - a).cross(c - a); }

// 2. 点 p 是否在线段 ab 上（含端点）：共线，且 p 到 a、b 的方向相反（或重合）
template <class T>
bool on_segment(const P<T> &p, const P<T> &a, const P<T> &b) {
    return sgn(orient(a, b, p)) == 0 && sgn((a - p).dot(b - p)) <= 0;
}

// 3. 线段 ab 与 cd 是否相交（含端点接触、共线重叠）
//    一般情况：c、d 在 ab 两侧，且 a、b 在 cd 两侧；否则只可能是某个端点落在另一条线段上
template <class T>
bool segments_intersect(const P<T> &a, const P<T> &b, const P<T> &c, const P<T> &d) {
    int d1 = sgn(orient(a, b, c)), d2 = sgn(orient(a, b, d)), d3 = sgn(orient(c, d, a)), d4 = sgn(orient(c, d, b));
    if (d1 * d2 < 0 && d3 * d4 < 0) return true;
    return on_segment(c, a, b) || on_segment(d, a, b) || on_segment(a, c, d) || on_segment(b, c, d);
}

// 4. 直线 ab 与直线 cd 的交点（要求不平行）：a + (b - a)·t，t = ((c - a) × (d - c)) / ((b - a) × (d - c))
Pd line_intersection(const Pd &a, const Pd &b, const Pd &c, const Pd &d) {
    double t = (c - a).cross(d - c) / (b - a).cross(d - c);
    return a + (b - a) * t;
}

// 5. 点 p 到线段 ab 的距离：投影落在线段内取垂直距离，否则取到较近端点的距离
double dist_point_segment(const Pd &p, const Pd &a, const Pd &b) {
    if (a == b) return (p - a).len();
    if (sgn((p - a).dot(b - a)) < 0) return (p - a).len();
    if (sgn((p - b).dot(a - b)) < 0) return (p - b).len();
    return fabs((b - a).cross(p - a)) / (b - a).len();
}

// 6. 多边形面积的两倍（有向：顶点逆时针为正）。整数坐标时结果精确，真正的面积为它的一半
template <class T>
T area2(const vector<P<T>> &poly) {
    T s = 0;
    for (size_t i = 0; i < poly.size(); i++) s += poly[i].cross(poly[(i + 1) % poly.size()]);
    return s;
}

// 7. 点是否在简单多边形内：1 内部，0 在边上，-1 外部（射线法：向右的射线与边相交奇数次则在内部）
int point_in_polygon(const Pt &p, const vector<Pt> &poly) {
    int n = poly.size();
    bool in = false;
    for (int i = 0; i < n; i++) {
        Pt a = poly[i], b = poly[(i + 1) % n];
        if (on_segment(p, a, b)) return 0;
        if ((a.y > p.y) != (b.y > p.y)) {   // 这条边跨过水平线 y = p.y（下端点算、上端点不算）
            ll c = orient(a, b, p);
            if (b.y > a.y ? c > 0 : c < 0) in = !in;   // 交点在 p 的右侧
        }
    }
    return in ? 1 : -1;
}
