#include "../common.hpp"
#include "../../templates/07_string/02_kmp.hpp"

int main() {
    for (int it = 0; it < 1000; it++) {
        string s(rnd(0, 30), 'a'), t(rnd(1, 4), 'a');
        for (char &c : s) c = 'a' + rnd(0, 1);
        for (char &c : t) c = 'a' + rnd(0, 1);
        vector<int> occ;
        for (int i = 0; i + t.size() <= s.size(); i++)
            if (s.compare(i, t.size(), t) == 0) occ.push_back(i);
        CHECK(kmp_search(s, t) == occ);
        auto pi = prefix_function(s);
        for (int i = 0; i < (int)s.size(); i++) {
            int best = 0;
            for (int k = 1; k <= i; k++)
                if (s.compare(0, k, s, i + 1 - k, k) == 0) best = k;
            CHECK(pi[i] == best);
        }
        int n = s.size(), p = n;
        for (int q = 1; q <= n; q++) {
            bool ok = true;
            for (int i = 0; i + q < n; i++) ok &= s[i] == s[i + q];
            if (ok) { p = q; break; }
        }
        CHECK(min_period(s) == p);
    }
    return 0;
}
