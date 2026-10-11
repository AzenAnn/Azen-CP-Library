#include "../common.hpp"
#include "../../templates/02_ds/02_monotone_queue.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(1, 30), k = rnd(1, n);
        auto a = rnd_vec(n, -5, 5);
        vector<ll> expect;
        for (int i = 0; i + k <= n; i++) expect.push_back(*max_element(a.begin() + i, a.begin() + i + k));
        CHECK(window_max(a, k) == expect);

        MaxQueue q;
        deque<ll> ref;
        for (int op = 0; op < 60; op++) {
            if (ref.empty() || rnd(0, 2)) {
                ll x = rnd(-5, 5);
                q.push(x), ref.push_back(x);
            } else {
                q.pop(), ref.pop_front();
            }
            CHECK(q.size() == (int)ref.size());
            if (!ref.empty()) CHECK(q.max() == *max_element(ref.begin(), ref.end()));
        }
    }
    return 0;
}
