#include "../common.hpp"
#include "../../templates/03_graph/19_flow_bound.hpp"

int main() {
    for (int it = 0; it < 600; it++) {
        int n = rnd(2, 4), m = rnd(1, 5), s = rnd(0, n - 1), t = rnd(0, n - 1);
        if (s == t) t = (s + 1) % n;
        vector<array<ll, 4>> es;
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            if (it % 2 == 0)   // 一半数据满足"没有流入 s、流出 t 的边"，用来测有源汇的最大 / 最小流
                while (v == s || u == t) u = rnd(0, n - 1), v = rnd(0, n - 1);
            ll lo = rnd(0, 2), hi = lo + rnd(0, 2);
            es.push_back({u, v, lo, hi});
        }
        // 暴力：枚举每条边的流量
        bool circ = false;
        ll mx = LLONG_MIN, mn = LLONG_MAX;
        vector<ll> f(m);
        function<void(int)> go = [&](int i) {
            if (i == m) {
                vector<ll> net(n, 0);   // 流出 − 流入
                for (int j = 0; j < m; j++) net[es[j][0]] += f[j], net[es[j][1]] -= f[j];
                bool all = true, st = true;
                for (int x = 0; x < n; x++) {
                    if (net[x]) all = false;
                    if (x != s && x != t && net[x]) st = false;
                }
                if (all) circ = true;
                if (st) mx = max(mx, net[s]), mn = min(mn, net[s]);
                return;
            }
            for (f[i] = es[i][2]; f[i] <= es[i][3]; f[i]++) go(i + 1);
        };
        go(0);
        BoundedFlow bf(n);
        for (auto [u, v, lo, hi] : es) bf.add_edge(u, v, lo, hi);
        bool c = bf.circulation();
        CHECK(c == circ);
        if (c) {   // 给出的流量合法
            vector<ll> net(n, 0);
            for (int j = 0; j < m; j++) {
                ll x = bf.flow_of(j);
                CHECK(es[j][2] <= x && x <= es[j][3]);
                net[es[j][0]] += x, net[es[j][1]] -= x;
            }
            for (int x = 0; x < n; x++) CHECK(net[x] == 0);
        }
        // 本题的 max_flow / min_flow 以"从 s 净流出"为流量；暴力里净流出可能为负，模板也按同样定义
        if (it % 2) continue;   // 另一半数据只测无源汇可行流
        ll a = bf.max_flow(s, t), b = bf.min_flow(s, t);
        if (mx == LLONG_MIN) CHECK(a == LLONG_MIN && b == LLONG_MIN);
        else {
            if (!(a == mx && b == mn)) {
                fprintf(stderr, "n=%d s=%d t=%d got %lld %lld want %lld %lld\n", n, s, t, a, b, mx, mn);
                for (auto [u, v, lo, hi] : es) fprintf(stderr, "  %lld->%lld [%lld,%lld]\n", u, v, lo, hi);
            }
            CHECK(a == mx && b == mn);
        }
    }
    return 0;
}
