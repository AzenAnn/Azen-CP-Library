#include "../common.hpp"
#include "../../templates/07_string/08_sam.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        string s(rnd(1, 30), 'a');
        for (char &c : s) c = 'a' + rnd(0, it % 2 ? 1 : 2);
        SAM sam(s);
        map<string, ll> occ;
        int n = s.size();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j <= n; j++) occ[s.substr(i, j - i)]++;
        CHECK(sam.distinct_substrings() == (ll)occ.size());
        ll best = 0;
        for (auto &[t, c] : occ)
            if (c > 1) best = max(best, c * (ll)t.size());
        CHECK(sam.max_occ_times_len() == best);
        for (int q = 0; q < 30; q++) {
            string t(rnd(1, 5), 'a');
            for (char &c : t) c = 'a' + rnd(0, 2);
            CHECK(sam.occurrences(t) == (occ.count(t) ? occ[t] : 0));
        }
        CHECK((int)sam.st.size() <= 2 * n);
    }
    return 0;
}
