// 暴力解：写得越简单越好，保证正确
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (auto &x : a) cin >> x;
        long long best = LLONG_MIN;
        for (int l = 0; l < n; l++)
            for (int r = l; r < n; r++) best = max(best, accumulate(a.begin() + l, a.begin() + r + 1, 0LL));
        cout << best << '\n';
    }
}
