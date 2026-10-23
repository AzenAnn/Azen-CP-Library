#include "../common.hpp"
#include "../../templates/07_string/11_seq_automaton.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(0, 12), sig = rnd(1, 4);
        string s;
        for (int i = 0; i < n; i++) s += char('a' + rnd(0, sig - 1));
        SeqAutomaton sa(s);
        set<string> subs;
        for (int m = 0; m < (1 << n); m++) {
            string t;
            for (int i = 0; i < n; i++)
                if (m >> i & 1) t += s[i];
            subs.insert(t);
        }
        CHECK(sa.count_distinct_subsequences(1000000007) == (ll)subs.size());
        for (int q = 0; q < 30; q++) {
            string t;
            int L = rnd(0, 6);
            for (int i = 0; i < L; i++) t += char('a' + rnd(0, sig));
            CHECK(sa.is_subsequence(t) == (subs.count(t) > 0));
        }
    }
    return 0;
}
