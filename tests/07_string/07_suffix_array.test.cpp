#include "../common.hpp"
#include "../../templates/07_string/07_suffix_array.hpp"

int main() {
    for (int it = 0; it < 1000; it++) {
        string s(rnd(0, 40), 'a');
        for (char &c : s) c = 'a' + rnd(0, it % 2 ? 1 : 3);
        int n = s.size();
        vector<int> sa(n);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&](int a, int b) { return s.substr(a) < s.substr(b); });
        CHECK(suffix_array(s) == sa);
        auto lcp = lcp_array(s, sa);
        for (int i = 1; i < n; i++) {
            int k = 0;
            while (sa[i] + k < n && sa[i - 1] + k < n && s[sa[i] + k] == s[sa[i - 1] + k]) k++;
            CHECK(lcp[i] == k);
        }
        set<string> subs;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j <= n; j++) subs.insert(s.substr(i, j - i));
        CHECK(distinct_substrings(s) == (ll)subs.size());
    }
    return 0;
}
