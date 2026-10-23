#include "../common.hpp"
#include "../../templates/05_math/22_burnside_polya.hpp"

int main() {
    const ll P = 1000000007;
    // 暴力：枚举所有染色，取所有旋转（及翻转）中字典序最小的作为代表
    for (int n = 1; n <= 8; n++)
        for (int m = 1; m <= 4; m++) {
            int total = 1;
            for (int i = 0; i < n; i++) total *= m;
            set<vector<int>> neck, brace;
            for (int x = 0; x < total; x++) {
                vector<int> a(n);
                for (int i = 0, y = x; i < n; i++, y /= m) a[i] = y % m;
                vector<int> best1 = a, best2 = a;
                for (int r = 0; r < n; r++) {
                    vector<int> b(n), c(n);
                    for (int i = 0; i < n; i++) b[i] = a[(i + r) % n], c[i] = a[((r - i) % n + n) % n];
                    best1 = min(best1, b), best2 = min({best2, b, c});
                }
                neck.insert(best1), brace.insert(best2);
            }
            CHECK(count_necklaces(n, m, P) == (ll)neck.size());
            CHECK(count_bracelets(n, m, P) == (ll)brace.size());
            // 一般形式：把旋转群写出来
            vector<vector<int>> rot;
            for (int r = 0; r < n; r++) {
                vector<int> g(n);
                for (int i = 0; i < n; i++) g[i] = (i + r) % n;
                rot.push_back(g);
            }
            CHECK(polya_general(rot, m, P) == (ll)neck.size());
        }
    // 大 n：与按 gcd 直接求和（O(n)）对比
    for (int it = 0; it < 50; it++) {
        ll n = rnd(1, 20000), m = rnd(1, 1000000000);
        const ll p = 998244353;
        ll s = 0;
        for (ll i = 0; i < n; i++) s = (s + polya_pow(m, __gcd(i, n) == 0 ? n : __gcd(i, n), p)) % p;
        s = s * polya_pow(n, p - 2, p) % p;
        CHECK(count_necklaces(n, m, p) == s);
    }
    return 0;
}
