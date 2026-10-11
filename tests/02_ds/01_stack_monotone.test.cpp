#include "../common.hpp"
#include "../../templates/02_ds/01_stack_monotone.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(0, 30);
        auto a = rnd_vec(n, 0, 6);
        auto L = left_greater(a), R = right_greater(a);
        for (int i = 0; i < n; i++) {
            int l = -1, r = n;
            for (int j = i - 1; j >= 0; j--)
                if (a[j] > a[i]) { l = j; break; }
            for (int j = i + 1; j < n; j++)
                if (a[j] > a[i]) { r = j; break; }
            CHECK(L[i] == l && R[i] == r);
        }
        ll s = 0, rect = 0;
        for (int l = 0; l < n; l++) {
            ll mn = LLONG_MAX;
            for (int r = l; r < n; r++) mn = min(mn, a[r]), s += mn, rect = max(rect, mn * (r - l + 1));
        }
        CHECK(sum_subarray_min(a) == s);
        CHECK(largest_rectangle(a) == rect);
    }
    return 0;
}
