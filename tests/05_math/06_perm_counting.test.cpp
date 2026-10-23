#include "../common.hpp"
#include "../../templates/05_math/06_perm_counting.hpp"

int main() {
    // 康托展开 / 逆展开：与 next_permutation 的顺序对比
    for (int n = 1; n <= 7; n++) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        ll r = 0;
        do {
            CHECK(cantor_rank(p, 1000000007) == r);
            CHECK(cantor_rank(p, 7) == r % 7);
            CHECK(cantor_unrank(n, r) == p);
            r++;
        } while (next_permutation(p.begin(), p.end()));
    }
    {   // n = 20 的最后一个排列：排名 20! - 1
        vector<int> p(20);
        iota(p.rbegin(), p.rend(), 0);
        ll f = 1;
        for (int i = 1; i <= 20; i++) f *= i;
        CHECK(cantor_rank(p, LLONG_MAX) == f - 1);
        CHECK(cantor_unrank(20, f - 1) == p);
    }
    // 错排：暴力枚举
    auto d = derangements(9, 1000000007);
    for (int n = 0; n <= 8; n++) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        ll c = 0;
        do {
            bool ok = true;
            for (int i = 0; i < n; i++) ok &= p[i] != i;
            c += ok;
        } while (next_permutation(p.begin(), p.end()));
        CHECK(d[n] == c);
    }
    CHECK(derangements(1, 5)[1] == 0 && derangements(0, 1)[0] == 0);
    // 约瑟夫：模拟
    for (int n = 1; n <= 60; n++)
        for (int k = 1; k <= 70; k++) {
            vector<int> a(n), order;
            iota(a.begin(), a.end(), 0);
            int cur = 0;
            while (!a.empty()) {
                cur = (cur + k - 1) % a.size();
                order.push_back(a[cur]), a.erase(a.begin() + cur);
            }
            CHECK(josephus(n, k) == order.back());
            CHECK(josephus_big(n, k) == order.back());
            CHECK(josephus_order(n, k) == order);
        }
    for (int it = 0; it < 200; it++) {   // 大 n：两种做法互相对比
        ll n = rnd(1, 200000), k = rnd(1, 50);
        CHECK(josephus(n, k) == josephus_big(n, k));
    }
    return 0;
}
