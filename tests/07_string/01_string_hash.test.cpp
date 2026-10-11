#include "../common.hpp"
#include "../../templates/07_string/01_string_hash.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        string s(rnd(1, 30), 'a'), t(rnd(1, 30), 'a');
        for (char &c : s) c = 'a' + rnd(0, 1);
        for (char &c : t) c = 'a' + rnd(0, 1);
        StrHash hs(s), ht(t);
        for (int q = 0; q < 200; q++) {
            int l1 = rnd(0, s.size()), r1 = rnd(l1, s.size());
            int l2 = rnd(0, t.size()), r2 = rnd(l2, t.size());
            bool eq = s.substr(l1, r1 - l1) == t.substr(l2, r2 - l2);
            CHECK((hs.get(l1, r1) == ht.get(l2, r2)) == eq);
            int i = rnd(0, s.size() - 1), j = rnd(0, t.size() - 1), k = 0;
            while (i + k < (int)s.size() && j + k < (int)t.size() && s[i + k] == t[j + k]) k++;
            CHECK(hash_lcp(hs, i, ht, j) == k);
        }
    }
    return 0;
}
