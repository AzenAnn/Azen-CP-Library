/**
 * 08_geometry/09 三维几何
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：08_geometry/01 点、向量与基本运算
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 三维向量：点积、叉积（法向量）、混合积（有向体积）
 *   2. 平面方程：ax + by + cz + d = 0；点到平面距离
 *   3. 直线与平面交点、两平面交线
 *   4. 三维凸包（增量法 / QuickHull）、旋转卡壳求直径
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/geometry/3d/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4724  P4724 【模板】三维凸包
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2287  省选/NOI−  P2287 [HNOI2004] 最佳包裹  考点：三维计算几何、计算几何、凸包
 *   https://www.luogu.com.cn/problem/P4080  NOI/NOI+/CTS  P4080 [SDOI2016] 平凡的骰子  考点：三维计算几何、计算几何、向量
 *   https://www.luogu.com.cn/problem/P4502  NOI/NOI+/CTS  P4502 [ZJOI2018] 保镖  考点：三维计算几何、计算几何
 *   https://www.luogu.com.cn/problem/P9141  NOI/NOI+/CTS  P9141 [THUPC 2023 初赛] 乱西星上的空战  考点：三维计算几何、模拟、计算几何
 *
 */

// 三维计算几何：向量运算、平面、三维凸包（增量法 O(n²)）。坐标用 double。
// 三维凸包：先给每个点加一个极小的随机扰动，避免四点共面；再逐个加点：
// 删去新点能"看到"的面（新点在面的外侧），在可见区域的边界边上与新点连出新面。结果的面都是逆时针朝外的三角形。
struct P3 {
    double x, y, z;
    P3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    P3 operator+(const P3 &o) const { return {x + o.x, y + o.y, z + o.z}; }
    P3 operator-(const P3 &o) const { return {x - o.x, y - o.y, z - o.z}; }
    P3 operator*(double k) const { return {x * k, y * k, z * k}; }
    double dot(const P3 &o) const { return x * o.x + y * o.y + z * o.z; }
    P3 cross(const P3 &o) const { return {y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x}; }
    double len() const { return sqrt(dot(*this)); }
};
// 混合积 (b−a)·((c−a)×(d−a))：四面体 abcd 有向体积的 6 倍，> 0 表示 d 在平面 abc（逆时针看）的上方
double mixed(const P3 &a, const P3 &b, const P3 &c, const P3 &d) { return (b - a).dot((c - a).cross(d - a)); }
// 点 p 到平面 abc 的有向距离（法向量为 (b−a)×(c−a)）
double dist_point_plane(const P3 &p, const P3 &a, const P3 &b, const P3 &c) {
    P3 nrm = (b - a).cross(c - a);
    return nrm.dot(p - a) / nrm.len();
}
// 直线 pq 与平面 abc 的交点（要求不平行）
P3 line_plane_intersection(const P3 &p, const P3 &q, const P3 &a, const P3 &b, const P3 &c) {
    P3 nrm = (b - a).cross(c - a);
    double t = nrm.dot(a - p) / nrm.dot(q - p);
    return p + (q - p) * t;
}
struct Hull3D {
    vector<P3> p;                  // 扰动后的点
    vector<array<int, 3>> faces;   // 每个面的三个顶点编号（朝外逆时针）
    Hull3D(vector<P3> pts, double jitter = 1e-9) : p(pts) {
        int n = p.size();
        if (n < 4) return;
        mt19937 rng(20261023);
        uniform_real_distribution<double> U(-jitter, jitter);
        for (auto &q : p) q = q + P3(U(rng), U(rng), U(rng));
        faces = {{0, 1, 2}, {2, 1, 0}};
        vector<vector<char>> vis(n, vector<char>(n, 0));
        for (int i = 3; i < n; i++) {
            vector<array<int, 3>> keep;
            vector<char> see(faces.size());
            for (size_t f = 0; f < faces.size(); f++) {
                auto [a, b, c] = faces[f];
                see[f] = mixed(p[a], p[b], p[c], p[i]) > 0;
                if (!see[f]) keep.push_back(faces[f]);
                vis[a][b] = vis[b][c] = vis[c][a] = see[f];
            }
            for (size_t f = 0; f < faces.size(); f++) {
                if (!see[f]) continue;
                auto [a, b, c] = faces[f];
                int e[3][2] = {{a, b}, {b, c}, {c, a}};
                for (auto &ed : e)
                    if (!vis[ed[1]][ed[0]]) keep.push_back({ed[0], ed[1], i});   // 边界边：另一侧的面看不到 i
            }
            faces = keep;
        }
    }
    double area() const {
        double s = 0;
        for (auto [a, b, c] : faces) s += (p[b] - p[a]).cross(p[c] - p[a]).len() / 2;
        return s;
    }
    double volume() const {   // 以原点为顶点的四面体有向体积之和
        double s = 0;
        for (auto [a, b, c] : faces) s += p[a].dot(p[b].cross(p[c])) / 6;
        return s;
    }
};
