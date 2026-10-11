#include "../common.hpp"
#include "../../templates/02_ds/03_heap.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        MedianHeap mh;
        vector<ll> v;
        for (int i = 0; i < 40; i++) {
            ll x = rnd(-10, 10);
            mh.push(x), v.push_back(x);
            auto s = v;
            sort(s.begin(), s.end());
            CHECK(mh.median() == s[(s.size() - 1) / 2]);
        }
        LazyHeap lh;
        multiset<ll> ms;
        for (int i = 0; i < 60; i++) {
            int op = rnd(0, 2);
            if (ms.empty() || op == 0) {
                ll x = rnd(0, 8);
                lh.push(x), ms.insert(x);
            } else if (op == 1) {
                auto pos = next(ms.begin(), rnd(0, ms.size() - 1));
                lh.erase(*pos), ms.erase(pos);
            } else {
                CHECK(lh.top() == *ms.rbegin());
                lh.pop(), ms.erase(prev(ms.end()));
            }
            CHECK(lh.size() == ms.size());
            if (!ms.empty()) CHECK(lh.top() == *ms.rbegin());
        }
        vector<vector<ll>> lists(rnd(0, 5));
        vector<ll> all;
        for (auto &l : lists) {
            l = rnd_vec(rnd(0, 6), 0, 20);
            sort(l.begin(), l.end());
            all.insert(all.end(), l.begin(), l.end());
        }
        sort(all.begin(), all.end());
        CHECK(merge_k(lists) == all);
    }
    return 0;
}
