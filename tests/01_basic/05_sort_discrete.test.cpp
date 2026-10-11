#include "../common.hpp"
#include "../../templates/01_basic/05_sort_discrete.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(0, 40);
        auto a = rnd_vec(n, -5, 5);
        ll inv = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) inv += a[i] > a[j];
        CHECK(inversions(a) == inv);
        if (!n) continue;
        Discrete d(a);
        for (int i = 0; i < n; i++) {
            CHECK(d.value(d.id(a[i])) == a[i]);
            for (int j = 0; j < n; j++) CHECK((a[i] < a[j]) == (d.id(a[i]) < d.id(a[j])));
        }
    }
    return 0;
}
