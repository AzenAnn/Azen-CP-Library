#include "../common.hpp"
#include "../../templates/06_dp/02_lis_lcs.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(0, 12);
        auto a = rnd_vec(n, 0, 6);
        int best_s = 0, best_ns = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            vector<ll> s;
            for (int i = 0; i < n; i++)
                if (mask >> i & 1) s.push_back(a[i]);
            bool inc = true, nondec = true;
            for (size_t i = 1; i < s.size(); i++) inc &= s[i - 1] < s[i], nondec &= s[i - 1] <= s[i];
            if (inc) best_s = max(best_s, (int)s.size());
            if (nondec) best_ns = max(best_ns, (int)s.size());
        }
        CHECK(lis(a) == best_s && lis(a, false) == best_ns);
        auto idx = lis_indices(a);
        CHECK((int)idx.size() == best_s);
        for (size_t i = 1; i < idx.size(); i++) CHECK(idx[i - 1] < idx[i] && a[idx[i - 1]] < a[idx[i]]);

        string x(rnd(0, 8), 'a'), y(rnd(0, 8), 'a');
        for (char &c : x) c = 'a' + rnd(0, 2);
        for (char &c : y) c = 'a' + rnd(0, 2);
        int bl = 0;   // 暴力 LCS：枚举 x 的子序列，检查是否为 y 的子序列
        for (int mask = 0; mask < (1 << x.size()); mask++) {
            string s;
            for (size_t i = 0; i < x.size(); i++)
                if (mask >> i & 1) s += x[i];
            size_t j = 0;
            for (char c : y)
                if (j < s.size() && s[j] == c) j++;
            if (j == s.size()) bl = max(bl, (int)s.size());
        }
        CHECK(lcs(x, y) == bl);
        // 编辑距离：与 BFS 暴力对比（字符串很短）
        if (x.size() <= 4 && y.size() <= 4) {
            map<string, int> dist{{x, 0}};
            queue<string> q;
            q.push(x);
            while (!q.empty()) {
                string s = q.front();
                q.pop();
                if (s == y) break;
                vector<string> nxt;
                for (size_t i = 0; i <= s.size(); i++)
                    for (char c : string("abc")) nxt.push_back(s.substr(0, i) + c + s.substr(i));
                for (size_t i = 0; i < s.size(); i++) {
                    nxt.push_back(s.substr(0, i) + s.substr(i + 1));
                    for (char c : string("abc")) nxt.push_back(s.substr(0, i) + c + s.substr(i + 1));
                }
                for (auto &t : nxt)
                    if (t.size() <= 6 && !dist.count(t)) dist[t] = dist[s] + 1, q.push(t);
            }
            CHECK(edit_distance(x, y) == dist[y]);
        }
        int m = rnd(1, 8);
        vector<int> p(m), q2(m);
        iota(p.begin(), p.end(), 1), iota(q2.begin(), q2.end(), 1);
        shuffle(p.begin(), p.end(), test_rng), shuffle(q2.begin(), q2.end(), test_rng);
        CHECK(lcs_permutation(p, q2) == lcs(p, q2));
    }
    return 0;
}
