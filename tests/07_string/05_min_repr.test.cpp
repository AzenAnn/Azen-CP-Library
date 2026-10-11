#include "../common.hpp"
#include "../../templates/07_string/05_min_repr.hpp"

int main() {
    for (int it = 0; it < 3000; it++) {
        string s(rnd(1, 12), 'a');
        for (char &c : s) c = 'a' + rnd(0, it % 2 ? 1 : 3);
        int n = s.size(), best = 0;
        for (int p = 1; p < n; p++)
            if (s.substr(p) + s.substr(0, p) < s.substr(best) + s.substr(0, best)) best = p;
        CHECK(min_rotation(s) == best);
    }
    return 0;
}
