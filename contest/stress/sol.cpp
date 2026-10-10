// 要检查的正解（比赛时把 main.cpp 复制过来：cp ../main.cpp sol.cpp）
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        long long cur = 0, best = LLONG_MIN;
        for (int i = 0; i < n; i++) {
            long long x;
            cin >> x;
            cur = max(cur + x, x);
            best = max(best, cur);
        }
        cout << best << '\n';
    }
}
