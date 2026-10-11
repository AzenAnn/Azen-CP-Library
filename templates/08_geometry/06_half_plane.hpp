/**
 * 08_geometry/06 半平面交
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：08_geometry/01 点、向量与基本运算
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 按极角排序 + 双端队列
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/geometry/half-plane/
 *   cp-algorithms  https://cp-algorithms.com/geometry/halfplane-intersection.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/geometry.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4196  P4196 【模板】半平面交 / [CQOI2006] 凸多边形
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P11264  省选/NOI−  P11264 [COTS 2018] 逃遁 Bijeg  考点：二分、半平面交
 *   https://www.luogu.com.cn/problem/P2600  省选/NOI−  P2600 [ZJOI2008] 瞭望塔  考点：计算几何、半平面交
 *   https://www.luogu.com.cn/problem/P3222  省选/NOI−  P3222 [HNOI2012] 射箭  考点：二分、凸包、半平面交
 *   https://www.luogu.com.cn/problem/P3256  省选/NOI−  P3256 [JLOI2013] 赛车  考点：枚举、栈、半平面交
 *   https://www.luogu.com.cn/problem/P3493  省选/NOI−  P3493 [POI 2009] WSP-Island  考点：计算几何、半平面交
 *   https://www.luogu.com.cn/problem/P5928  省选/NOI−  P5928 [清华集训 2014] 文学  考点：动态规划 DP、模拟退火、凸包
 *   https://www.luogu.com.cn/problem/P7397  省选/NOI−  P7397 雨水收集系统（2021 CoE-I E）  考点：计算几何、凸包、半平面交
 *   https://www.luogu.com.cn/problem/P3297  NOI/NOI+/CTS  P3297 [SDOI2013] 逃考  考点：计算几何、半平面交
 *   https://www.luogu.com.cn/problem/P4250  NOI/NOI+/CTS  P4250 [SCOI2015] 小凸想跑步  考点：计算几何、半平面交
 *   https://www.luogu.com.cn/problem/P4642  NOI/NOI+/CTS  P4642 [BJWC2008] 方程  考点：线性规划、半平面交
 *   https://www.luogu.com.cn/problem/P9675  NOI/NOI+/CTS  P9675 [ICPC 2022 Jinan R] Shortest Path  考点：半平面交、李超线段树
 *
 */

// 半平面交（需要先粘贴 08_geometry/01 的点结构）。每个半平面用有向直线表示（经过点 p、方向 v），取直线左侧。
// 按极角排序后用双端队列维护：加入新直线时，弹出队尾、队头中交点在新直线右侧的直线。O(n log n)
// 要求结果有界：请加上四条很远的边界框直线。返回交出的凸多边形顶点（逆时针）；
// 交为空、或者退化成一个点 / 一条线段（面积为 0）时返回空。
struct HalfPlane {
    Pd p, v;
    double ang;
    HalfPlane(Pd p, Pd v) : p(p), v(v), ang(atan2(v.y, v.x)) {}
    bool out(const Pd &q) const { return v.cross(q - p) < -EPS; }   // q 严格在右侧（在半平面外）
};
Pd hp_intersection(const HalfPlane &a, const HalfPlane &b) {
    double t = (b.p - a.p).cross(b.v) / a.v.cross(b.v);
    return a.p + a.v * t;
}
vector<Pd> half_plane_intersection(vector<HalfPlane> hs) {
    sort(hs.begin(), hs.end(), [](const HalfPlane &a, const HalfPlane &b) { return a.ang < b.ang; });
    deque<HalfPlane> dq;
    for (auto &h : hs) {
        while (dq.size() > 1 && h.out(hp_intersection(dq[dq.size() - 1], dq[dq.size() - 2]))) dq.pop_back();
        while (dq.size() > 1 && h.out(hp_intersection(dq[0], dq[1]))) dq.pop_front();
        if (!dq.empty() && fabs(h.v.cross(dq.back().v)) < EPS) {   // 与队尾平行
            if (h.v.dot(dq.back().v) < 0) return {};   // 方向相反且相邻：交为空
            if (h.out(dq.back().p)) dq.pop_back();      // 方向相同：只保留更靠内的那条
            else continue;
        }
        dq.push_back(h);
    }
    // 最后用队头、队尾互相检查一次
    while (dq.size() > 2 && dq[0].out(hp_intersection(dq[dq.size() - 1], dq[dq.size() - 2]))) dq.pop_back();
    while (dq.size() > 2 && dq.back().out(hp_intersection(dq[0], dq[1]))) dq.pop_front();
    if (dq.size() < 3) return {};
    vector<Pd> res;
    for (size_t i = 0; i < dq.size(); i++) res.push_back(hp_intersection(dq[i], dq[(i + 1) % dq.size()]));
    double area2 = 0;   // 面积为 0 说明退化（或数值误差造成的假交点），按空处理
    for (size_t i = 0; i < res.size(); i++) area2 += res[i].cross(res[(i + 1) % res.size()]);
    if (area2 < EPS) return {};
    return res;
}
