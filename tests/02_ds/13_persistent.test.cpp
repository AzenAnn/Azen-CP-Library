#include "../common.hpp"
#include "../../templates/02_ds/13_persistent.hpp"

int main() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(1, 30);
        auto a = rnd_vec(n, -10, 10);
        vector<ll> vals(a);
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        PersistentSeg ps(vals.size());
        vector<int> root(n + 1, 0);
        for (int i = 0; i < n; i++) root[i + 1] = ps.insert(root[i], lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin());
        for (int q = 0; q < 50; q++) {
            int l = rnd(0, n - 1), r = rnd(l + 1, n), k = rnd(1, r - l);
            vector<ll> s(a.begin() + l, a.begin() + r);
            sort(s.begin(), s.end());
            CHECK(vals[ps.kth(root[r], root[l], k)] == s[k - 1]);
        }
        // 可持久化数组
        PersistentArray pa(a);
        vector<vector<ll>> vers{a};
        for (int op = 0; op < 60; op++) {
            int ver = rnd(0, vers.size() - 1), pos = rnd(0, n - 1);
            if (rnd(0, 1)) {
                ll v = rnd(-10, 10);
                CHECK(pa.update(ver, pos, v) == (int)vers.size());
                vers.push_back(vers[ver]), vers.back()[pos] = v;
            } else {
                CHECK(pa.get(ver, pos) == vers[ver][pos]);
                pa.copy_version(ver), vers.push_back(vers[ver]);
            }
        }
        for (size_t v = 0; v < vers.size(); v++)
            for (int i = 0; i < n; i++) CHECK(pa.get(v, i) == vers[v][i]);
        // 可持久化 Trie
        PersistentTrie pt;
        vector<int> b(n);
        for (int &x : b) x = rnd(0, 1023), pt.push(x);
        for (int q = 0; q < 50; q++) {
            int l = rnd(0, n - 1), r = rnd(l + 1, n), x = rnd(0, 1023), best = 0;
            for (int i = l; i < r; i++) best = max(best, x ^ b[i]);
            CHECK(pt.max_xor(l, r, x) == best);
        }
    }
    return 0;
}
