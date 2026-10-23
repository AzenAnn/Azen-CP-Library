// 只引入一个总头文件，即可使用库中全部 DONE 模板；这里演示 Fenwick。
// 保持此文件位于 contest/，相对路径便能找到 ../templates/ 中的实现。
// OJ 通常只接收单文件，提交前需将本地头文件展开为源码。
// 输入：n q；接着 n 个初始值；接着 q 个操作。
// 1 p x：a[p] += x；2 l r：输出 a[l..r] 的和。下标从 1 开始。
// 样例输入：
// 5 3
// 1 2 3 4 5
// 2 1 5
// 1 3 7
// 2 2 4
// 样例输出：
// 15
// 16
#include "../templates/all.hpp"

void solve() {
    int n, q;
    if (!(cin >> n >> q)) return;
    Fenwick f(n);
    for (int i = 1; i <= n; ++i) {
        ll x;
        cin >> x;
        f.add(i, x);
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int p;
            ll x;
            cin >> p >> x;
            f.add(p, x);
        } else if (op == 2) {
            int l, r;
            cin >> l >> r;
            cout << f.sum(l, r) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;  // 多组测试时启用。
    while (T--) solve();
    return 0;
}
