#include "../common.hpp"
#include "../../templates/07_string/09_pam.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        string s(rnd(1, 30), 'a');
        for (char &c : s) c = 'a' + rnd(0, it % 2 ? 1 : 2);
        PAM pam;
        for (char c : s) pam.add(c);
        int n = s.size();
        auto is_pal = [](const string &t) { return equal(t.begin(), t.end(), t.rbegin()); };
        map<string, ll> occ;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j <= n; j++)
                if (is_pal(s.substr(i, j - i))) occ[s.substr(i, j - i)]++;
        CHECK(pam.distinct_palindromes() == (int)occ.size());
        for (int i = 0; i < n; i++) {   // 以 s[i] 结尾的回文子串个数
            int c = 0;
            for (int j = 0; j <= i; j++) c += is_pal(s.substr(j, i - j + 1));
            CHECK(pam.suffix_count[i] == c);
        }
        // 每个节点对应的回文串：从奇根 / 偶根出发，沿 ch 还原
        auto o = pam.occurrences();
        vector<string> str(pam.len.size());
        for (size_t v = 0; v < pam.len.size(); v++)
            for (int x = 0; x < 26; x++) {
                int u = pam.ch[v][x];
                if (!u) continue;
                string c(1, char('a' + x));
                str[u] = pam.len[v] == -1 ? c : c + str[v] + c;
            }
        for (size_t v = 2; v < pam.len.size(); v++) CHECK(occ.count(str[v]) && o[v] == occ[str[v]]);
    }
    return 0;
}
