#include "../common.hpp"
#include "../../templates/02_ds/12_segment_tree_adv.hpp"

int main() {
    // 动态开点：多棵树 + 合并 + 分裂，与 multiset 对比
    for (int it = 0; it < 200; it++) {
        ll lo = rnd(-50, 0), hi = rnd(1, 50);
        DynSeg seg(lo, hi);
        int K = rnd(1, 4);
        vector<int> roots(K, 0);
        vector<multiset<ll>> ref(K);
        for (int op = 0; op < 80; op++) {
            int a = rnd(0, K - 1), t = rnd(0, 4);
            if (t <= 1) {
                ll v = rnd(lo, hi - 1);
                roots[a] = seg.add(roots[a], v, 1), ref[a].insert(v);
            } else if (t == 2) {
                int b = rnd(0, K - 1);
                if (a == b) continue;
                roots[a] = seg.merge(roots[a], roots[b]), roots[b] = 0;
                ref[a].insert(ref[b].begin(), ref[b].end()), ref[b].clear();
            } else if (t == 3) {
                int b = rnd(0, K - 1);
                if (a == b || !ref[b].empty()) continue;
                ll l = rnd(lo, hi), r = rnd(l, hi);
                auto [p, q] = seg.split(roots[a], l, r);
                roots[a] = p, roots[b] = q;
                for (auto itr = ref[a].lower_bound(l); itr != ref[a].end() && *itr < r;) ref[b].insert(*itr), itr = ref[a].erase(itr);
            }
            for (int x = 0; x < K; x++) {
                ll l = rnd(lo, hi), r = rnd(l, hi);
                ll c = 0;
                for (ll v : ref[x]) c += l <= v && v < r;
                CHECK(seg.count(roots[x], l, r) == c);
                if (!ref[x].empty()) {
                    int k = rnd(1, ref[x].size());
                    CHECK(seg.kth(roots[x], k) == *next(ref[x].begin(), k - 1));
                }
            }
        }
    }
    // 李超线段树：直线和线段，与暴力对比
    for (int it = 0; it < 200; it++) {
        ll lo = rnd(-30, 0), hi = rnd(1, 30);
        LiChao lc(lo, hi);
        vector<array<ll, 4>> segs;   // k, b, xl, xr
        for (int op = 0; op < 40; op++) {
            ll k = rnd(-10, 10), b = rnd(-100, 100);
            if (rnd(0, 1)) lc.insert_line(k, b), segs.push_back({k, b, lo, hi});
            else {
                ll xl = rnd(lo, hi), xr = rnd(xl, hi);
                lc.insert_segment(k, b, xl, xr), segs.push_back({k, b, xl, xr});
            }
            ll x = rnd(lo, hi - 1), best = LLONG_MIN;
            for (auto &s : segs)
                if (s[2] <= x && x < s[3]) best = max(best, s[0] * x + s[1]);
            CHECK(lc.query(x) == best);
        }
    }
    return 0;
}
