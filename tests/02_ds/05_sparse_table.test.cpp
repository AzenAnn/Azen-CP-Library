#include "../common.hpp"
#include "../../templates/02_ds/05_sparse_table.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 40);
        auto a = rnd_vec(n, -100, 100);
        SparseTable mx(a, [](ll x, ll y) { return max(x, y); });
        auto b = rnd_vec(n, 1, 60);
        SparseTable g(b, [](ll x, ll y) { return __gcd(x, y); });
        for (int l = 0; l < n; l++)
            for (int r = l + 1; r <= n; r++) {
                CHECK(mx.query(l, r) == *max_element(a.begin() + l, a.begin() + r));
                ll gg = 0;
                for (int i = l; i < r; i++) gg = __gcd(gg, b[i]);
                CHECK(g.query(l, r) == gg);
            }
    }
    return 0;
}
