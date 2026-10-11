// 所有测试共用的开头：与 contest/main.cpp 的开头一致，再加上随机数和断言工具
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937_64 test_rng(20261010);
ll rnd(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(test_rng); }   // [l, r]
vector<ll> rnd_vec(int n, ll l, ll r) {
    vector<ll> a(n);
    for (auto &x : a) x = rnd(l, r);
    return a;
}

#define CHECK(...)                                                                    \
    do {                                                                              \
        if (!(__VA_ARGS__)) {                                                                \
            fprintf(stderr, "CHECK 失败: %s  (%s:%d)\n", #__VA_ARGS__, __FILE__, __LINE__); \
            exit(1);                                                                  \
        }                                                                             \
    } while (0)
