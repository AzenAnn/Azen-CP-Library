#include "../common.hpp"
#include "../../templates/05_math/16_fft_ntt.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 200), m = rnd(1, 200);
        auto a = rnd_vec(n, -1000, 1000), b = rnd_vec(m, -1000, 1000);
        vector<ll> c(n + m - 1, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) c[i + j] += a[i] * b[j];
        CHECK(multiply_fft(a, b) == c);
        auto d = multiply_ntt(a, b);
        for (int i = 0; i < n + m - 1; i++) CHECK(d[i] == (c[i] % NTT_MOD + NTT_MOD) % NTT_MOD);
    }
    CHECK(multiply_fft({}, {1}).empty() && multiply_ntt({1}, {}).empty());
    return 0;
}
