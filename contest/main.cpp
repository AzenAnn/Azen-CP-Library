#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

struct StrHash {
    using u64 = unsigned long long;
    static constexpr u64 M = (1ULL << 61) - 1;
    static u64 mul(u64 a, u64 b) {
        __uint128_t c = (__uint128_t)a * b;
        u64 r = (u64)(c & M) + (u64)(c >> 61);
        return r >= M ? r - M : r;
    }
    static u64 base() {
        static const u64 B = mt19937_64(chrono::steady_clock::now().time_since_epoch().count())() % (M - 1000) + 500;
        return B;
    }
    vector<u64> h, p;
    StrHash(const string &s) : h(s.size() + 1, 0), p(s.size() + 1, 1) {
        u64 B = base();
        for (size_t i = 0; i < s.size(); i++) {
            h[i + 1] = mul(h[i], B) + (unsigned char)s[i];
            if (h[i + 1] >= M) h[i + 1] -= M;
            p[i + 1] = mul(p[i], B);
        }
    }
    u64 get(int l, int r) const {
        u64 x = h[r] + M - mul(h[l], p[r - l]);
        return x >= M ? x - M : x;
    }
};

int hash_lcp(const StrHash &a, int i, const StrHash &b, int j) {
    int lo = 0, hi = min((int)a.h.size() - 1 - i, (int)b.h.size() - 1 - j) + 1;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        (a.get(i, i + mid) == b.get(j, j + mid) ? lo : hi) = mid;
    }
    return lo;
}


void solve() {
    int n, len, S;
    cin >> n >> len >> S;
    vector<string> a(n);
    for (auto &s : a) cin >> s;

    vector<StrHash> hs;
    for (auto &s : a) hs.emplace_back(s);

    ll ans = 0;
    // 对每个删除位置，统计哈希值出现次数
    for (int del = 0; del < len; del++) {
        unordered_map<ull, int> cnt;
        for (int i = 0; i < n; i++) {
            ull h = (StrHash::mul(hs[i].get(0, del), hs[i].p[len - del - 1]) + hs[i].get(del + 1, len)) % StrHash::M;
            ans += cnt[h]++;
        }
    }
    cout << ans << "\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;   // 只有一组数据时删掉这一行
    while (T--) solve();
    return 0;
}
