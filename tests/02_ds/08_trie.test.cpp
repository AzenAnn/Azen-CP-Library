#include "../common.hpp"
#include "../../templates/02_ds/08_trie.hpp"

string rnd_str(int maxlen) {
    string s(rnd(0, maxlen), 'a');
    for (char &c : s) c = 'a' + rnd(0, 2);
    return s;
}

int main() {
    for (int it = 0; it < 200; it++) {
        Trie t;
        vector<string> words;
        for (int i = 0; i < 30; i++) {
            words.push_back(rnd_str(4));
            t.insert(words.back());
        }
        for (int q = 0; q < 30; q++) {
            string p = rnd_str(4);
            int c = 0, pc = 0;
            for (auto &w : words) c += w == p, pc += w.compare(0, p.size(), p) == 0 && w.size() >= p.size();
            CHECK(t.count(p) == c);
            CHECK(t.prefix_count(p) == pc);
        }
        XorTrie xt;
        multiset<int> ms;
        for (int op = 0; op < 60; op++) {
            if (ms.empty() || rnd(0, 2)) {
                int x = rnd(0, (1 << 10) - 1);
                xt.insert(x), ms.insert(x);
            } else {
                auto pos = next(ms.begin(), rnd(0, ms.size() - 1));
                xt.insert(*pos, -1), ms.erase(pos);
            }
            if (ms.empty()) continue;
            int x = rnd(0, (1 << 10) - 1), best = 0;
            for (int y : ms) best = max(best, x ^ y);
            CHECK(xt.max_xor(x) == best);
        }
    }
    return 0;
}
