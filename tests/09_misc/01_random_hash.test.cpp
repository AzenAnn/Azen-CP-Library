#include "../common.hpp"
#include "../../templates/09_misc/01_random_hash.hpp"

int main() {
    for (int it = 0; it < 10000; it++) {
        ll l = rnd(-100, 100), r = l + rnd(0, 50), x = rand_int(l, r);
        CHECK(l <= x && x <= r);
    }
    unordered_map<ll, int, SafeHash> mp;
    map<ll, int> ref;
    for (int i = 0; i < 20000; i++) {
        ll k = rnd(-1000, 1000);
        mp[k]++, ref[k]++;
    }
    CHECK(mp.size() == ref.size());
    for (auto [k, v] : ref) CHECK(mp[k] == v);
    unordered_map<pair<ll, ll>, int, SafeHash> pm;
    pm[{1, 2}] = 3, pm[{2, 1}] = 4;
    CHECK(pm[{1, 2}] == 3 && pm[{2, 1}] == 4 && pm.size() == 2);
    return 0;
}
