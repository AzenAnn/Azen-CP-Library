/**
 * 02_ds/24 K-D Tree
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/07 线段树（含懒标记）
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 建树：按维度交替选择中位数，递归建树
 *   2. 最近邻查询：优先搜索更近的子树，回溯时检查另一子树
 *   3. 范围查询：矩形区域内查询，利用边界剪枝
 *   4. 应用：高维空间最近邻、平面点集查询
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/kdt/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P14312  P14312 【模板】K-D Tree
 *   https://www.luogu.com.cn/problem/P4148  P4148 简单题
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1429  提高  P1429 平面最近点对（加强版）  考点：K-D Tree、计算几何、递归
 *   https://www.luogu.com.cn/problem/P4169  提高+/省选−  P4169 [Violet] 天使玩偶/SJY摆棋子  考点：树状数组、cdq 分治、分治
 *   https://www.luogu.com.cn/problem/P4390  提高+/省选−  P4390 [BalkanOI 2007] Mokia 摩基亚  考点：K-D Tree、树状数组、cdq 分治
 *   https://www.luogu.com.cn/problem/P6247  提高+/省选−  P6247 [SDOI2012] 最近最远点对  考点：K-D Tree、分治、凸包
 *   https://www.luogu.com.cn/problem/P2093  省选/NOI−  P2093 [国家集训队] JZPFAR  考点：K-D Tree
 *   https://www.luogu.com.cn/problem/P2479  省选/NOI−  P2479 [SDOI2010] 捉迷藏  考点：K-D Tree、搜索、递归
 *   https://www.luogu.com.cn/problem/P3769  省选/NOI−  P3769 [CH弱省胡策R2] TATT  考点：K-D Tree、线段树、平衡树
 *   https://www.luogu.com.cn/problem/P4357  省选/NOI−  P4357 [CQOI2016] K 远点对  考点：K-D Tree 求第 k 远点对（维护大小为 2k 的堆）
 *   https://www.luogu.com.cn/problem/P6224  省选/NOI−  P6224 [BJWC2014] 数据  考点：K-D Tree、树状数组、cdq 分治
 *   https://www.luogu.com.cn/problem/P4631  NOI/NOI+/CTS  P4631 [APIO2018] 选圆圈  考点：K-D Tree、搜索、剪枝
 *
 */

// 二维 KD-Tree（静态建树）：轮流按 x、y 取中位数划分，每个节点记录子树的包围盒和权值和。
// 最近点查询期望 O(log n)（最坏 O(√n)），矩形查询 O(√n)。坐标为整数，距离用平方（ll）。
struct KDTree {
    struct Pt { ll x, y, w; int id; };
    vector<Pt> p;                          // 建树后重排：节点 i 就是 p[i]（以子树区间中点为根）
    vector<ll> mnx, mxx, mny, mxy, sum;    // 子树 [l, r] 的包围盒和权值和，下标为子树根
    KDTree(vector<Pt> pts) : p(pts) {
        int n = p.size();
        mnx.resize(n), mxx.resize(n), mny.resize(n), mxy.resize(n), sum.resize(n);
        if (n) build(0, n - 1, 0);
    }
    void build(int l, int r, int dim) {
        int m = (l + r) / 2;
        nth_element(p.begin() + l, p.begin() + m, p.begin() + r + 1,
                    [&](const Pt &a, const Pt &b) { return dim ? a.y < b.y : a.x < b.x; });
        if (l < m) build(l, m - 1, !dim);
        if (m < r) build(m + 1, r, !dim);
        mnx[m] = mxx[m] = p[m].x, mny[m] = mxy[m] = p[m].y, sum[m] = p[m].w;
        for (int c : {(l + m - 1) / 2, (m + 1 + r) / 2})
            if ((c < m && l < m) || (c > m && m < r)) {
                mnx[m] = min(mnx[m], mnx[c]), mxx[m] = max(mxx[m], mxx[c]);
                mny[m] = min(mny[m], mny[c]), mxy[m] = max(mxy[m], mxy[c]);
                sum[m] += sum[c];
            }
    }
    // 包围盒到点 (x, y) 的最小距离平方（下界，用于剪枝）
    ll box_dist(int m, ll x, ll y) const {
        ll dx = x < mnx[m] ? mnx[m] - x : x > mxx[m] ? x - mxx[m] : 0;
        ll dy = y < mny[m] ? mny[m] - y : y > mxy[m] ? y - mxy[m] : 0;
        return dx * dx + dy * dy;
    }
    // 1. 离 (x, y) 最近的点的距离平方；skip_id 为要跳过的点（如查询点自己），没有可用点时返回 LLONG_MAX
    ll nearest(ll x, ll y, int skip_id = -1) const {
        ll best = LLONG_MAX;
        if (!p.empty()) near(0, p.size() - 1, x, y, skip_id, best);
        return best;
    }
    void near(int l, int r, ll x, ll y, int skip, ll &best) const {
        int m = (l + r) / 2;
        if (box_dist(m, x, y) >= best) return;
        if (p[m].id != skip) {
            ll dx = p[m].x - x, dy = p[m].y - y;
            best = min(best, dx * dx + dy * dy);
        }
        int a = l < m ? (l + m - 1) / 2 : -1, b = m < r ? (m + 1 + r) / 2 : -1;
        ll da = a < 0 ? LLONG_MAX : box_dist(a, x, y), db = b < 0 ? LLONG_MAX : box_dist(b, x, y);
        if (da <= db) {   // 先搜更可能近的一侧
            if (a >= 0) near(l, m - 1, x, y, skip, best);
            if (b >= 0) near(m + 1, r, x, y, skip, best);
        } else {
            if (b >= 0) near(m + 1, r, x, y, skip, best);
            if (a >= 0) near(l, m - 1, x, y, skip, best);
        }
    }
    // 2. 矩形 [x1, x2] × [y1, y2] 内的点的权值和
    ll rect_sum(ll x1, ll x2, ll y1, ll y2) const { return p.empty() ? 0 : rect(0, p.size() - 1, x1, x2, y1, y2); }
    ll rect(int l, int r, ll x1, ll x2, ll y1, ll y2) const {
        int m = (l + r) / 2;
        if (mxx[m] < x1 || mnx[m] > x2 || mxy[m] < y1 || mny[m] > y2) return 0;   // 完全在外
        if (x1 <= mnx[m] && mxx[m] <= x2 && y1 <= mny[m] && mxy[m] <= y2) return sum[m];   // 完全在内
        ll s = (x1 <= p[m].x && p[m].x <= x2 && y1 <= p[m].y && p[m].y <= y2) ? p[m].w : 0;
        if (l < m) s += rect(l, m - 1, x1, x2, y1, y2);
        if (m < r) s += rect(m + 1, r, x1, x2, y1, y2);
        return s;
    }
};
