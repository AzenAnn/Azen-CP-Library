#include "../common.hpp"
#include "../../templates/01_basic/06_bits.hpp"

int main() {
    for (int mask = 0; mask < 256; mask++) {
        vector<int> got, expect;
        for_each_subset(mask, [&](int s) { got.push_back(s); });
        for (int s = 0; s < 256; s++)
            if ((s & mask) == s) expect.push_back(s);
        sort(got.begin(), got.end());
        CHECK(got == expect);
    }
    for (int n = 1; n <= 10; n++)
        for (int k = 0; k <= n; k++) {
            vector<int> got, expect;
            for_each_k_subset(n, k, [&](int s) { got.push_back(s); });
            for (int s = 0; s < (1 << n); s++)
                if (__builtin_popcount(s) == k) expect.push_back(s);
            CHECK(got == expect);
        }
    for (int it = 0; it < 200; it++) {
        auto a = rnd_vec(rnd(0, 30), 0, (1 << 20) - 1);
        ll s = 0;
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = i + 1; j < a.size(); j++) s += a[i] ^ a[j];
        CHECK(pair_xor_sum(a, 20) == s);
    }
    return 0;
}
