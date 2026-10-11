#include "../common.hpp"
#include "../../templates/06_dp/07_digit_dp.hpp"

int main() {
    array<ll, 10> acc{};
    ll windy = 0;
    for (ll x = 0; x <= 30000; x++) {
        if (x > 0) {
            string s = to_string(x);
            for (char c : s) acc[c - '0']++;
            bool ok = true;
            for (size_t i = 1; i < s.size(); i++) ok &= abs(s[i] - s[i - 1]) >= 2;
            windy += ok;
        }
        if (x % 997 == 0 || x < 300) {
            CHECK(digit_count(x) == acc);
            CHECK(windy_count(x) == windy);
        }
    }
    // 大数：与"按区间相减"的一致性检查
    ll a = 123456789012LL, b = 987654321098LL;
    auto fa = digit_count(a), fb = digit_count(b);
    ll total = 0;
    for (int d = 0; d < 10; d++) total += fb[d] - fa[d];
    ll digits = 0;   // [a+1, b] 中所有数的位数之和
    for (ll p = 1, len = 1; p <= b; p *= 10, len++) {
        ll lo = max(p, a + 1), hi = min(p * 10 - 1, b);
        if (lo <= hi) digits += (hi - lo + 1) * len;
    }
    CHECK(total == digits);
    return 0;
}
