#include "../common.hpp"
#include "../../templates/02_ds/07_segment_tree.hpp"

int main() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(1, 40);
        // 例 1：区间加、区间和、区间最大值、线段树上二分
        auto a = rnd_vec(n, -20, 20);
        vector<SumInfo> init(n);
        for (int i = 0; i < n; i++) init[i] = {a[i], a[i], 1};
        LazySegTree<SumInfo, AddTag> seg(init);
        // 例 2：区间乘加取模
        AFFINE_MOD = rnd(0, 1) ? 998244353 : 7;
        auto b = rnd_vec(n, 0, AFFINE_MOD - 1);
        vector<ModSumInfo> init2(n);
        for (int i = 0; i < n; i++) init2[i] = {b[i], 1};
        LazySegTree<ModSumInfo, AffineTag> seg2(init2);
        // 例 3：最大子段和
        auto c = rnd_vec(n, -10, 10);
        vector<SubInfo> init3(n);
        for (int i = 0; i < n; i++) init3[i] = SubInfo::leaf(c[i]);
        LazySegTree<SubInfo, NoTag> seg3(init3);

        for (int op = 0; op < 100; op++) {
            int l = rnd(0, n - 1), r = rnd(l + 1, n);
            int t = rnd(0, 3);
            if (t == 0) {
                ll x = rnd(-5, 5);
                seg.range_apply(l, r, {x});
                for (int i = l; i < r; i++) a[i] += x;
            } else if (t == 1) {
                int p = rnd(0, n - 1);
                ll x = rnd(-20, 20);
                seg.modify(p, {x, x, 1}), a[p] = x;
            } else if (t == 2) {
                ll k = rnd(-25, 25);
                int expect = -1;
                for (int i = l; i < r; i++)
                    if (a[i] >= k) { expect = i; break; }
                CHECK(seg.find_first(l, r, [&](const SumInfo &s) { return s.len && s.mx >= k; }) == expect);
            }
            auto q = seg.query(l, r);
            CHECK(q.sum == accumulate(a.begin() + l, a.begin() + r, 0LL));
            CHECK(q.mx == *max_element(a.begin() + l, a.begin() + r));

            ll mu = rnd(0, AFFINE_MOD - 1), ad = rnd(0, AFFINE_MOD - 1);
            seg2.range_apply(l, r, {mu, ad});
            for (int i = l; i < r; i++) b[i] = (b[i] * mu + ad) % AFFINE_MOD;
            int l2 = rnd(0, n - 1), r2 = rnd(l2 + 1, n);
            ll s2 = 0;
            for (int i = l2; i < r2; i++) s2 = (s2 + b[i]) % AFFINE_MOD;
            CHECK(seg2.query(l2, r2).sum == s2);

            int p = rnd(0, n - 1);
            c[p] = rnd(-10, 10);
            seg3.modify(p, SubInfo::leaf(c[p]));
            ll best = LLONG_MIN;
            for (int i = l; i < r; i++) {
                ll s = 0;
                for (int j = i; j < r; j++) s += c[j], best = max(best, s);
            }
            CHECK(seg3.query(l, r).best == best);
        }
    }
    return 0;
}
