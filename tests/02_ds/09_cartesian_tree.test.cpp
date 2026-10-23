#include "../common.hpp"
#include "../../templates/02_ds/09_cartesian_tree.hpp"

int main() {
    for (int it = 0; it < 1000; it++) {
        int n = rnd(1, 40);
        auto a = rnd_vec(n, -5, 5);
        for (int big = 0; big < 2; big++) {
            vector<int> lc, rc, fa, L, R;
            int root;
            auto better = [&](ll x, ll y) { return big ? x > y : x < y; };   // x 严格更优
            if (big) {
                CartesianTree<ll, greater<ll>> ct(a);
                lc = ct.lc, rc = ct.rc, fa = ct.fa, L = ct.L, R = ct.R, root = ct.root;
            } else {
                CartesianTree<ll> ct(a);
                lc = ct.lc, rc = ct.rc, fa = ct.fa, L = ct.L, R = ct.R, root = ct.root;
            }
            // 根是最左边的最优值
            int r = 0;
            for (int i = 1; i < n; i++)
                if (better(a[i], a[r])) r = i;
            CHECK(root == r && fa[root] == -1);
            for (int u = 0; u < n; u++) {
                // [L, R] 是 u 作为"最左最优值"的极大区间
                int l = u, rr = u;
                while (l > 0 && better(a[u], a[l - 1])) l--;
                while (rr + 1 < n && !better(a[rr + 1], a[u])) rr++;
                CHECK(L[u] == l && R[u] == rr);
                if (lc[u] != -1) CHECK(fa[lc[u]] == u && lc[u] < u);
                if (rc[u] != -1) CHECK(fa[rc[u]] == u && rc[u] > u);
            }
        }
        ll s = 0;
        for (int i = 0; i < n; i++) {
            ll mn = LLONG_MAX;
            for (int j = i; j < n; j++) mn = min(mn, a[j]), s += mn;
        }
        CHECK(sum_of_subarray_min(a) == s);
    }
    return 0;
}
