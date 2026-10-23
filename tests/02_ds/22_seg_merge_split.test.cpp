#include "../common.hpp"
#include "../../templates/02_ds/22_seg_merge_split.hpp"

int main() {
    for (int it = 0; it < 200; it++) {
        int V = rnd(1, 50);
        SegMergeSplit sm(V);
        vector<int> root;
        vector<multiset<int>> ms;   // 暴力：每棵树对应一个可重集合
        for (int q = 0; q < 300; q++) {
            int op = rnd(0, 6);
            if (root.empty() || op == 0) {
                root.push_back(0), ms.push_back({});
                continue;
            }
            int i = rnd(0, root.size() - 1);
            if (op == 1) {
                int x = rnd(0, V - 1), c = rnd(1, 3);
                root[i] = sm.insert(root[i], x, c);
                for (int t = 0; t < c; t++) ms[i].insert(x);
            } else if (op == 2 && root.size() >= 2) {
                int j = rnd(0, root.size() - 1);
                if (i == j) continue;
                root[i] = sm.merge(root[i], root[j]);
                ms[i].insert(ms[j].begin(), ms[j].end());
                root.erase(root.begin() + j), ms.erase(ms.begin() + j);
            } else if (op == 3) {
                ll k = rnd(0, ms[i].size() + 1);
                int nr = sm.split_k(root[i], k);
                multiset<int> a, b;
                int c = 0;
                for (int x : ms[i]) (c++ < k ? a : b).insert(x);
                ms[i] = a, root.push_back(nr), ms.push_back(b);
            } else if (op == 4) {
                int v = rnd(-1, V);
                int nr = sm.split_val(root[i], v);
                multiset<int> a, b;
                for (int x : ms[i]) (x <= v ? a : b).insert(x);
                ms[i] = a, root.push_back(nr), ms.push_back(b);
            } else {
                int a = rnd(0, V - 1), b = rnd(0, V - 1);
                if (a > b) swap(a, b);
                ll c = 0, s = 0;
                for (int x : ms[i])
                    if (a <= x && x <= b) c++, s += x;
                CHECK(sm.count(root[i], a, b) == c && sm.range_sum(root[i], a, b) == s);
                if (!ms[i].empty()) {
                    ll k = rnd(1, ms[i].size());
                    CHECK(sm.kth(root[i], k) == *next(ms[i].begin(), k - 1));
                }
            }
        }
        for (size_t i = 0; i < root.size(); i++) CHECK(sm.count(root[i], 0, V - 1) == (ll)ms[i].size());
    }
    return 0;
}
