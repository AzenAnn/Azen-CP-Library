#include "../common.hpp"
#include "../../templates/07_string/10_general_sam.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int k = rnd(1, 5), sig = rnd(1, 3);
        vector<string> strs(k);
        for (auto &s : strs) {
            int L = rnd(0, 10);
            for (int i = 0; i < L; i++) s += char('a' + rnd(0, sig - 1));
        }
        GeneralSAM g;
        for (auto &s : strs) g.insert(s);
        set<string> all;
        vector<set<string>> each(k);
        for (int i = 0; i < k; i++)
            for (size_t l = 0; l < strs[i].size(); l++)
                for (size_t r = l + 1; r <= strs[i].size(); r++) all.insert(strs[i].substr(l, r - l)), each[i].insert(strs[i].substr(l, r - l));
        CHECK(g.distinct_substrings() == (ll)all.size());
        int best = 0;
        for (auto &t : all) {
            bool ok = true;
            for (int i = 0; i < k; i++) ok &= each[i].count(t) > 0;
            if (ok) best = max(best, (int)t.size());
        }
        CHECK(g.common_substring() == best);
        // SAM 识别的串恰好是所有子串：随机串检查
        for (int q = 0; q < 20; q++) {
            string t;
            int L = rnd(1, 5);
            for (int i = 0; i < L; i++) t += char('a' + rnd(0, sig - 1));
            int v = 0;
            for (char ch : t)
                if (v != -1) v = g.nx[v][ch - 'a'];
            CHECK((v != -1) == (all.count(t) > 0));
        }
    }
    return 0;
}
