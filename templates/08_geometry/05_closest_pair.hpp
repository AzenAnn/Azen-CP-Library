/**
 * 08_geometry/05 平面最近点对
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：01_basic/10 分治
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 分治做法
 *   2. 按 x 排序 + set 做法
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/geometry/nearest-points/
 *   cp-algorithms  https://cp-algorithms.com/geometry/nearest_points.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/geometry.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1429  P1429 平面最近点对（加强版）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1257  普及−  P1257 平面上的最接近点对  热身：O(n^2) 暴力即可
 *   https://codeforces.com/problemset/problem/120/J  CF1900  CF120J Minimum Sum  翻转坐标后转化为最近点对
 *   https://www.luogu.com.cn/problem/P4169  提高+/省选−  P4169 [Violet] 天使玩偶/SJY摆棋子  曼哈顿最近点：CDQ 分治或 K-D Tree
 *   https://www.luogu.com.cn/problem/P6247  提高+/省选−  P6247 [SDOI2012] 最近最远点对  最近点对 + 最远点对（凸包直径）
 *   https://www.luogu.com.cn/problem/P7883  提高+/省选−  P7883 平面最近点对（加强加强版）  分治 + 按 y 归并，注意用整数算距离
 *   https://codeforces.com/problemset/problem/429/D  CF2200  CF429D Tricky Function  前缀和后转化为最近点对
 *   https://www.luogu.com.cn/problem/P2479  省选/NOI−  P2479 [SDOI2010] 捉迷藏  K-D Tree 求最近 / 最远点
 *   https://www.luogu.com.cn/problem/P4357  省选/NOI−  P4357 [CQOI2016] K 远点对  第 K 远点对：K-D Tree
 *
 */

// 平面最近点对（需要先粘贴 08_geometry/01 的点结构），返回最近距离的平方，要求至少 2 个点。

// 1. 分治：按 x 排序后分成左右两半，分别求出最近距离 d；跨越中线的点对只需考虑距中线 < d 的点，
//    且按 y 排序后每个点只需和前面 y 差 < d 的少数几个点比较。递归时顺便按 y 归并排序。O(n log n)
ll closest_pair2(vector<Pt> a) {
    sort(a.begin(), a.end());
    ll best = LLONG_MAX;
    auto by_y = [](const Pt &p, const Pt &q) { return p.y < q.y; };
    vector<Pt> strip;
    function<void(int, int)> rec = [&](int l, int r) {   // 处理 [l, r)，返回时这一段已按 y 排序
        if (r - l <= 3) {
            for (int i = l; i < r; i++)
                for (int j = i + 1; j < r; j++) best = min(best, (a[i] - a[j]).norm2());
            sort(a.begin() + l, a.begin() + r, by_y);
            return;
        }
        int m = (l + r) / 2;
        ll midx = a[m].x;   // 递归会打乱顺序，先记下中线
        rec(l, m), rec(m, r);
        inplace_merge(a.begin() + l, a.begin() + m, a.begin() + r, by_y);
        strip.clear();
        for (int i = l; i < r; i++) {
            ll dx = a[i].x - midx;
            if (dx * dx >= best) continue;
            for (int j = (int)strip.size() - 1; j >= 0; j--) {
                ll dy = a[i].y - strip[j].y;
                if (dy * dy >= best) break;
                best = min(best, (a[i] - strip[j]).norm2());
            }
            strip.push_back(a[i]);
        }
    };
    rec(0, a.size());
    return best;
}

// 2. 扫描线 + set：按 x 排序后从左往右扫，set 中按 y 维护"x 距离当前点 < d"的点，
//    每个点只需查询 y 在 [y - d, y + d] 内的点。O(n log n)
ll closest_pair2_sweep(vector<Pt> a) {
    sort(a.begin(), a.end());
    set<pair<ll, ll>> s;   // (y, x)
    ll best = LLONG_MAX;
    for (size_t i = 0, j = 0; i < a.size(); i++) {
        ll d = (ll)ceil(sqrtl((long double)best));
        while (j < i && (a[i].x - a[j].x) * (a[i].x - a[j].x) >= best) s.erase({a[j].y, a[j].x}), j++;
        for (auto it = s.lower_bound({a[i].y - d, LLONG_MIN}); it != s.end() && it->first <= a[i].y + d; ++it) {
            ll dx = a[i].x - it->second, dy = a[i].y - it->first;
            best = min(best, dx * dx + dy * dy);
        }
        s.insert({a[i].y, a[i].x});
    }
    return best;
}
