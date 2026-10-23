#include "../common.hpp"
#include "../../templates/03_graph/06_matrix_tree.hpp"

int main() {
    // 行列式：与按定义展开（全排列）对比，模数含合数
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 5);
        ll m = rnd(0, 1) ? 998244353 : rnd(2, 1000);
        vector<vector<ll>> a(n, vector<ll>(n));
        for (auto &r : a)
            for (auto &x : r) x = rnd(0, m - 1);
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        ll s = 0;
        do {
            int inv = 0;
            for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++) inv += p[i] > p[j];
            ll t = 1;
            for (int i = 0; i < n; i++) t = t * a[i][p[i]] % m;
            s = ((s + (inv & 1 ? -t : t)) % m + m) % m;
        } while (next_permutation(p.begin(), p.end()));
        CHECK(det_mod(a, m) == s);
    }
    // 生成树计数：暴力枚举
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 5), E = rnd(0, 8);
        ll m = rnd(0, 1) ? 1000000007 : rnd(2, 100);
        vector<array<ll, 3>> es;
        for (int i = 0; i < E; i++) es.push_back({rnd(0, n - 1), rnd(0, n - 1), rnd(1, 5)});
        // 无向：枚举 n-1 条边的子集
        ll s = 0;
        for (int mask = 0; mask < (1 << E); mask++) {
            if (__builtin_popcount(mask) != n - 1) continue;
            vector<int> f(n);
            iota(f.begin(), f.end(), 0);
            function<int(int)> find = [&](int x) { return f[x] == x ? x : f[x] = find(f[x]); };
            bool ok = true;
            ll prod = 1;
            for (int i = 0; i < E; i++)
                if (mask >> i & 1) {
                    int a = find(es[i][0]), b = find(es[i][1]);
                    if (a == b) ok = false;
                    f[a] = b, prod = prod * es[i][2] % m;
                }
            if (ok) s = (s + prod) % m;
        }
        CHECK(count_spanning_trees(n, es, m) == s % m);
        // 有向：每个非根点选一条入边（外向树）/ 出边（内向树），检查没有环
        int root = rnd(0, n - 1);
        for (int type = 1; type <= 2; type++) {
            vector<vector<int>> cand(n);   // 每个点可选的边
            for (int i = 0; i < E; i++) {
                int u = es[i][0], v = es[i][1];
                if (u == v) continue;
                if (type == 1) cand[v].push_back(i);
                else cand[u].push_back(i);
            }
            ll tot = 0;
            vector<int> par(n, -1);
            function<void(int, ll)> go = [&](int x, ll prod) {
                if (x == n) {
                    for (int v = 0; v < n; v++) {   // 沿 par 走 n 步必须到根
                        int c = v;
                        for (int k = 0; k < n && c != root; k++) c = par[c];
                        if (c != root) return;
                    }
                    tot = (tot + prod) % m;
                    return;
                }
                if (x == root) return go(x + 1, prod);
                for (int i : cand[x]) par[x] = type == 1 ? es[i][0] : es[i][1], go(x + 1, prod * es[i][2] % m);
            };
            go(0, 1 % m);
            CHECK(count_spanning_trees(n, es, m, type, root) == tot);
        }
    }
    return 0;
}
