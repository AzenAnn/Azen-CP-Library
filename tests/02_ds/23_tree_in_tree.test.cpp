#include "../common.hpp"
#include "../../templates/02_ds/23_tree_in_tree.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 30), V = rnd(1, 40);
        vector<int> a(n);
        BitSegKth t(n, V);
        for (int i = 0; i < n; i++) a[i] = rnd(0, V - 1), t.add(i, a[i], 1);
        for (int q = 0; q < 200; q++) {
            int l = rnd(0, n - 1), r = rnd(0, n - 1);
            if (l > r) swap(l, r);
            int op = rnd(0, 2);
            if (op == 0) {
                int pos = rnd(0, n - 1), v = rnd(0, V - 1);
                t.add(pos, a[pos], -1), a[pos] = v, t.add(pos, v, 1);
            } else if (op == 1) {
                vector<int> b(a.begin() + l, a.begin() + r + 1);
                sort(b.begin(), b.end());
                int k = rnd(1, b.size());
                CHECK(t.kth(l, r, k) == b[k - 1]);
            } else {
                int v = rnd(-1, V + 1), c = 0;
                for (int i = l; i <= r; i++) c += a[i] < v;
                CHECK(t.count_less(l, r, v) == c);
            }
        }
    }
    return 0;
}
