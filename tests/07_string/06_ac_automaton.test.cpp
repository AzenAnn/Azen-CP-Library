#include "../common.hpp"
#include "../../templates/07_string/06_ac_automaton.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int k = rnd(1, 8);
        vector<string> pats(k);
        ACAutomaton ac;
        vector<int> nodes;
        for (auto &p : pats) {
            p.assign(rnd(1, 4), 'a');
            for (char &c : p) c = 'a' + rnd(0, 2);
            nodes.push_back(ac.insert(p));
        }
        ac.build();
        string t(rnd(0, 40), 'a');
        for (char &c : t) c = 'a' + rnd(0, 2);
        auto got = ac.count_occurrences(t, nodes);
        int appeared = 0;
        for (int i = 0; i < k; i++) {
            ll c = 0;
            for (size_t j = 0; j + pats[i].size() <= t.size(); j++) c += t.compare(j, pats[i].size(), pats[i]) == 0;
            CHECK(got[i] == c);
            appeared += c > 0;
        }
        CHECK(ac.count_appeared(t, nodes) == appeared);
    }
    return 0;
}
