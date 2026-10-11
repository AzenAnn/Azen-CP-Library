/**
 * 08_geometry/04 扫描线：矩形面积并
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/07 线段树（含懒标记）
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 事件排序
 *   2. 线段树维护覆盖长度
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/geometry/scanning/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/segment_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5490  P5490 【模板】扫描线 & 矩形面积并
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10814  提高  P10814 【模板】离线二维数点  考点：线段树、树状数组、扫描线
 *   https://www.luogu.com.cn/problem/P1502  提高  P1502 窗口的星星  考点：线段树、离散化、扫描线
 *   https://www.luogu.com.cn/problem/P1856  提高  P1856 [IOI 1998 / USACO5.5] 矩形周长 Picture  考点：线段树、扫描线
 *   https://www.luogu.com.cn/problem/P3582  提高  P3582 [POI 2015 R1] 影迷 Movie-goer  考点：线段树、扫描线
 *   https://www.luogu.com.cn/problem/P4113  提高  P4113 [HEOI2012] 采花  考点：线段树、树状数组、排序
 *   https://www.luogu.com.cn/problem/P14363  提高+/省选−  P14363 [CSP-S 2025] 谐音替换  考点：二分、哈希 hashing、扫描线
 *   https://codeforces.com/problemset/problem/1278/D  CF2100  CF1278D Segment Tree  考点：数据结构、并查集、图论
 *   https://codeforces.com/problemset/problem/1285/E  CF2300  CF1285E Delete a Segment  考点：暴力、构造、数据结构
 *   https://codeforces.com/problemset/problem/1379/D  CF2300  CF1379D New Passenger Trams  考点：二分、暴力、数据结构
 *   https://codeforces.com/problemset/problem/610/D  CF2300  CF610D Vika and Segments  考点：构造、数据结构、计算几何
 *   https://codeforces.com/problemset/problem/258/E  CF2400  CF258E Little Elephant and Tree  考点：数据结构、搜索、树
 *   https://www.luogu.com.cn/problem/P11364  省选/NOI−  P11364 [NOIP2024] 树上查询  考点：线段树、cdq 分治、最近公共祖先 LCA
 *   https://www.luogu.com.cn/problem/P3246  省选/NOI−  P3246 [HNOI2016] 序列  考点：莫队、线段树、前缀和
 *   https://www.luogu.com.cn/problem/P3863  省选/NOI−  P3863 序列  考点：排序、分块、扫描线
 *   https://www.luogu.com.cn/problem/P8078  省选/NOI−  P8078 [WC2022] 秃子酋长  考点：莫队、分治、扫描线
 *
 */

// 扫描线：矩形面积并（洛谷 P5490）。
// 用一条竖直的扫描线从左往右扫，遇到矩形左边界时把 [y1, y2) 覆盖次数加一，右边界时减一；
// 相邻两个事件之间，面积 = 被覆盖的 y 总长度 × x 的差。
// y 坐标离散化后用线段树维护：cnt 为整段被完整覆盖的次数，len 为区间内被覆盖的长度。
// 这里的标记不下传：cnt > 0 时整段被覆盖，否则长度由两个儿子合并。O(n log n)
// rects[i] = {x1, y1, x2, y2}，要求 x1 < x2、y1 < y2
ll rect_union_area(const vector<array<ll, 4>> &rects) {
    vector<ll> ys;
    for (auto &r : rects) ys.push_back(r[1]), ys.push_back(r[3]);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int m = ys.size();
    if (m < 2) return 0;
    vector<int> cnt(4 * m, 0);
    vector<ll> len(4 * m, 0);
    // 节点 p 管辖第 [l, r) 个基本区间，第 i 个基本区间为 [ys[i], ys[i+1])
    function<void(int, int, int, int, int, int)> update = [&](int p, int l, int r, int x, int y, int v) {
        if (y <= l || r <= x) return;
        if (x <= l && r <= y) cnt[p] += v;
        else {
            int mid = (l + r) / 2;
            update(2 * p, l, mid, x, y, v), update(2 * p + 1, mid, r, x, y, v);
        }
        if (cnt[p] > 0) len[p] = ys[r] - ys[l];
        else len[p] = r - l == 1 ? 0 : len[2 * p] + len[2 * p + 1];
    };
    vector<array<ll, 4>> ev;   // (x, 类型 +1/-1, y1, y2)
    for (auto &r : rects) ev.push_back({r[0], 1, r[1], r[3]}), ev.push_back({r[2], -1, r[1], r[3]});
    sort(ev.begin(), ev.end());
    ll area = 0;
    for (size_t i = 0; i < ev.size(); i++) {
        if (i) area += len[1] * (ev[i][0] - ev[i - 1][0]);
        int a = lower_bound(ys.begin(), ys.end(), ev[i][2]) - ys.begin();
        int b = lower_bound(ys.begin(), ys.end(), ev[i][3]) - ys.begin();
        update(1, 0, m - 1, a, b, ev[i][1]);
    }
    return area;
}
