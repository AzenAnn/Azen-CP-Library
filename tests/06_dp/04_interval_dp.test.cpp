#include "../common.hpp"
#include "../../templates/06_dp/04_interval_dp.hpp"

// 暴力：枚举每一步合并哪两堆相邻的石子（ring 时首尾也相邻）
pair<ll, ll> brute(vector<ll> a, bool ring) {
    if (a.size() <= 1) return {0, 0};
    ll mn = LLONG_MAX, mx = LLONG_MIN;
    int n = a.size();
    for (int i = 0; i < (ring && n > 2 ? n : n - 1); i++) {
        int j = (i + 1) % n;
        vector<ll> b;
        ll c = a[i] + a[j];
        for (int k = 0; k < n; k++) {
            if (k == j) continue;
            b.push_back(k == i ? c : a[k]);
        }
        auto [x, y] = brute(b, ring);
        mn = min(mn, x + c), mx = max(mx, y + c);
    }
    return {mn, mx};
}

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 7);
        auto a = rnd_vec(n, 1, 20);
        auto [mn, mx] = brute(a, false);
        CHECK(stone_merge(a) == mn && stone_merge(a, true) == mx);
        auto [rmn, rmx] = brute(a, true);
        CHECK(stone_merge_ring(a) == rmn && stone_merge_ring(a, true) == rmx);
        string s(rnd(0, 10), 'a');
        for (char &c : s) c = 'a' + rnd(0, 2);
        int best = 0;
        for (int mask = 0; mask < (1 << s.size()); mask++) {
            string t;
            for (size_t i = 0; i < s.size(); i++)
                if (mask >> i & 1) t += s[i];
            if (equal(t.begin(), t.end(), t.rbegin())) best = max(best, (int)t.size());
        }
        CHECK(longest_palindrome_subseq(s) == best);
    }
    return 0;
}
