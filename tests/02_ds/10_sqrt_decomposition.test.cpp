#include "../common.hpp"
#include "../../templates/02_ds/10_sqrt_decomposition.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 60);
        auto a = rnd_vec(n, -20, 20);
        BlockSum bs(a);
        BlockCount bc(a);
        auto b = a;
        for (int op = 0; op < 100; op++) {
            int l = rnd(0, n), r = rnd(l, n);
            if (rnd(0, 1)) {
                ll x = rnd(-5, 5);
                bs.add(l, r, x), bc.add(l, r, x);
                for (int i = l; i < r; i++) b[i] += x;
            } else {
                ll s = 0, x = rnd(-25, 25);
                int c = 0;
                for (int i = l; i < r; i++) s += b[i], c += b[i] >= x;
                CHECK(bs.query(l, r) == s);
                CHECK(bc.count_ge(l, r, x) == c);
            }
        }
    }
    return 0;
}
