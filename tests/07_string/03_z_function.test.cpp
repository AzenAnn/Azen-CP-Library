#include "../common.hpp"
#include "../../templates/07_string/03_z_function.hpp"

int main() {
    for (int it = 0; it < 1000; it++) {
        string s(rnd(0, 30), 'a'), t(rnd(1, 4), 'a');
        for (char &c : s) c = 'a' + rnd(0, 1);
        for (char &c : t) c = 'a' + rnd(0, 1);
        auto z = z_function(s);
        for (int i = 0; i < (int)s.size(); i++) {
            int k = 0;
            while (i + k < (int)s.size() && s[k] == s[i + k]) k++;
            CHECK(z[i] == k);
        }
        vector<int> occ;
        for (int i = 0; i + t.size() <= s.size(); i++)
            if (s.compare(i, t.size(), t) == 0) occ.push_back(i);
        CHECK(z_search(s, t) == occ);
    }
    return 0;
}
