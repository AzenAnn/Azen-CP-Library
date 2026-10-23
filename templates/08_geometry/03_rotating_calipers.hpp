/**
 * 08_geometry/03 旋转卡壳
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：08_geometry/02 凸包
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 凸包直径（最远点对）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/geometry/rotating-calipers/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/geometry.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1452  P1452 [USACO03FALL] Beauty Contest G
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P11441  省选/NOI−  P11441 [Code+#6] 进阶法师  考点：计算几何、凸包、叉积
 *   https://www.luogu.com.cn/problem/P13303  省选/NOI−  P13303 [GCJ 2013 Finals] Drummer  考点：计算几何、凸包、旋转卡壳
 *   https://www.luogu.com.cn/problem/P13335  省选/NOI−  P13335 [GCJ 2012 Finals] Twirling Towards Freedom  考点：数学、计算几何、凸包
 *   https://www.luogu.com.cn/problem/P14498  省选/NOI−  P14498 [NCPC 2025] Dune Dash  考点：计算几何、排序、凸包
 *   https://www.luogu.com.cn/problem/P14802  省选/NOI−  P14802 [CCPC 2024 哈尔滨站] 凹包  考点：计算几何、凸包、旋转卡壳
 *   https://www.luogu.com.cn/problem/P16223  提高+/省选−  P16223 【模板】旋转卡壳/最远点对  考点：计算几何、凸包、旋转卡壳
 *   https://www.luogu.com.cn/problem/P3187  省选/NOI−  P3187 [HNOI2007] 最小矩形覆盖  考点：枚举、凸包、旋转卡壳
 *   https://www.luogu.com.cn/problem/P4166  省选/NOI−  P4166 [SCOI2007] 最大土地面积  考点：枚举、向量、凸包
 *   https://www.luogu.com.cn/problem/P4357  省选/NOI−  P4357 [CQOI2016] K 远点对  考点：旋转卡壳
 *   https://www.luogu.com.cn/problem/P8000  省选/NOI−  P8000 [WFOI - 01] 循环节（circle）  考点：计算几何、凸包、旋转卡壳
 *   https://www.luogu.com.cn/problem/P8222  省选/NOI−  P8222 [WFOI - 02] I wanna escape the shadow（阴影）  考点：凸包、旋转卡壳、其它技巧
 *
 */

// 旋转卡壳（需要先粘贴 08_geometry/01 和 02）
// 求点集中最远的两个点（凸包直径），返回距离的平方（洛谷 P1452）。
// 按逆时针枚举凸包的每条边 (i, i+1)，离这条边最远的点 j 也随之单调地逆时针移动，
// 用叉积（三角形面积）比较距离。总复杂度 O(n log n)（求凸包）+ O(n)
ll hull_diameter2(const vector<Pt> &pts) {
    vector<Pt> h = convex_hull(pts);
    int n = h.size();
    if (n == 1) return 0;
    if (n == 2) return (h[0] - h[1]).norm2();
    ll best = 0;
    for (int i = 0, j = 1; i < n; i++) {
        int ni = (i + 1) % n;
        while ((h[ni] - h[i]).cross(h[(j + 1) % n] - h[i]) > (h[ni] - h[i]).cross(h[j] - h[i])) j = (j + 1) % n;
        best = max({best, (h[i] - h[j]).norm2(), (h[ni] - h[j]).norm2()});
    }
    return best;
}
