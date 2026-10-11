#include "../common.hpp"
#include "../../templates/02_ds/10_mo.hpp"

int main() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(1, 40), q = rnd(1, 40);
        vector<int> a(n);
        for (int &x : a) x = rnd(0, 6);
        // 1. 区间不同数的个数
        vector<pair<int, int>> qs;
        for (int i = 0; i < q; i++) {
            int l = rnd(0, n - 1), r = rnd(l + 1, n);
            qs.push_back({l, r});
        }
        vector<int> cnt(10, 0);
        int distinct = 0;
        auto res = mo(n, qs, [&](int i) { distinct += cnt[a[i]]++ == 0; },
                      [&](int i) { distinct -= --cnt[a[i]] == 0; }, [&] { return distinct; });
        for (int i = 0; i < q; i++) {
            set<int> s(a.begin() + qs[i].first, a.begin() + qs[i].second);
            CHECK(res[i] == (int)s.size());
        }
        // 3. 回滚莫队：区间内某个数出现次数的最大值
        vector<int> c2(10, 0), hist;
        int best = 0, saved_best = 0;
        size_t saved = 0;
        auto res2 = mo_rollback(
            n, qs, [&] { fill(c2.begin(), c2.end(), 0), best = 0, hist.clear(); },
            [&](int i) { hist.push_back(a[i]), best = max(best, ++c2[a[i]]); },
            [&] { saved = hist.size(), saved_best = best; },
            [&] {
                while (hist.size() > saved) c2[hist.back()]--, hist.pop_back();
                best = saved_best;
            },
            [&] { return best; });
        for (int i = 0; i < q; i++) {
            map<int, int> m;
            int mx = 0;
            for (int j = qs[i].first; j < qs[i].second; j++) mx = max(mx, ++m[a[j]]);
            CHECK(res2[i] == mx);
        }
        // 2. 带修莫队：单点修改 + 区间不同数个数
        vector<pair<int, int>> ups;
        vector<array<int, 3>> q3;
        vector<int> expect;
        auto cur = a;
        for (int i = 0; i < q; i++) {
            if (rnd(0, 1)) {
                int p = rnd(0, n - 1), v = rnd(0, 6);
                ups.push_back({p, v}), cur[p] = v;
            } else {
                int l = rnd(0, n - 1), r = rnd(l + 1, n);
                q3.push_back({l, r, (int)ups.size()});
                expect.push_back(set<int>(cur.begin() + l, cur.begin() + r).size());
            }
        }
        fill(cnt.begin(), cnt.end(), 0), distinct = 0;
        auto orig = a;
        auto res3 = mo_with_updates(a, q3, ups, [&](int i) { distinct += cnt[a[i]]++ == 0; },
                                    [&](int i) { distinct -= --cnt[a[i]] == 0; }, [&] { return distinct; });
        CHECK(res3 == expect);
        CHECK(a == orig);
    }
    // 4. 树上莫队：路径上不同颜色的个数
    for (int it = 0; it < 200; it++) {
        int n = rnd(1, 25);
        vector<vector<int>> g(n);
        vector<int> par(n, -1), dep(n, 0), col(n);
        for (int &c : col) c = rnd(0, 5);
        for (int v = 1; v < n; v++) {
            int u = rnd(0, v - 1);
            g[u].push_back(v), g[v].push_back(u), par[v] = u, dep[v] = dep[u] + 1;
        }
        TreeMoRanges tm(g, 0);
        int q = rnd(1, 30);
        vector<pair<int, int>> qs;
        vector<int> extra, qu, qv;
        for (int i = 0; i < q; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            auto [l, r, e] = tm.range(u, v);
            qs.push_back({l, r}), extra.push_back(e), qu.push_back(u), qv.push_back(v);
        }
        vector<int> cnt(6, 0), in(n, 0);
        int distinct = 0;
        auto toggle = [&](int x) {
            if ((in[x] ^= 1)) distinct += cnt[col[x]]++ == 0;
            else distinct -= --cnt[col[x]] == 0;
        };
        // 用 mo 处理括号序区间（add / remove 都是 toggle）；extra 在下面单独判断
        auto res = mo((int)tm.euler.size(), qs, [&](int i) { toggle(tm.euler[i]); },
                      [&](int i) { toggle(tm.euler[i]); }, [&] { return distinct; });
        for (int i = 0; i < q; i++) {
            // 暴力求路径颜色集合
            int x = qu[i], y = qv[i];
            set<int> s;
            while (dep[x] > dep[y]) s.insert(col[x]), x = par[x];
            while (dep[y] > dep[x]) s.insert(col[y]), y = par[y];
            while (x != y) s.insert(col[x]), s.insert(col[y]), x = par[x], y = par[y];
            s.insert(col[x]);
            // res[i] 不含 extra；若 extra 的颜色不在区间中，答案加 1
            int ans = res[i];
            if (extra[i] != -1) {
                // 重新统计区间颜色，判断 LCA 颜色是否已出现
                vector<int> c(6, 0), inn(n, 0);
                for (int j = qs[i].first; j < qs[i].second; j++) inn[tm.euler[j]] ^= 1;
                for (int v = 0; v < n; v++)
                    if (inn[v]) c[col[v]]++;
                if (!c[col[extra[i]]]) ans++;
            }
            CHECK(ans == (int)s.size());
        }
    }
    return 0;
}
