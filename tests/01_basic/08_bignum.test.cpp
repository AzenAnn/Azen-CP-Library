#include "../common.hpp"
#include "../../templates/01_basic/08_bignum.hpp"

string rnd_num(int maxlen) {
    string s(rnd(1, maxlen), '0');
    for (char &c : s) c = '0' + rnd(0, 9);
    return s;
}
string i128s(__int128 x) {
    if (x == 0) return "0";
    string s;
    while (x) s += char('0' + x % 10), x /= 10;
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    for (int it = 0; it < 5000; it++) {
        __int128 a = rnd(0, 1e18), b = rnd(0, 1e18);
        if (it % 3 == 0) a = rnd(0, 1000), b = rnd(0, 1000);
        if (a < b) swap(a, b);
        Big A = big_from(i128s(a)), B = big_from(i128s(b));
        CHECK(big_str(A) == i128s(a));
        CHECK(big_str(big_add(A, B)) == i128s(a + b));
        CHECK(big_str(big_sub(A, B)) == i128s(a - b));
        CHECK(big_str(big_mul(A, B)) == i128s(a * b));
        ll s = rnd(0, 1e9);
        CHECK(big_str(big_mul_small(A, s)) == i128s(a * s));
        CHECK(big_cmp(A, B) == (a < b ? -1 : a > b));
        if (s) {
            auto [q, r] = big_divmod_small(A, s);
            CHECK(big_str(q) == i128s(a / s) && r == (ll)(a % s));
        }
        if (b) {
            auto [q, r] = big_divmod(A, B);
            CHECK(big_str(q) == i128s(a / b) && big_str(r) == i128s(a % b));
        }
    }
    // 长数字：(x * y) / y == x，(x + y) - y == x
    for (int it = 0; it < 200; it++) {
        Big x = big_from(rnd_num(60)), y = big_from(rnd_num(40));
        if (big_str(y) == "0") continue;
        auto [q, r] = big_divmod(big_mul(x, y), y);
        CHECK(big_cmp(q, x) == 0 && big_str(r) == "0");
        CHECK(big_cmp(big_sub(big_add(x, y), y), x) == 0);
    }
    CHECK(big_str(big_from("000123")) == "123" && big_str(big_from("0")) == "0");
    return 0;
}
