#include "../common.hpp"
#include "../../templates/02_ds/12_balanced_tree.hpp"

int main() {
    for (int it = 0; it < 200; it++) {
        FHQTreap fhq;
        Splay sp;
        ordered_set<pair<ll, int>> os;
        multiset<ll> ref;
        int uid = 0;
        for (int op = 0; op < 200; op++) {
            int t = rnd(0, 6);
            ll x = rnd(-20, 20);
            if (t <= 2 || ref.empty()) {
                fhq.insert(x), sp.insert(x), os.insert({x, uid++}), ref.insert(x);
            } else if (t == 3) {
                fhq.erase(x), sp.erase(x);
                if (ref.count(x)) {
                    ref.erase(ref.find(x));
                    os.erase(os.lower_bound({x, INT_MIN}));
                }
            }
            CHECK(fhq.size() == (int)ref.size() && sp.size() == (int)ref.size() && os.size() == ref.size());
            if (ref.empty()) continue;
            int rk = distance(ref.begin(), ref.lower_bound(x)) + 1;
            CHECK(fhq.rank(x) == rk && sp.rank(x) == rk);
            CHECK((int)os.order_of_key({x, INT_MIN}) + 1 == rk);
            int k = rnd(1, ref.size());
            ll kv = *next(ref.begin(), k - 1);
            CHECK(fhq.kth(k) == kv && sp.kth(k) == kv && os.find_by_order(k - 1)->first == kv);
            auto lb = ref.lower_bound(x);
            if (lb != ref.begin()) CHECK(fhq.prev(x) == *prev(lb) && sp.prev(x) == *prev(lb));
            else CHECK(sp.prev_node(x) == 0);
            auto ub = ref.upper_bound(x);
            if (ub != ref.end()) CHECK(fhq.next(x) == *ub && sp.next(x) == *ub);
            else CHECK(sp.next_node(x) == 0);
        }
    }
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 30);
        ImplicitTreap tr;
        vector<ll> v(n);
        iota(v.begin(), v.end(), 0);
        for (ll x : v) tr.push_back(x);
        for (int op = 0; op < 30; op++) {
            int l = rnd(0, n), r = rnd(l, n);
            tr.reverse(l, r), reverse(v.begin() + l, v.begin() + r);
            CHECK(tr.to_vector() == v);
        }
    }
    return 0;
}
