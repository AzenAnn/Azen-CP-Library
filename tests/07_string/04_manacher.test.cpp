#include "../common.hpp"
#include "../../templates/07_string/04_manacher.hpp"

int main() {
    for (int it = 0; it < 1000; it++) {
        string s(rnd(0, 25), 'a');
        for (char &c : s) c = 'a' + rnd(0, 1);
        auto d = manacher(s);
        int n = s.size(), best = 0;
        for (int l = 0; l < n; l++)
            for (int r = l + 1; r <= n; r++) {
                string sub = s.substr(l, r - l);
                bool pal = equal(sub.begin(), sub.end(), sub.rbegin());
                CHECK(is_palindrome(d, l, r) == pal);
                if (pal) best = max(best, r - l);
            }
        auto [st, len] = longest_palindrome(s);
        CHECK(len == best);
        string sub = s.substr(st, len);
        CHECK(equal(sub.begin(), sub.end(), sub.rbegin()));
    }
    return 0;
}
