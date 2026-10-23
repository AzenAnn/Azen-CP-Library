#include "../common.hpp"
#include "../../templates/05_math/20_catalan.hpp"

int main() {
    const ll P = 1000000007;
    CountingTables ct(9, P);
    for (int n = 0; n <= 9; n++) {
        // 卡特兰：长度 2n 的合法括号序列个数
        ll c = 0;
        for (int s = 0; s < (1 << (2 * n)); s++) {
            int bal = 0;
            bool ok = true;
            for (int i = 0; i < 2 * n && ok; i++) bal += (s >> i & 1) ? 1 : -1, ok = bal >= 0;
            c += ok && bal == 0;
        }
        CHECK(ct.catalan[n] == c);
        // 第一类：排列按循环个数分类；第二类：用"限制增长串"枚举集合划分
        vector<ll> cyc(n + 1, 0), part(n + 1, 0);
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        do {
            vector<bool> vis(n);
            int k = 0;
            for (int i = 0; i < n; i++)
                if (!vis[i]) {
                    k++;
                    for (int j = i; !vis[j]; j = p[j]) vis[j] = true;
                }
            cyc[k]++;
        } while (next_permutation(p.begin(), p.end()));
        vector<int> a(n, 0);
        function<void(int, int)> go = [&](int i, int mx) {
            if (i == n) return void(part[mx]++);
            for (int v = 0; v <= mx; v++) a[i] = v, go(i + 1, max(mx, v + 1));
        };
        go(0, 0);
        ll bell = 0;
        for (int k = 0; k <= n; k++) {
            CHECK(ct.s1[n][k] == cyc[k] % P);
            CHECK(ct.s2[n][k] == part[k]);
            bell += part[k];
        }
        CHECK(ct.bell[n] == bell);
    }
    // 模数为合数时也成立（只用了加法和乘法）：与精确值（n ≤ 30 时不超过 long long）比较
    CountingTables small(30, 1000);
    vector<ll> exact(31, 0);
    exact[0] = 1;
    for (int i = 1; i <= 30; i++)
        for (int j = 0; j < i; j++) exact[i] += exact[j] * exact[i - 1 - j];
    for (int n = 0; n <= 30; n++) CHECK(small.catalan[n] == exact[n] % 1000);
    return 0;
}
