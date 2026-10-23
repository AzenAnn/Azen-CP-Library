#include "../common.hpp"
#include "../../templates/06_dp/15_dp_of_dp.hpp"

int main() {
    for (int it = 0; it < 200; it++) {
        string alpha = vector<string>{"ab", "abc", "ACGT"}[rnd(0, 2)];
        int m = rnd(0, 6), n = rnd(0, 6);
        while (pow(alpha.size(), n) > 5000) n--;
        string s;
        for (int i = 0; i < m; i++) s += alpha[rnd(0, alpha.size() - 1)];
        vector<ll> cnt(m + 1, 0);
        int total = 1;
        for (int i = 0; i < n; i++) total *= alpha.size();
        for (int x = 0; x < total; x++) {
            string t;
            for (int i = 0, y = x; i < n; i++, y /= alpha.size()) t += alpha[y % alpha.size()];
            vector<vector<int>> d(n + 1, vector<int>(m + 1, 0));
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++) d[i][j] = t[i - 1] == s[j - 1] ? d[i - 1][j - 1] + 1 : max(d[i - 1][j], d[i][j - 1]);
            cnt[d[n][m]]++;
        }
        CHECK(count_by_lcs(s, n, alpha, 1000000007) == cnt);
    }
    return 0;
}
