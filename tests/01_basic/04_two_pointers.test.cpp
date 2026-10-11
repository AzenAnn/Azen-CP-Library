#include "../common.hpp"
#include "../../templates/01_basic/04_two_pointers.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(1, 25);
        auto a = rnd_vec(n, -20, 20);
        int k = rnd(1, n);
        ll best = LLONG_MIN;
        for (int i = 0; i + k <= n; i++) best = max(best, accumulate(a.begin() + i, a.begin() + i + k, 0LL));
        CHECK(max_window_sum(a, k) == best);

        vector<int> c(n);
        for (auto &x : c) x = rnd(0, 6);
        int bl = 0;
        for (int l = 0; l < n; l++)
            for (int r = l; r < n; r++) {
                set<int> s(c.begin() + l, c.begin() + r + 1);
                if ((int)s.size() == r - l + 1) bl = max(bl, r - l + 1);
            }
        CHECK(longest_distinct(c) == bl);

        auto p = rnd_vec(n, 1, 10);
        ll S = rnd(1, 60);
        int bs = -1;
        ll cnt = 0;
        for (int l = 0; l < n; l++)
            for (int r = l; r < n; r++) {
                ll sum = accumulate(p.begin() + l, p.begin() + r + 1, 0LL);
                if (sum >= S && (bs == -1 || r - l + 1 < bs)) bs = r - l + 1;
                cnt += sum <= S;
            }
        CHECK(shortest_sum_at_least(p, S) == bs);
        CHECK(count_sum_at_most(p, S) == cnt);

        auto q = rnd_vec(n, -10, 10);
        sort(q.begin(), q.end());
        ll t = rnd(-20, 20);
        bool exist = false;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) exist |= q[i] + q[j] == t;
        auto [i, j] = two_sum_sorted(q, t);
        if (exist) CHECK(i >= 0 && i < j && q[i] + q[j] == t);
        else CHECK(i == -1);
    }
    return 0;
}
