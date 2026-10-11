/**
 * 08_geometry/02 凸包
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：08_geometry/01 点、向量与基本运算
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Andrew 单调链
 *   2. 凸包周长与面积
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/geometry/convex-hull/
 *   cp-algorithms  https://cp-algorithms.com/geometry/convex-hull.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/geometry.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2742  P2742 【模板】二维凸包 / [USACO5.1] 圈奶牛Fencing the Cows
 *   https://judge.yosupo.jp/problem/static_convex_hull  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2116  提高  P2116 [NEERC 2001] 城墙  考点：计算几何、凸包
 *   https://www.luogu.com.cn/problem/P2924  提高  P2924 [USACO08DEC] Largest Fence G  考点：计算几何、凸包、极角排序
 *   https://www.luogu.com.cn/problem/P3194  提高  P3194 [HNOI2008] 水平可见直线  考点：计算几何、栈、凸包
 *   https://www.luogu.com.cn/problem/P7401  提高  P7401 [COCI 2020/2021 #5] Planine  考点：贪心、斜率优化、凸包
 *   https://www.luogu.com.cn/problem/P9568  提高  P9568 [SDCPC 2023] Computational Geometry  考点：计算几何、凸包
 *   https://www.luogu.com.cn/problem/P3829  提高+/省选−  P3829 [SHOI2012] 信用卡凸包  考点：凸包
 *   https://www.luogu.com.cn/problem/P4072  提高+/省选−  P4072 [SDOI2016] 征途  考点：单调队列、斜率优化、凸完全单调性（wqs 二分）
 *   https://www.luogu.com.cn/problem/P5155  提高+/省选−  P5155 [USACO18DEC] Balance Beam P  考点：数学、期望、凸包
 *   https://www.luogu.com.cn/problem/P6247  提高+/省选−  P6247 [SDOI2012] 最近最远点对  考点：分治、凸包、K-D Tree
 *   https://codeforces.com/problemset/problem/340/B  CF2100  CF340B Maximal Area Quadrilateral  考点：暴力、计算几何
 *   https://codeforces.com/problemset/problem/1142/C  CF2400  CF1142C U2  考点：计算几何
 *   https://www.luogu.com.cn/problem/P4557  省选/NOI−  P4557 [JSOI2018] 战争  考点：向量、凸包、闵可夫斯基和 Minkowski sum
 *   https://codeforces.com/problemset/problem/87/E  CF2600  CF87E Mogohu-Rea Idol  考点：计算几何
 *   https://codeforces.com/problemset/problem/1841/F  CF2700  CF1841F Monocarp and a Strategic Game  考点：计算几何、排序、双指针
 *   https://codeforces.com/problemset/problem/70/D  CF2700  CF70D Professor's task  考点：数据结构、计算几何
 *
 */

// 凸包（需要先粘贴 08_geometry/01 的点结构）
// Andrew 单调链：把点按 (x, y) 排序，从左到右求下凸壳，再从右到左求上凸壳。
// 维护时如果新点让栈顶两个点"向右拐"（叉积 <= 0），就弹出栈顶。O(n log n)
// 返回逆时针顺序的凸包顶点，不含共线的点（想保留共线点，把 <= 0 改成 < 0）
vector<Pt> convex_hull(vector<Pt> pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    int n = pts.size();
    if (n <= 2) return pts;
    vector<Pt> h(2 * n);
    int k = 0;
    for (int i = 0; i < n; i++) {   // 下凸壳
        while (k >= 2 && orient(h[k - 2], h[k - 1], pts[i]) <= 0) k--;
        h[k++] = pts[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {   // 上凸壳
        while (k >= t && orient(h[k - 2], h[k - 1], pts[i]) <= 0) k--;
        h[k++] = pts[i];
    }
    h.resize(k - 1);   // 最后一个点和第一个点重复
    return h;
}

// 凸包周长（只有两个点时为线段长度的两倍）
double hull_perimeter(const vector<Pt> &h) {
    double s = 0;
    for (size_t i = 0; i < h.size(); i++) s += (h[(i + 1) % h.size()] - h[i]).len();
    return s;
}
// 凸包面积的两倍：area2(h)（见 08_geometry/01）
