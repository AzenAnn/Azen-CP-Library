#include "../common.hpp"
#include "../../templates/02_ds/19_leftist_tree.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 30);
        auto a = rnd_vec(n, 0, 10);
        LeftistHeap h(a);
        vector<int> group(n);
        iota(group.begin(), group.end(), 0);
        vector<bool> del(n, false);
        for (int op = 0; op < 80; op++) {
            int x = rnd(0, n - 1);
            if (rnd(0, 1)) {
                int y = rnd(0, n - 1);
                h.unite(x, y);
                if (!del[x] && !del[y] && group[x] != group[y]) {
                    int gx = group[x], gy = group[y];
                    for (int &g : group)
                        if (g == gy) g = gx;
                }
            } else {
                ll got = h.pop(x);
                if (del[x]) { CHECK(got == LLONG_MIN); continue; }
                int best = -1;   // 同组未删除元素中 (值, 编号) 最小的
                for (int i = 0; i < n; i++)
                    if (!del[i] && group[i] == group[x] && (best == -1 || a[i] < a[best])) best = i;
                CHECK(got == a[best]);
                del[best] = true;
            }
        }
    }
    return 0;
}
