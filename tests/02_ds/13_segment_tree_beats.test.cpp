#include "../common.hpp"
#include "../../templates/02_ds/13_segment_tree_beats.hpp"

int main() {
    for (int it = 0; it < 400; it++) {
        int n = rnd(1, 30);
        ll V = rnd(1, 3) == 1 ? 3 : 1000;   // 小值域时会频繁出现"只有一两种值"的节点
        auto a = rnd_vec(n, -V, V);
        SegBeats sb(a);
        for (int q = 0; q < 300; q++) {
            int l = rnd(0, n - 1), r = rnd(0, n - 1);
            if (l > r) swap(l, r);
            int op = rnd(0, 5);
            ll v = rnd(-V, V);
            if (op == 0) {
                sb.range_add(l, r, v);
                for (int i = l; i <= r; i++) a[i] += v;
            } else if (op == 1) {
                sb.range_chmin(l, r, v);
                for (int i = l; i <= r; i++) a[i] = min(a[i], v);
            } else if (op == 2) {
                sb.range_chmax(l, r, v);
                for (int i = l; i <= r; i++) a[i] = max(a[i], v);
            } else {
                ll s = 0, mx = LLONG_MIN, mn = LLONG_MAX;
                for (int i = l; i <= r; i++) s += a[i], mx = max(mx, a[i]), mn = min(mn, a[i]);
                CHECK(sb.query_sum(l, r) == s);
                CHECK(sb.query_max(l, r) == mx);
                CHECK(sb.query_min(l, r) == mn);
            }
        }
    }
    return 0;
}
